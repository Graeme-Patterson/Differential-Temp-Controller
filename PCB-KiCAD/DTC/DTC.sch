EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Differential Temperature Controller"
Date "2019-05-11"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x14 J1
U 1 1 5CD65AFA
P 7200 3400
F 0 "J1" H 7280 3392 50  0000 L CNN
F 1 "Conn_01x14" H 7280 3301 50  0000 L CNN
F 2 "Connectors_Molex:Molex_KK-6410-14_14x2.54mm_Straight" H 7200 3400 50  0001 C CNN
F 3 "~" H 7200 3400 50  0001 C CNN
	1    7200 3400
	1    0    0    -1  
$EndComp
$Comp
L Relay:G5LE-1 K1
U 1 1 5CD65BD4
P 6650 2200
F 0 "K1" H 7080 2246 50  0000 L CNN
F 1 "G5LE-1" H 7080 2155 50  0000 L CNN
F 2 "Relays_ThroughHole:Relay_SPDT_OMRON-G5LE-1" H 7100 2150 50  0001 L CNN
F 3 "http://www.omron.com/ecb/products/pdf/en-g5le.pdf" H 6650 1800 50  0001 C CNN
	1    6650 2200
	1    0    0    -1  
$EndComp
$Comp
L ESP8266:NodeMCU1.0(ESP-12E) U1
U 1 1 5CD6626E
P 4450 3250
F 0 "U1" H 4450 4443 60  0000 C CNN
F 1 "NodeMCU1.0(ESP-12E)" H 4450 4337 60  0000 C CNN
F 2 "ESP8266:NodeMCU1.0(12-E)" H 4450 4231 60  0000 C CNN
F 3 "" H 3850 2400 60  0000 C CNN
	1    4450 3250
	1    0    0    -1  
$EndComp
$Comp
L dk_Barrel-Power-Connectors:PJ-102A J4
U 1 1 5CD6640D
P 3700 4600
F 0 "J4" H 3631 4825 50  0000 C CNN
F 1 "PJ-102A" H 3631 4734 50  0000 C CNN
F 2 "digikey-footprints:Barrel_Jack_5.5mmODx2.1mmID_PJ-102A" H 3900 4800 60  0001 L CNN
F 3 "https://www.cui.com/product/resource/digikeypdf/pj-102a.pdf" H 3900 4900 60  0001 L CNN
F 4 "CP-102A-ND" H 3900 5000 60  0001 L CNN "Digi-Key_PN"
F 5 "PJ-102A" H 3900 5100 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 3900 5200 60  0001 L CNN "Category"
F 7 "Barrel - Power Connectors" H 3900 5300 60  0001 L CNN "Family"
F 8 "https://www.cui.com/product/resource/digikeypdf/pj-102a.pdf" H 3900 5400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cui-inc/PJ-102A/CP-102A-ND/275425" H 3900 5500 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN PWR JACK 2X5.5MM SOLDER" H 3900 5600 60  0001 L CNN "Description"
F 11 "CUI Inc." H 3900 5700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3900 5800 60  0001 L CNN "Status"
	1    3700 4600
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4004 D3
U 1 1 5CD664FA
P 6100 2200
F 0 "D3" V 6050 2000 50  0000 L CNN
F 1 "1N4004" V 6150 1850 50  0000 L CNN
F 2 "Diodes_ThroughHole:D_DO-41_SOD81_P10.16mm_Horizontal" H 6100 2025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 6100 2200 50  0001 C CNN
	1    6100 2200
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4004 D2
U 1 1 5CD6655F
P 6550 5100
F 0 "D2" H 6550 5316 50  0000 C CNN
F 1 "1N4004" H 6550 5225 50  0000 C CNN
F 2 "Diodes_ThroughHole:D_DO-41_SOD81_P10.16mm_Horizontal" H 6550 4925 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 6550 5100 50  0001 C CNN
	1    6550 5100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4004 D1
