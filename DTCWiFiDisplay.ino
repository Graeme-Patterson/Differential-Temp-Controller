#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <EEPROM.h>
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ILI9341esp.h>
#include <Adafruit_GFX.h>
#include <XPT2046.h>

// which analog pin to connect
#define THERMISTORPIN A0         
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average to smooth thing sout
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000    
#define Thermistor0 0
#define Thermistor1 1
#define ThermistorSelect D3
//#define DIFFERENTIAL 5
#define DIODECOMPENSATION 100
#define RELAYOUTPUT D0
// For the esp shield, these are the default.
#define TFT_DC 2
#define TFT_CS 15
#define HOME 1
#define SET 2
#define INFO 3

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046 touch(/*cs=*/ 4, /*irq=*/ 5);

Adafruit_GFX_Button homeButton;
Adafruit_GFX_Button upButton;
Adafruit_GFX_Button downButton;
Adafruit_GFX_Button saveButton;
Adafruit_GFX_Button setButton;
Adafruit_GFX_Button infoButton;

String webPage,notice,homeWebPage,message;
int DIFFERENTIAL;
int unsavedDifferential;
float Temp0;
float Temp1;
int samples[NUMSAMPLES];
int address = 0;
int relayState = 0;
int measurePeriod=10000;  // this is 10 seconds
unsigned long time_now = 0;
int screen = 1;
static uint16_t prev_x = 0xffff, prev_y = 0xffff;

ESP8266WebServer server(80);

const char htmlPage[]PROGMEM=R"=====(
<!DOCTYPE html>
<html><head><title>DTC-SET</title></head>
<body>
<h1>Differential Temperature Controller</h1><font size="5">
<FORM METHOD="POST" action="/Save">
<p> Enter the required Temperature Differential
<br> Whole numbers only less than 100, then click SAVE</p></font>
<table>
    <tr
        ><th style="font-size: 24px; text-align: left">Temp Differential : </th>
        <th><input type="text" size="4" name="myText" value="" autofocus style="font-size:24px;" ></th>
    </tr>
    <tr>
        <th style="font-size: 24px; text-align: left">Password          :</th>
        <th><input type="password" size="4" name="myCheck" value=""  style="font-size:24px"></th>
    </tr>
</table>
<br><br>
<th><input type="submit" value="SAVE" style="height:50px; width:250px;border-radius: 8px"></th>
<input type="button" value="CANCEL" style="height:50px; width:250px;border-radius: 8px" onclick="location.href='/'" />
</form>
</body>
</html>
)=====";

void handleRoot()
{
  homeWebPage = "<!DOCTYPE html><html><head><title>DTC</title><meta http-equiv=\"refresh\" content=\"30\" /></head><body><h1>Differential Temperature Controller</h1><font size=\"5\"><p><pre>Temp Sensor 0     : ";
  homeWebPage += Temp0;
  homeWebPage += "<br>Temp Sensor 1     : ";
  homeWebPage += Temp1;
  homeWebPage += "<br>Temp Differential : ";
  homeWebPage += DIFFERENTIAL;
  homeWebPage += "<br>Output State is   :";
  if(relayState)
  {
    homeWebPage += "<button style=\"height:25px; width:60px; border-radius: 8px; color: white; background-color: green\" >ON</button>";
  }
  else
  {
    homeWebPage += "<button style=\"height:25px; width:60px; border-radius: 8px; color: white; background-color: red\" >OFF</button>";
  }
  homeWebPage += "<br></font><font size=\"5\" color=\"red\">";
  homeWebPage += message;
  homeWebPage += "</font><br><button style=\"height:50px; width:250px; border-radius: 8px\" onclick=\"location.href='/postForm'\">SET TEMP DIFFERENTIAL</button></body></html>"; // need to escape '\' the " characters
  server.send(200,"text/html",homeWebPage);
}

void handlePostForm()
{
  webPage=htmlPage;
  server.send(200,"text/html",webPage);
}

