EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "DCM Flyback"
Date "2021-07-01"
Rev "A"
Comp "NXP Toulouse"
Comment1 "Xavier Bourlot"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+12V #PWR01
U 1 1 60DFB73C
P 1600 2100
F 0 "#PWR01" H 1600 1950 50  0001 C CNN
F 1 "+12V" H 1615 2273 50  0000 C CNN
F 2 "" H 1600 2100 50  0001 C CNN
F 3 "" H 1600 2100 50  0001 C CNN
	1    1600 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 60E06B6E
P 4300 2350
F 0 "C9" H 4415 2396 50  0000 L CNN
F 1 "100n" H 4415 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4338 2200 50  0001 C CNN
F 3 "~" H 4300 2350 50  0001 C CNN
	1    4300 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 60E07B20
P 3900 2350
F 0 "C6" H 4015 2396 50  0000 L CNN
F 1 "2.2u" H 4015 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3938 2200 50  0001 C CNN
F 3 "~" H 3900 2350 50  0001 C CNN
	1    3900 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 60E09D27
P 3500 2350
F 0 "C5" H 3615 2396 50  0000 L CNN
F 1 "2.2u" H 3615 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3538 2200 50  0001 C CNN
F 3 "~" H 3500 2350 50  0001 C CNN
	1    3500 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 60E0A97F
P 3150 2350
F 0 "C4" H 3268 2396 50  0000 L CNN
F 1 "10u" H 3268 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3188 2200 50  0001 C CNN
F 3 "~" H 3150 2350 50  0001 C CNN
	1    3150 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 60E0B57E
P 2750 2350
F 0 "C3" H 2868 2396 50  0000 L CNN
F 1 "10u" H 2868 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2788 2200 50  0001 C CNN
F 3 "~" H 2750 2350 50  0001 C CNN
	1    2750 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:Ferrite_Bead FB1
U 1 1 60E1881F
P 2350 2200
F 0 "FB1" V 2076 2200 50  0000 C CNN
F 1 "Ferrite_Bead" V 2167 2200 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric" V 2280 2200 50  0001 C CNN
F 3 "~" H 2350 2200 50  0001 C CNN
	1    2350 2200
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 60E20073
P 1600 2350
F 0 "C1" H 1715 2396 50  0000 L CNN
F 1 "100n" H 1715 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1638 2200 50  0001 C CNN
F 3 "~" H 1600 2350 50  0001 C CNN
	1    1600 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2200 2750 2200
Connection ~ 2750 2200
Wire Wire Line
	2750 2200 3150 2200
Connection ~ 3150 2200
Wire Wire Line
	3150 2200 3500 2200
Connection ~ 3500 2200
Wire Wire Line
	3500 2200 3900 2200
Connection ~ 3900 2200
Wire Wire Line
	3900 2200 4300 2200
Wire Wire Line
	4300 2500 3900 2500
Connection ~ 2750 2500
Connection ~ 3150 2500
Wire Wire Line
	3150 2500 2750 2500
Connection ~ 3500 2500
Wire Wire Line
	3500 2500 3150 2500
Connection ~ 3900 2500
Wire Wire Line
	3900 2500 3500 2500
Wire Wire Line
	1600 2100 1600 2200
Connection ~ 1600 2200
$Comp
L power:+12P #PWR04
U 1 1 60E28347
P 4300 2100
F 0 "#PWR04" H 4300 1950 50  0001 C CNN
F 1 "+12P" H 4315 2273 50  0000 C CNN
F 2 "" H 4300 2100 50  0001 C CNN
F 3 "" H 4300 2100 50  0001 C CNN
	1    4300 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2100 4300 2200
Connection ~ 4300 2200
$Comp
L Device:D_Schottky_ALT D3
U 1 1 60E2F8CA
P 7650 1850
F 0 "D3" H 7650 1634 50  0000 C CNN
F 1 "D_Schottky_ALT" H 7650 1725 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 7650 1850 50  0001 C CNN
F 3 "~" H 7650 1850 50  0001 C CNN
	1    7650 1850
	-1   0    0    1   
