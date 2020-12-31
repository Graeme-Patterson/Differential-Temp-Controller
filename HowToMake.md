# How to make your DTC

You will need to gather all the required parts first.

Parts List

- 1 x ESP8266/NodeMCU/ESP12-E
- 3 x 1N4004 (or similar)  Diodes
- 1 x SRD-05VDC-SL-C SPDT 5V Relay
- 1 x DC-005 Power Supply Jack
- 2 x 10k NTC Waterproof Thermistor
- 1 x 2.8" TFT SPI LCD Touch Panel (ILI9341 240x320 5V/3.3V)
- 1 x BC337 transistor
- 1 x BC327 transistor
- 4 x 10k 1/4W MF ressitors
- 1 x 100uF 25V electrolytic capacitor
- 2 x 2 pin 0.1" pitch headers
- 1 x 14 pin 0.1" pitch header
- 1 x 3 way 0.2" pitch screw terminal
- 1 x PCB (you'll need to have this manufactured. I used JLCPCB - 5 boards for $2)

As I mentioned above, I used JLCPCB (jlcpcb.com) to have my PCB's made. They provided me with great service at an awesome $2 for 5 pcbs - double sided with solder mask and silk screened in your choice of colour.

Upload the DTCWiFiDisplay.ino sketch to your ESP8266
Assemble the PCB as shown in [PCB Component Placement](/PCB/DTC_Component_Placement.pdf)

## First Run

On first run, the ESP device will not now about your WiFi network and will go into AP mode. Use you phone/laptop etc to connect to the ESP device AP and provide your WiFi network details. Restart tye device and it should be connected to your WiFi.

After you have your DTC on your WiFi network, take a look at [Operation instructions](/Operation.md) to see how to use it.