void handleSave()
{
  int tempEntered;
  Serial.println("=========================================================");
  Serial.println("Text Value = " + server.arg("myText"));
  tempEntered = (server.arg("myText")).toInt();
  //DIFFERENTIAL += 10;  // This just proves that I can use the integer
  Serial.println(tempEntered);
  if(server.arg("myCheck") != (String(ESP.getChipId()).c_str()))
  {
    message = "Password is incorrect!";
  }
  else if(tempEntered == 0)
  {
    Serial.println("Value entered wasn't a number");
    message = "Value entered wasn't a number";
  }
  else if ((tempEntered < -100) || (tempEntered > 100))
  {
    Serial.println("Value entered was to large");
    message = "Temp differential entered was to large (needs to be < 100)";
  }
  else if ((tempEntered <= 100) && (tempEntered >= -100))  // this ensures the FLASH used will only be 1 byte.
  {
    DIFFERENTIAL = tempEntered;
    EEPROM.write(address, DIFFERENTIAL);
    EEPROM.commit();
    message = "";
    delay(100);   // give it time to do what's required
  }
  server.sendHeader("Location","/");
  server.send(303);
}

void handleNotFound()
{
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void setup() 
{
  Serial.begin(115200);
  pinMode(ThermistorSelect, OUTPUT);
  pinMode(RELAYOUTPUT, OUTPUT);  
  EEPROM.begin(512);
  DIFFERENTIAL = EEPROM.read(address);  //get the initial stored value after reboot
    
  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();

  wifiManager.setTimeout(180);
  
  if(!wifiManager.autoConnect("DTCDevice")) 
  {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  } 

  //if you get here you have connected to the WiFi
  Serial.print("connected to selected WiFi access point with IP Address ");
  Serial.println(WiFi.localIP());
  message = "";
  server.on("/", HTTP_GET, handleRoot);
  server.on("/postForm",handlePostForm);  // tells server what function to call for the selected url
  server.on("/Save",handleSave);
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.begin(); // starts the web server
  Serial.println("============================================");
  Serial.println(String(ESP.getChipId()).c_str());
  Serial.println("============================================");
  SPI.setFrequency(ESP_SPI_FREQ);
  tft.begin();
  touch.begin(tft.width(), tft.height());  // Must be done before setting rotation
  Serial.print("tftx ="); Serial.print(tft.width()); Serial.print(" tfty ="); Serial.println(tft.height());
  tft.fillScreen(ILI9341_BLACK);
  // Replace these for your screen module
  touch.setCalibration(1951, 128, 169, 1915);
  drawHome();
  delay(10000);
}

void loop() 
{
  server.handleClient();   // handles web requests
  float average;
  uint16_t x, y;  // used for touch screen input

  if(millis()> time_now + measurePeriod)
  {
    time_now = millis();
    // Get Thermistor0 temp
    average = getTemp(Thermistor0);
    Temp0 = convertToTemp(average);  
    // Get Thermistor1 temp
    average = getTemp(Thermistor1);
    Temp1 = convertToTemp(average);
    // set relay state
    if((Temp1 - Temp0)>DIFFERENTIAL)
    {
      relayState = 1;
    }
    else
    {
      relayState = 0;
    }
    // write to relay output
    Serial.println("============================================");
    Serial.print("Differential value : ");
    Serial.println(Temp1 - Temp0);
    digitalWrite(RELAYOUTPUT,relayState);
 
    Serial.println("============================================");
    Serial.println(String(ESP.getChipId()).c_str());
    Serial.println("============================================");
    if(screen == HOME)
    { 
      updateHome();
    }
  }
//============================================================
if (touch.isTouching()) 
  {
    touch.getPosition(x, y);
    prev_x = x;
    prev_y = y;
  } 
  else 
  {
    prev_x = prev_y = x = y = 0xffff;
  }

  if (screen == HOME)
  {
    // Check if a button is being pressed.
    setButton.press(setButton.contains(x, y)); // tell the button it is pressed 
    infoButton.press(infoButton.contains(x,y));
    // now we can ask the buttons if their state has changed
    if (setButton.justReleased()) { unsavedDifferential = DIFFERENTIAL; drawSetScreen();}
    if (setButton.justPressed()) { setButton.drawButton(true);} // draw invert!       
    if (infoButton.justReleased()) { drawInfo();} 
    if (infoButton.justPressed()) { infoButton.drawButton(true);} // draw invert!  
  }
  else if (screen == SET)
  {
    // Check if a button is being pressed.
    homeButton.press(homeButton.contains(x, y)); // tell the button it is pressed
    upButton.press(upButton.contains(x, y)); // tell the button it is pressed
    downButton.press(downButton.contains(x, y)); // tell the button it is pressed
    saveButton.press(saveButton.contains(x, y)); // tell the button it is pressed
  
    // now we can ask the buttons if their state has changed
    if (homeButton.justReleased()) {drawHome();} 
    if (homeButton.justPressed()) { homeButton.drawButton(true);} // draw invert!
    if (upButton.justReleased()) { printDifferential(); upButton.drawButton();} // draw normal
    if (upButton.justPressed()) { unsavedDifferential += 1; upButton.drawButton(true);} // draw invert!
    if (downButton.justReleased()) { printDifferential(); downButton.drawButton();} // draw normal
    if (downButton.justPressed()) { unsavedDifferential -= 1; downButton.drawButton(true);} // draw invert!
    if (saveButton.justReleased()) 
    { 
      // save the unsavedDifferential to DIFFERENTIAL and store
      DIFFERENTIAL = unsavedDifferential;
      EEPROM.write(address, DIFFERENTIAL);
      EEPROM.commit();
      delay(100);   // give it time to do what's required
      saveButton.drawButton(); // draw normal
    } 
    if (saveButton.justPressed()) { saveButton.drawButton(true);} // draw invert!
  }
  else if (screen == INFO)
  {
    // Check if a button is being pressed.
    homeButton.press(homeButton.contains(x, y)); // tell the button it is pressed
    upButton.press(upButton.contains(x, y)); // tell the button it is pressed
    if (homeButton.justReleased()) {drawHome();} 
    if (homeButton.justPressed()) { homeButton.drawButton(true);} // draw invert!        
  }
  delay(20);
}

float getTemp(int Thermistor)
{
  uint8_t i;
  float average;

  digitalWrite(ThermistorSelect, Thermistor);
  delay(10);
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) 
  {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
  }
  
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) 
  {
     average += samples[i];
  }
  average /= NUMSAMPLES;
  average += DIODECOMPENSATION;
  Serial.println("============================================");
  Serial.print("Average analog reading on Thermistor "); 
  Serial.print(Thermistor);
  Serial.print(" ");
  Serial.println(average);
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  Serial.print("Resistance of Thermistor "); 
  Serial.print(Thermistor);
  Serial.print(" ");
  Serial.println(average);  
  return average;
}