$EndComp
$Comp
L Device:C C10
U 1 1 60E33D29
P 7800 2150
F 0 "C10" V 8050 2150 50  0000 C CNN
F 1 "22p DNP" V 7950 2150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7838 2000 50  0001 C CNN
F 3 "~" H 7800 2150 50  0001 C CNN
	1    7800 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 2150 7350 1850
Wire Wire Line
	7350 1850 7500 1850
Wire Wire Line
	7800 1850 7950 1850
Wire Wire Line
	7950 1850 7950 2150
$Comp
L Device:CP C14
U 1 1 60E413EC
P 8500 2350
F 0 "C14" H 8618 2396 50  0000 L CNN
F 1 "10u" H 8618 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8538 2200 50  0001 C CNN
F 3 "~" H 8500 2350 50  0001 C CNN
	1    8500 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C16
U 1 1 60E41C23
P 8900 2350
F 0 "C16" H 9018 2396 50  0000 L CNN
F 1 "10u" H 9018 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8938 2200 50  0001 C CNN
F 3 "~" H 8900 2350 50  0001 C CNN
	1    8900 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 1850 8150 1850
Wire Wire Line
	8500 1850 8500 2200
Connection ~ 7950 1850
Wire Wire Line
	8900 2200 8900 1850
Wire Wire Line
	8900 1850 8500 1850
$Comp
L Device:R_US R7
U 1 1 60E33101
P 7500 2150
F 0 "R7" V 7300 2200 50  0000 C CNN
F 1 "100 DNP" V 7400 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7540 2140 50  0001 C CNN
F 3 "~" H 7500 2150 50  0001 C CNN
	1    7500 2150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R9
U 1 1 60E4C2F1
P 9300 2350
F 0 "R9" H 9150 2300 50  0000 C CNN
F 1 "10k" H 9150 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9340 2340 50  0001 C CNN
F 3 "~" H 9300 2350 50  0001 C CNN
	1    9300 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	9300 2200 9300 1850
Wire Wire Line
	9300 1850 8900 1850
Connection ~ 8900 1850
Wire Wire Line
	9300 2500 9300 2800
Wire Wire Line
	8500 2500 8500 2800
Wire Wire Line
	8500 2800 8900 2800
Wire Wire Line
	8900 2500 8900 2800
$Comp
L Device:CP C12
U 1 1 60E51E18
P 8150 2350
F 0 "C12" H 8268 2396 50  0000 L CNN
F 1 "22u" H 8268 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 8188 2200 50  0001 C CNN
F 3 "~" H 8150 2350 50  0001 C CNN
	1    8150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 2200 8150 1850
Wire Wire Line
	8150 2500 8150 2800
$Comp
L Device:D_Zener_ALT D7
U 1 1 60E555DB
P 9700 2300
F 0 "D7" V 9654 2379 50  0000 L CNN
F 1 "24V" V 9745 2379 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 9700 2300 50  0001 C CNN
F 3 "~" H 9700 2300 50  0001 C CNN
	1    9700 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	9700 2150 9700 1850
Wire Wire Line
	9700 1850 9300 1850
Connection ~ 9300 1850
Wire Wire Line
	9700 2450 9700 2800
Wire Wire Line
	9700 2800 9300 2800
$Comp
L Device:D_Zener_ALT D5
U 1 1 60E59651
P 9300 2950
F 0 "D5" V 9254 3029 50  0000 L CNN
F 1 "3.9V" V 9345 3029 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 9300 2950 50  0001 C CNN
F 3 "~" H 9300 2950 50  0001 C CNN
	1    9300 2950
	0    1    1    0   
$EndComp
Connection ~ 9300 2800
Wire Wire Line
	9300 3100 8900 3100
Wire Wire Line
	8900 3100 8900 2800
Connection ~ 8900 2800
$Comp
L Device:C C18
U 1 1 60E5EBAA
P 10050 2300
F 0 "C18" H 10165 2346 50  0000 L CNN
F 1 "4.7u" H 10165 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10088 2150 50  0001 C CNN
F 3 "~" H 10050 2300 50  0001 C CNN
	1    10050 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 60E60E77