U 1 1 5CD665E8
P 5650 5100
F 0 "D1" H 5650 4884 50  0000 C CNN
F 1 "1N4004" H 5650 4975 50  0000 C CNN
F 2 "Diodes_ThroughHole:D_DO-41_SOD81_P10.16mm_Horizontal" H 5650 4925 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5650 5100 50  0001 C CNN
	1    5650 5100
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:BC337 Q1
U 1 1 5CD6679A
P 6000 2550
F 0 "Q1" H 6200 2550 50  0000 L CNN
F 1 "BC337" H 6200 2450 50  0000 L CNN
F 2 "digikey-footprints:TO-92-3_Formed_Leads" H 6200 2475 50  0001 L CIN
F 3 "http://www.nxp.com/documents/data_sheet/BC817_BC817W_BC337.pdf" H 6000 2550 50  0001 L CNN
	1    6000 2550
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC327 Q2
U 1 1 5CD66817
P 6600 4350
F 0 "Q2" H 6791 4396 50  0000 L CNN
F 1 "BC327" H 6791 4305 50  0000 L CNN
F 2 "digikey-footprints:TO-92-3_Formed_Leads" H 6800 4275 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/BC327-D.PDF" H 6600 4350 50  0001 L CNN
	1    6600 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5CD6692C
P 5600 2550
F 0 "R1" V 5393 2550 50  0000 C CNN
F 1 "10k" V 5484 2550 50  0000 C CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5530 2550 50  0001 C CNN
F 3 "~" H 5600 2550 50  0001 C CNN
	1    5600 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5CD6699E
P 6050 4350
F 0 "R2" V 5843 4350 50  0000 C CNN
F 1 "10k" V 5934 4350 50  0000 C CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5980 4350 50  0001 C CNN
F 3 "~" H 6050 4350 50  0001 C CNN
	1    6050 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5CD669F5
P 5500 4550
F 0 "R3" H 5570 4596 50  0000 L CNN
F 1 "10k" H 5570 4505 50  0000 L CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5430 4550 50  0001 C CNN
F 3 "~" H 5500 4550 50  0001 C CNN
	1    5500 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5CD66A46
P 6700 4750
F 0 "R4" H 6770 4796 50  0000 L CNN
F 1 "10k" H 6770 4705 50  0000 L CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 6630 4750 50  0001 C CNN
F 3 "~" H 6700 4750 50  0001 C CNN
	1    6700 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5CD66AD6
P 5200 5000
F 0 "J2" H 5120 4675 50  0000 C CNN
F 1 "Conn_01x02" H 5120 4766 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 5200 5000 50  0001 C CNN
F 3 "~" H 5200 5000 50  0001 C CNN
	1    5200 5000
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5CD66B33
P 7000 4900
F 0 "J3" H 7080 4892 50  0000 L CNN
F 1 "Conn_01x02" H 7080 4801 50  0000 L CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 7000 4900 50  0001 C CNN
F 3 "~" H 7000 4900 50  0001 C CNN
	1    7000 4900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J5
U 1 1 5CD66DA2
P 7650 2200
F 0 "J5" H 7730 2242 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 7730 2151 50  0000 L CNN
F 2 "Terminal_Blocks:TerminalBlock_bornier-3_P5.08mm" H 7650 2200 50  0001 C CNN
F 3 "~" H 7650 2200 50  0001 C CNN
	1    7650 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2550 5450 2550
Wire Wire Line
	5750 2550 5800 2550
Wire Wire Line
	6100 2050 6450 2050
Wire Wire Line
	6450 2050 6450 1900
Wire Wire Line
	6850 2500 7250 2500
Wire Wire Line
	7250 2500 7250 2300
Wire Wire Line
	7250 2300 7450 2300
Wire Wire Line
	6950 1900 7200 1900
Wire Wire Line
	7200 1900 7200 2200
Wire Wire Line
	7200 2200 7450 2200
Wire Wire Line
	7450 2100 7450 1850
Wire Wire Line
	7450 1850 6750 1850
Wire Wire Line
	6750 1850 6750 1900
Wire Wire Line
	6200 4350 6400 4350
Wire Wire Line
	6700 4550 6700 4600
Wire Wire Line
	6700 4900 6700 5100
Wire Wire Line
	6700 4900 6800 4900
Connection ~ 6700 4900
Wire Wire Line
	5800 5100 6100 5100
Wire Wire Line
	5500 4700 5500 4900
Wire Wire Line
	5400 4900 5500 4900
Connection ~ 5500 4900
Wire Wire Line
	5500 4900 5500 5100
Wire Wire Line
	5900 4350 5500 4350
Wire Wire Line
	5500 4350 5500 4400
Wire Wire Line
	5250 2850 5500 2850