float convertToTemp(float average)
{
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // In Kelvin, convert to C  
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");
  Serial.println("============================================");
  return steinhart;
}

void updateHome()
{
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.fillRoundRect(160,55,60,35,10, ILI9341_BLACK);
  tft.drawRoundRect(160,55,60,35,10, ILI9341_DARKCYAN);
  tft.fillRoundRect(160,95,60,35,10, ILI9341_BLACK);
  tft.drawRoundRect(160,95,60,35,10, ILI9341_DARKCYAN); 
  tft.fillRoundRect(160,135,60,35,10, ILI9341_BLACK);
  tft.drawRoundRect(160,135,60,35,10, ILI9341_DARKCYAN);   
  
  tft.setCursor(162, 65);
  tft.println(Temp0);
  tft.setCursor(162, 105);
  tft.println(Temp1);  
  tft.setCursor(180,145);
  if(DIFFERENTIAL < 10){tft.print(" ");}
  tft.println(DIFFERENTIAL);  
  
  tft.setTextColor(ILI9341_WHITE);
  if(relayState)
  {
    tft.fillRoundRect(160, 175, 60, 35, 10, ILI9341_DARKGREEN);
    tft.setCursor(167,179);
    tft.setTextSize(4);
    tft.print("ON");
  }
  else
  {
    tft.fillRoundRect(160, 175, 60, 35, 10, ILI9341_RED);
    tft.setCursor(165,181);
    tft.setTextSize(3);
    tft.print("OFF");
  }
}