P 10050 2950
F 0 "C19" H 10165 2996 50  0000 L CNN
F 1 "10u" H 10165 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10088 2800 50  0001 C CNN
F 3 "~" H 10050 2950 50  0001 C CNN
	1    10050 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 3100 9300 3100
Connection ~ 9300 3100
Wire Wire Line
	10050 2800 9700 2800
Connection ~ 9700 2800
Wire Wire Line
	10050 2450 10050 2800
Connection ~ 10050 2800
Wire Wire Line
	10050 2150 10050 1850
Wire Wire Line
	10050 1850 9700 1850
Connection ~ 9700 1850
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 60E6EC13
P 10600 2800
F 0 "J3" H 10680 2842 50  0000 L CNN
F 1 "Aux HS" H 10680 2751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 10600 2800 50  0001 C CNN
F 3 "~" H 10600 2800 50  0001 C CNN
	1    10600 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 2800 10050 2800
Wire Wire Line
	10050 3100 10400 3100
Wire Wire Line
	10400 3100 10400 2900
Connection ~ 10050 3100
Wire Wire Line
	10400 2700 10400 1850
Wire Wire Line
	10400 1850 10050 1850
Connection ~ 10050 1850
Text Label 10400 1850 0    50   ~ 0
VCCH
Text Label 10400 3100 0    50   ~ 0
VEEH
Text Label 9300 2800 0    50   ~ 0
GNDH
$Comp
L Device:Ferrite_Bead FB2
U 1 1 60E78EC4
P 8300 1850
F 0 "FB2" V 8026 1850 50  0000 C CNN
F 1 "Ferrite_Bead" V 8117 1850 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 8230 1850 50  0001 C CNN
F 3 "~" H 8300 1850 50  0001 C CNN
	1    8300 1850
	0    1    1    0   
$EndComp
Connection ~ 8150 1850
Wire Wire Line
	8450 1850 8500 1850
Connection ~ 8500 1850
$Comp
L Device:Ferrite_Bead FB3
U 1 1 60E7BCC2
P 8300 2800
F 0 "FB3" V 8026 2800 50  0000 C CNN
F 1 "Ferrite_Bead" V 8117 2800 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 8230 2800 50  0001 C CNN
F 3 "~" H 8300 2800 50  0001 C CNN
	1    8300 2800
	0    1    1    0   
$EndComp
Connection ~ 8150 2800
Wire Wire Line
	8450 2800 8500 2800
Connection ~ 8500 2800
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 60E8AF8D
P 1050 2400
F 0 "J1" H 968 2075 50  0000 C CNN
F 1 "VSUP" H 968 2166 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1050 2400 50  0001 C CNN
F 3 "~" H 1050 2400 50  0001 C CNN
	1    1050 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	1250 2400 1250 2500
Wire Wire Line
	1250 2500 1600 2500
Connection ~ 1600 2500
Wire Wire Line
	1600 2200 1250 2200
Wire Wire Line
	1250 2200 1250 2300
$Comp
L _MYLIBRARY:YA9036-ALD T1
U 1 1 60E9B7FD
P 6850 2550
F 0 "T1" H 6850 2981 50  0000 C CNN
F 1 "YA9036-ALD" H 6850 2890 50  0000 C CNN
F 2 "footprints:YA9036-ALD" H 6850 2550 50  0001 C CNN
F 3 "~" H 6850 2550 50  0001 C CNN
	1    6850 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2750 7150 2800
Wire Wire Line
	7150 2800 8150 2800
Connection ~ 7150 2800
Wire Wire Line
	7150 2350 7150 2300
Wire Wire Line
	7150 1850 7350 1850
Connection ~ 7150 2300
Wire Wire Line
	7150 2300 7150 1850
