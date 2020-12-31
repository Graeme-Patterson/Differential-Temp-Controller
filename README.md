# Differential-Temp-Controller

This is my differential temperature controller with Wi-Fi interface and Touch screen.

The idea behind this controller was to minimise the heating cost of keeping my workshop/mancave warm in Canberra Australia winters. After recently installing a solar electricity system on our house my thoughts were about how I could use the heat from the sun to warm my workshop.
The design was to heat air in long black platsic tubes mounted in a glass fronted box in a sunny location on the roof or wall of the workshop and use a low voltage fan to move air from outside, through the plastic tubes to warm the air and blow this into the workshop. To ensure that heating is achieved and to accound for any temperature drop getting the warmed air into the workshop, I needed a device that measured the temperature at the source and at the destination. I also wanted to have control over the device from inside my house and local control with visual display.

The final result uses a 2.8" ILI9341 TFT SPI display sourced from eBay (China) and an ESP8266/NodeMCU/ESP12-E device mounted on a custom PCB using a simple relay output to control a fan. Power is via a DC barrel connector (with ideas that this could be via Solar). The temperature sensors are low cost waterproof 10k NTC Thermistors, again sourced from eBay.

![DTC Pic](/Images/DTCWebSmall.png)
![DTC Interface](/Images/DTCMainScreenWebSmall.png)

[How to make one](HowToMake.md)