void drawHome()
{
  HomeMadeTech();
  screen = HOME;
  setButton.initButtonUL(&tft, 20, 230, 95, 40, ILI9341_DARKCYAN, ILI9341_BLUE, ILI9341_GREENYELLOW, "Set", 2);
  setButton.drawButton();
  infoButton.initButtonUL(&tft, 125, 230, 95, 40, ILI9341_DARKCYAN, ILI9341_BLUE, ILI9341_GREENYELLOW, "Info", 2);
  infoButton.drawButton();
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.setCursor(25, 65);
  tft.println("Probe #1");
  tft.setCursor(25, 105);
  tft.println("Probe #2");
  tft.setCursor(25, 145);
  tft.println("Temp Diff ");
  tft.setCursor(25, 185);
  tft.print("Output is");
  updateHome();
}

void drawSetScreen()
{
  HomeMadeTech();
  screen = SET;
  homeButton.initButtonUL(&tft, 20, 230, 95, 40, ILI9341_DARKCYAN, ILI9341_BLUE, ILI9341_GREENYELLOW, "Home", 2);
  upButton.initButtonUL(&tft, 170, 100, 50, 50, ILI9341_DARKCYAN, ILI9341_BLUE, ILI9341_GREENYELLOW, "UP", 2);
  downButton.initButtonUL(&tft, 170, 160, 50, 50, ILI9341_DARKCYAN, ILI9341_BLUE, ILI9341_GREENYELLOW, "DN", 2);
  saveButton.initButtonUL(&tft, 125, 230, 95, 40, ILI9341_DARKCYAN, ILI9341_BLUE, ILI9341_GREENYELLOW, "Save", 2);
  homeButton.drawButton();
  upButton.drawButton();
  downButton.drawButton();
  saveButton.drawButton();
  tft.drawRoundRect(20, 100, 140, 110, 10, ILI9341_DARKCYAN);
  printDifferential();
}

void drawInfo()
{
  HomeMadeTech();
  screen = INFO; 
  homeButton.initButtonUL(&tft, 20, 230, 95, 40, ILI9341_DARKCYAN, ILI9341_BLUE, ILI9341_GREENYELLOW, "Home", 2);
  homeButton.drawButton(); 
  tft.setTextColor(ILI9341_BLUE);
  tft.setCursor(25, 65);
  tft.print("ChipID is ");
  tft.println(String(ESP.getChipId()).c_str());
  tft.setCursor(25, 85);
  tft.println("IP Address ");
  tft.setCursor(25, 105);
  tft.println(WiFi.localIP());
  tft.setCursor(25, 185);
  tft.setTextSize(1);
  tft.println("Designed and built by Graeme");
  tft.setCursor(25, 195);
  tft.println("in Gilmore ACT");
}
void printDifferential()
{
  if(unsavedDifferential >= 20){unsavedDifferential = 20; tft.setTextColor(ILI9341_RED);}
  if(unsavedDifferential <= 0){unsavedDifferential = 0; tft.setTextColor(ILI9341_RED);}
  else {tft.setTextColor(ILI9341_GREEN);}
  tft.setCursor(40, 120);
  tft.setTextSize(10);
  tft.fillRoundRect(25, 105, 130, 100,10, ILI9341_BLACK);
  if(unsavedDifferential < 10) { tft.print(" ");}
  tft.print(unsavedDifferential);
}

void HomeMadeTech()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRoundRect(10, 10, 220, 300, 10, ILI9341_DARKCYAN);
  tft.drawLine(10,50,230,50,ILI9341_DARKCYAN);
  tft.drawLine(10,225,230,225,ILI9341_DARKCYAN);
  tft.setCursor(20, 20);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_GREEN);
  tft.print("DTC  ");
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(40,280);
  tft.println("Home Made Tech");
}