Connection ~ 7350 1850
$Comp
L power:+12P #PWR05
U 1 1 60EA7C9F
P 6350 2350
F 0 "#PWR05" H 6350 2200 50  0001 C CNN
F 1 "+12P" H 6365 2523 50  0000 C CNN
F 2 "" H 6350 2350 50  0001 C CNN
F 3 "" H 6350 2350 50  0001 C CNN
	1    6350 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2350 6550 2350
Wire Wire Line
	1600 2500 2050 2500
Connection ~ 2050 2500
Wire Wire Line
	2050 2500 2750 2500
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 60F734D7
P 5000 7100
F 0 "H1" H 5100 7103 50  0000 L CNN
F 1 "MountingHole_Pad" H 5100 7058 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5000 7100 50  0001 C CNN
F 3 "~" H 5000 7100 50  0001 C CNN
	1    5000 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 60F76F18
P 5600 7100
F 0 "H2" H 5700 7103 50  0000 L CNN
F 1 "MountingHole_Pad" H 5700 7058 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5600 7100 50  0001 C CNN
F 3 "~" H 5600 7100 50  0001 C CNN
	1    5600 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 60F77254
P 4650 7100
F 0 "H3" H 4750 7103 50  0000 L CNN
F 1 "MountingHole_Pad" H 4750 7058 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 4650 7100 50  0001 C CNN
F 3 "~" H 4650 7100 50  0001 C CNN
	1    4650 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 60F773FD
P 5900 7100
F 0 "H4" H 6000 7103 50  0000 L CNN
F 1 "MountingHole_Pad" H 6000 7058 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5900 7100 50  0001 C CNN
F 3 "~" H 5900 7100 50  0001 C CNN
	1    5900 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 7200 5750 7200
$Comp
L power:GND #PWR07
U 1 1 60F7CBE2
P 5750 7200
F 0 "#PWR07" H 5750 6950 50  0001 C CNN
F 1 "GND" H 5755 7027 50  0000 C CNN
F 2 "" H 5750 7200 50  0001 C CNN
F 3 "" H 5750 7200 50  0001 C CNN
	1    5750 7200
	1    0    0    -1  
$EndComp
Connection ~ 5750 7200
Wire Wire Line
	5750 7200 5900 7200
Wire Wire Line
	4650 7200 4650 7300
Wire Wire Line
	5000 7200 5000 7300
Text Label 5000 7300 0    50   ~ 0
GNDL
Text Label 4650 7300 0    50   ~ 0
GNDH
$Comp
L power:GND #PWR0101
U 1 1 60FB9A1B
P 2050 2500
F 0 "#PWR0101" H 2050 2250 50  0001 C CNN
F 1 "GND" H 2055 2327 50  0000 C CNN
F 2 "" H 2050 2500 50  0001 C CNN
F 3 "" H 2050 2500 50  0001 C CNN
	1    2050 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2200 2200 2200
Wire Wire Line
	5750 2750 6550 2750
Wire Notes Line
	6700 6450 6800 6450
Wire Notes Line
	6800 3350 11150 3350
Wire Notes Line
	11150 3350 11150 3250
Wire Notes Line
	11150 3250 6800 3250
Wire Notes Line
	6800 3250 6800 650 
Wire Notes Line
	6800 650  6700 650 
Wire Notes Line
	6800 6450 6800 3350
Wire Notes Line
	6700 650  6700 6450
Wire Wire Line
	5750 4600 6450 4600
Connection ~ 5750 4600
Wire Wire Line
	5750 2750 5750 4600
Wire Wire Line
	4850 4600 5750 4600
$Comp
L LM25180-Q1:LM25180QNGURQ1 U1
U 1 1 60E00943
P 2800 5000
F 0 "U1" H 2800 5788 60  0000 C CNN
F 1 "LM25180QNGURQ1" H 2800 5682 60  0000 C CNN
F 2 "footprints:LM25180QNGURQ1" H 2800 4940 60  0001 C CNN
F 3 "" H 2800 5000 60  0000 C CNN
	1    2800 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4950 8800 4950