Wire Wire Line
	5500 2850 5500 4350
Connection ~ 5500 4350
Wire Wire Line
	3800 4700 3900 4700
Wire Wire Line
	3900 4700 3900 4300
Wire Wire Line
	3900 4300 3350 4300
Wire Wire Line
	3350 4300 3350 3950
Wire Wire Line
	3350 3950 3650 3950
Wire Wire Line
	3650 3850 3600 3850
Wire Wire Line
	3600 3850 3600 4250
Wire Wire Line
	3600 4250 4000 4250
Wire Wire Line
	4000 4250 4000 4800
Wire Wire Line
	4000 4800 3800 4800
Wire Wire Line
	4000 4800 4000 5200
Wire Wire Line
	4000 5200 5400 5200
Wire Wire Line
	5400 5200 5400 5000
Connection ~ 4000 4800
Wire Wire Line
	5400 5200 6800 5200
Wire Wire Line
	6800 5200 6800 5000
Connection ~ 5400 5200
Wire Wire Line
	5250 3950 6700 3950
Wire Wire Line
	6700 3950 6700 4100
Wire Wire Line
	5250 3150 6100 3150
Wire Wire Line
	6100 3150 6100 2750
Wire Wire Line
	3350 3950 3350 1850
Wire Wire Line
	3350 1850 6450 1850
Wire Wire Line
	6450 1850 6450 1900
Connection ~ 3350 3950
Connection ~ 6450 1900
Wire Wire Line
	3650 2550 3500 2550
Wire Wire Line
	3500 2550 3500 4200
Wire Wire Line
	3500 4200 5800 4200
Wire Wire Line
	5800 4200 5800 4750
Wire Wire Line
	5800 4750 6100 4750
Wire Wire Line
	6100 4750 6100 5100
Connection ~ 6100 5100
Wire Wire Line
	6100 5100 6400 5100
Connection ~ 6100 2350
Wire Wire Line
	6100 2350 6200 2350
Wire Wire Line
	6450 2500 6200 2500
Wire Wire Line
	6200 2500 6200 2350
Wire Wire Line
	5250 2650 5950 2650
Wire Wire Line
	5950 2650 5950 2800
Wire Wire Line
	5950 2800 7000 2800
Wire Wire Line
	5250 3350 6200 3350
Wire Wire Line
	6200 3350 6200 3300
Wire Wire Line
	6200 2900 7000 2900
Wire Wire Line
	7000 3300 6200 3300
Connection ~ 6200 3300
Wire Wire Line
	6200 3300 6200 2900
Wire Wire Line
	5250 3450 6250 3450
Wire Wire Line
	6250 3450 6250 3000
Wire Wire Line
	6250 3000 7000 3000
Wire Wire Line
	7000 3100 5900 3100
Wire Wire Line
	5900 3100 5900 2750
Wire Wire Line
	5900 2750 5250 2750
Wire Wire Line
	5250 3250 5600 3250
Wire Wire Line
	5600 3250 5600 3200
Wire Wire Line
	5600 3200 6500 3200
Wire Wire Line
	7000 3500 6500 3500
Wire Wire Line
	6500 3500 6500 3200
Connection ~ 6500 3200
Wire Wire Line
	6500 3200 7000 3200
Wire Wire Line
	7000 3400 6700 3400
Wire Wire Line
	6700 3400 6700 3800
Connection ~ 6700 3950
Wire Wire Line
	7000 4100 6700 4100
Connection ~ 6700 4100
Wire Wire Line
	6700 4100 6700 4150
Wire Wire Line
	7000 3800 6700 3800
Connection ~ 6700 3800
Wire Wire Line
	6700 3800 6700 3950
Wire Wire Line
	7000 3600 6250 3600
Wire Wire Line
	6250 3600 6250 3450
Connection ~ 6250 3450
Wire Wire Line
	7000 3700 5850 3700
Wire Wire Line
	5850 3700 5850 2950
Wire Wire Line
	5850 2950 5250 2950
Wire Wire Line
	5250 3550 6200 3550
Wire Wire Line
	6200 3550 6200 3900
Wire Wire Line
	6200 3900 7000 3900
Wire Wire Line
	7000 4000 5400 4000
Wire Wire Line
	5400 4000 5400 3850
Wire Wire Line
	5400 3850 5250 3850
$EndSCHEMATC
