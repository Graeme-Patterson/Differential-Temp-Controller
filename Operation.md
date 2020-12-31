### Operation

The DTC has only 3 screens availavle on the touch screen.

1. Main screen.
2. Set differential temp screen.
3. Information screen

When you are first using the DTC, you wil need to start with the touch screen.

The main screen provides details of the temperatures of the two probes, the configured temperature difference as well as the current output status. In addition, you can access the Set screen and the Information screen.

![Main screen](/images/DTCMainScreen.png)

The Set differential temperature screen provides you the ability to adjust the temperature difference between the probes that will turn the output on. It is a simple up/down button operation with teh "Save" button saving the value to memory. As expected the "Home" button will take you back to the main screen.

![Set Differential Temperature Screen](/images/DTCChangeTemp.png)

The last screen is the Information screen. This screen provides you with easily accessible details allowing you to connect to the web interface from a browser and shows the chip Id which is used as a basic password allowing a user to configure the temperature differential from the browser. To connect to the web interface from a browser, simply type "http://\<IP Address>" into the address bar. 

![Information Screen](/images/DTCInfoScreen.png)

### Using the web interface

As I just mentioned, you will need to first obtain the IP address and Chip ID of the ESP device first and navigate to "http://\<IP Address>". Here you will be presented with a "functional" display allowing you to set the differential temperature of the controller only. 

![Web Interface](/images/WebInterface.png)

That's it. It's fairly simple and functional.

## A word of warning.

If you choose to power the external fan from 110/240V via the onboard relay, **you do so at your own risk.** While the relay is rated for this voltage and the PCB traces have adequate separation from the other traces, this voltage is dangerous and should only be attempted by suitably qualified/experienced people.