$Comp
L Device:R_US R6
U 1 1 60EB665B
P 3800 4450
F 0 "R6" H 3650 4500 50  0000 C CNN
F 1 "100 DNP" H 3600 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3840 4440 50  0001 C CNN
F 3 "~" H 3800 4450 50  0001 C CNN
	1    3800 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R5
U 1 1 60E017EF
P 3650 5000
F 0 "R5" V 3445 5000 50  0000 C CNN
F 1 "75k" V 3536 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3690 4990 50  0001 C CNN
F 3 "~" H 3650 5000 50  0001 C CNN
	1    3650 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 4400 4850 4600
Connection ~ 4850 4600
$Comp
L Connector:TestPoint TP1
U 1 1 60F4F10D
P 4850 4400
F 0 "TP1" H 4908 4518 50  0000 L CNN
F 1 "TestPoint" H 4908 4427 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5010-5014_Multipurpose" H 5050 4400 50  0001 C CNN
F 3 "~" H 5050 4400 50  0001 C CNN
	1    4850 4400
	1    0    0    -1  
$EndComp
Text Label 5700 4600 2    50   ~ 0
SW
Wire Wire Line
	6250 4200 6450 4200
$Comp
L power:+12P #PWR06
U 1 1 60F19355
P 6250 4200
F 0 "#PWR06" H 6250 4050 50  0001 C CNN
F 1 "+12P" H 6265 4373 50  0000 C CNN
F 2 "" H 6250 4200 50  0001 C CNN
F 3 "" H 6250 4200 50  0001 C CNN
	1    6250 4200
	1    0    0    -1  
$EndComp
Connection ~ 7250 3700
Wire Wire Line
	7050 4150 7050 3700
Connection ~ 7050 4150
Wire Wire Line
	7050 3700 7250 3700
Wire Wire Line
	7050 4200 7050 4150
Connection ~ 7050 4650
Wire Wire Line
	7050 4650 8050 4650
Wire Wire Line
	7050 4600 7050 4650
$Comp
L _MYLIBRARY:YA9036-ALD T2
U 1 1 60F19343
P 6750 4400
F 0 "T2" H 6750 4831 50  0000 C CNN
F 1 "YA9036-ALD" H 6750 4740 50  0000 C CNN
F 2 "footprints:YA9036-ALD" H 6750 4400 50  0001 C CNN
F 3 "~" H 6750 4400 50  0001 C CNN
	1    6750 4400
	1    0    0    -1  
$EndComp
Connection ~ 8400 4650
Wire Wire Line
	8350 4650 8400 4650
Connection ~ 8050 4650
$Comp
L Device:Ferrite_Bead FB5
U 1 1 60F19336
P 8200 4650
F 0 "FB5" V 7926 4650 50  0000 C CNN
F 1 "Ferrite_Bead" V 8017 4650 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 8130 4650 50  0001 C CNN
F 3 "~" H 8200 4650 50  0001 C CNN
	1    8200 4650
	0    1    1    0   
$EndComp
Connection ~ 8400 3700
Wire Wire Line
	8350 3700 8400 3700
Connection ~ 8050 3700
$Comp
L Device:Ferrite_Bead FB4
U 1 1 60F19329
P 8200 3700
F 0 "FB4" V 7926 3700 50  0000 C CNN
F 1 "Ferrite_Bead" V 8017 3700 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 8130 3700 50  0001 C CNN
F 3 "~" H 8200 3700 50  0001 C CNN
	1    8200 3700
	0    1    1    0   
$EndComp
Text Label 9200 4650 0    50   ~ 0
GNDL
Text Label 10300 4950 0    50   ~ 0
VEEL
Text Label 10300 3700 0    50   ~ 0
VCCL
Connection ~ 9950 3700
Wire Wire Line
	10300 3700 9950 3700
Wire Wire Line
	10300 4550 10300 3700
Connection ~ 9950 4950
Wire Wire Line
	10300 4950 10300 4750
Wire Wire Line
	9950 4950 10300 4950
Wire Wire Line
	10300 4650 9950 4650
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 60F19315
P 10500 4650
F 0 "J4" H 10580 4692 50  0000 L CNN
F 1 "Aux LS" H 10580 4601 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 10500 4650 50  0001 C CNN
F 3 "~" H 10500 4650 50  0001 C CNN
	1    10500 4650
	1    0    0    -1  
$EndComp
Connection ~ 9600 3700
Wire Wire Line
	9950 3700 9600 3700
Wire Wire Line
	9950 4000 9950 3700
Connection ~ 9950 4650
Wire Wire Line
	9950 4300 9950 4650
Connection ~ 9600 4650
Wire Wire Line
	9950 4650 9600 4650
Connection ~ 9200 4950
Wire Wire Line
	9950 4950 9200 4950
$Comp
L Device:C C21
U 1 1 60F19302
P 9950 4800
F 0 "C21" H 10065 4846 50  0000 L CNN
F 1 "10u" H 10065 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9988 4650 50  0001 C CNN
F 3 "~" H 9950 4800 50  0001 C CNN
	1    9950 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C20
U 1 1 60F192F8
P 9950 4150
F 0 "C20" H 10065 4196 50  0000 L CNN
F 1 "4.7u" H 10065 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9988 4000 50  0001 C CNN
F 3 "~" H 9950 4150 50  0001 C CNN
	1    9950 4150
	1    0    0    -1  
$EndComp
Connection ~ 8800 4650
Wire Wire Line
	8800 4950 8800 4650
Connection ~ 9200 4650
$Comp
L Device:D_Zener_ALT D6
U 1 1 60F192EA
P 9200 4800
F 0 "D6" V 9154 4879 50  0000 L CNN
F 1 "3.9V" V 9245 4879 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 9200 4800 50  0001 C CNN
F 3 "~" H 9200 4800 50  0001 C CNN
	1    9200 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 4650 9200 4650
Wire Wire Line
	9600 4300 9600 4650
Connection ~ 9200 3700
Wire Wire Line
	9600 3700 9200 3700
Wire Wire Line
	9600 4000 9600 3700
$Comp
L Device:D_Zener_ALT D8
U 1 1 60F192DB
P 9600 4150
F 0 "D8" V 9554 4229 50  0000 L CNN
F 1 "24V" V 9645 4229 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 9600 4150 50  0001 C CNN
F 3 "~" H 9600 4150 50  0001 C CNN
	1    9600 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	8050 4350 8050 4650
Wire Wire Line
	8050 4050 8050 3700
$Comp
L Device:CP C13
U 1 1 60F192CF
P 8050 4200
F 0 "C13" H 8168 4246 50  0000 L CNN
F 1 "22u" H 8168 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 8088 4050 50  0001 C CNN
F 3 "~" H 8050 4200 50  0001 C CNN
	1    8050 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 4350 8800 4650
Wire Wire Line
	8400 4650 8800 4650
Wire Wire Line
	8400 4350 8400 4650
Wire Wire Line
	9200 4350 9200 4650
Connection ~ 8800 3700
Wire Wire Line
	9200 3700 8800 3700
Wire Wire Line
	9200 4050 9200 3700
$Comp
L Device:R_US R10
U 1 1 60F192BE
P 9200 4200
F 0 "R10" H 9050 4150 50  0000 C CNN
F 1 "10k" H 9050 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9240 4190 50  0001 C CNN
F 3 "~" H 9200 4200 50  0001 C CNN
	1    9200 4200
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R8
U 1 1 60F192B4
P 7400 4000
F 0 "R8" V 7200 4050 50  0000 C CNN
F 1 "100 DNP" V 7300 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7440 3990 50  0001 C CNN
F 3 "~" H 7400 4000 50  0001 C CNN
	1    7400 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8800 3700 8400 3700
Wire Wire Line
	8800 4050 8800 3700
Connection ~ 7850 3700
Wire Wire Line
	8400 3700 8400 4050
Wire Wire Line
	7850 3700 8050 3700
$Comp
L Device:CP C17
U 1 1 60F192A5
P 8800 4200
F 0 "C17" H 8918 4246 50  0000 L CNN
F 1 "10u" H 8918 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8838 4050 50  0001 C CNN
F 3 "~" H 8800 4200 50  0001 C CNN
	1    8800 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C15
U 1 1 60F1929B
P 8400 4200
F 0 "C15" H 8518 4246 50  0000 L CNN
F 1 "10u" H 8518 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8438 4050 50  0001 C CNN
F 3 "~" H 8400 4200 50  0001 C CNN
	1    8400 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 3700 7850 4000
Wire Wire Line
	7700 3700 7850 3700
Wire Wire Line
	7250 3700 7400 3700
Wire Wire Line
	7250 4000 7250 3700
$Comp
L Device:C C11
U 1 1 60F1928D
P 7700 4000
F 0 "C11" V 7950 4000 50  0000 C CNN
F 1 "22p DNP" V 7850 4000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7738 3850 50  0001 C CNN
F 3 "~" H 7700 4000 50  0001 C CNN
	1    7700 4000
	0    1    1    0   
$EndComp
$Comp
L Device:D_Schottky_ALT D4
U 1 1 60F19283
P 7550 3700
F 0 "D4" H 7550 3484 50  0000 C CNN
F 1 "D_Schottky_ALT" H 7550 3575 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 7550 3700 50  0001 C CNN
F 3 "~" H 7550 3700 50  0001 C CNN
	1    7550 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 4000 2100 4000
Connection ~ 3800 4000
$Comp
L Device:C C7
U 1 1 60EB70D0
P 3800 4150
F 0 "C7" H 4000 4050 50  0000 C CNN
F 1 "22p DNP" H 4100 4150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3838 4000 50  0001 C CNN
F 3 "~" H 3800 4150 50  0001 C CNN
	1    3800 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 4600 4050 4600
Connection ~ 3800 4600
Connection ~ 4500 4600
Wire Wire Line
	4500 4600 4850 4600
Wire Wire Line
	4350 4600 4500 4600
Connection ~ 4350 4600
Wire Wire Line
	4350 4750 4350 4600
Connection ~ 2100 4000
Wire Wire Line
	4050 4000 3800 4000
Wire Wire Line
	4050 4600 4350 4600
Connection ~ 4050 4600
$Comp
L Device:D_ALT D2
U 1 1 60E2D090
P 4050 4450
F 0 "D2" V 4004 4529 50  0000 L CNN
F 1 "D_ALT" V 4095 4529 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 4050 4450 50  0001 C CNN
F 3 "~" H 4050 4450 50  0001 C CNN
	1    4050 4450
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener_ALT D1
U 1 1 60E2C5DC
P 4050 4150
F 0 "D1" V 4096 4071 50  0000 R CNN
F 1 "30V" V 4005 4071 50  0000 R CNN
F 2 "Diode_SMD:D_SMA" H 4050 4150 50  0001 C CNN
F 3 "~" H 4050 4150 50  0001 C CNN
	1    4050 4150
	0    -1   -1   0   
$EndComp
$Comp
L power:+12P #PWR02
U 1 1 60E28B59
P 1700 3850
F 0 "#PWR02" H 1700 3700 50  0001 C CNN
F 1 "+12P" H 1715 4023 50  0000 C CNN
F 2 "" H 1700 3850 50  0001 C CNN
F 3 "" H 1700 3850 50  0001 C CNN
	1    1700 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 4000 2100 4000
Connection ~ 1700 4000
Wire Wire Line
	1700 4000 1700 3850
Connection ~ 3500 5800
Wire Wire Line
	3800 5800 3500 5800
Wire Wire Line
	3800 5500 3800 5800
Wire Wire Line
	3500 5200 3800 5200
$Comp
L Device:C C8
U 1 1 60E05BB3
P 3800 5350
F 0 "C8" H 3915 5396 50  0000 L CNN
F 1 "47n DNP" H 3915 5305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3838 5200 50  0001 C CNN
F 3 "~" H 3800 5350 50  0001 C CNN
	1    3800 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 5400 1300 5050
Wire Wire Line
	1050 5400 1300 5400
Connection ~ 1450 5800
Wire Wire Line
	1050 5800 1450 5800
Wire Wire Line
	1050 5500 1050 5800
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 60E03542
P 850 5500
F 0 "J2" H 768 5175 50  0000 C CNN
F 1 "EN_PS" H 768 5266 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 850 5500 50  0001 C CNN
F 3 "~" H 850 5500 50  0001 C CNN
	1    850  5500
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 5000 4500 4900
Wire Wire Line
	3800 5000 4500 5000
Wire Wire Line
	3500 4600 3800 4600
Connection ~ 3500 5500
Wire Wire Line
	3500 5400 3500 5500
Wire Wire Line
	3500 5500 3500 5800
Wire Wire Line
	2850 5800 3500 5800
Connection ~ 2850 5800
$Comp
L power:GND #PWR03
U 1 1 60DFBE9B
P 2850 5800
F 0 "#PWR03" H 2850 5550 50  0001 C CNN
F 1 "GND" H 2855 5627 50  0000 C CNN
F 2 "" H 2850 5800 50  0001 C CNN
F 3 "" H 2850 5800 50  0001 C CNN
	1    2850 5800
	1    0    0    -1  
$EndComp
Connection ~ 1800 5800
Wire Wire Line
	1800 5800 2850 5800
Wire Wire Line
	1800 5800 1800 5700
Wire Wire Line
	1450 5800 1800 5800
Wire Wire Line
	1450 5700 1450 5800
Connection ~ 1450 4800
Wire Wire Line
	1450 5400 1450 4800
Wire Wire Line
	2100 4000 2100 4600
Wire Wire Line
	1300 4000 1700 4000
Wire Wire Line
	1300 4200 1300 4000
Wire Wire Line
	1450 4800 2100 4800
Wire Wire Line
	1300 4500 1300 4550
$Comp
L Jumper:Jumper_3_Bridged12 JP1
U 1 1 60DF4993
P 1300 4800
F 0 "JP1" V 1254 4867 50  0000 L CNN
F 1 "PS_EN" V 1345 4867 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged12_RoundedPad1.0x1.5mm" H 1300 4800 50  0001 C CNN
F 3 "~" H 1300 4800 50  0001 C CNN
	1    1300 4800
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R1
U 1 1 60DF3B9B
P 1300 4350
F 0 "R1" H 1368 4396 50  0000 L CNN
F 1 "390k" H 1368 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1340 4340 50  0001 C CNN
F 3 "~" H 1300 4350 50  0001 C CNN
	1    1300 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 60DF369D
P 1450 5550
F 0 "R2" H 1518 5596 50  0000 L CNN
F 1 "75k" H 1518 5505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1490 5540 50  0001 C CNN
F 3 "~" H 1450 5550 50  0001 C CNN
	1    1450 5550
	1    0    0    -1  
$EndComp
Connection ~ 1800 5400
Wire Wire Line
	1800 5400 1800 5300
Wire Wire Line
	1800 5400 2100 5400
Wire Wire Line
	1800 5000 2100 5000
$Comp
L Device:R_US R3
U 1 1 60DF2550
P 1800 5150
F 0 "R3" H 1868 5196 50  0000 L CNN
F 1 "487k DNP" H 1868 5105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1840 5140 50  0001 C CNN
F 3 "~" H 1800 5150 50  0001 C CNN
	1    1800 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV1
U 1 1 60DF1C61
P 4500 4750
F 0 "RV1" H 4432 4704 50  0000 R CNN
F 1 "100k" H 4432 4795 50  0000 R CNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_3224W_Vertical" H 4500 4750 50  0001 C CNN
F 3 "~" H 4500 4750 50  0001 C CNN
	1    4500 4750
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R4
U 1 1 60DF131B
P 1800 5550
F 0 "R4" H 1868 5596 50  0000 L CNN
F 1 "12.1k" H 1868 5505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1840 5540 50  0001 C CNN
F 3 "~" H 1800 5550 50  0001 C CNN
	1    1800 5550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
