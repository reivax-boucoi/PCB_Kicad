EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Controller:UC3843_DIP8 U1
U 1 1 62DD4E6C
P 3400 3000
F 0 "U1" H 3400 3100 50  0000 C CNN
F 1 "UC3843_DIP8" H 3400 3000 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 3400 2500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/uc3842.pdf" H 3400 3000 50  0001 C CNN
	1    3400 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 62DD55F0
P 950 1650
F 0 "J1" H 868 1325 50  0000 C CNN
F 1 "Conn_01x02" H 868 1416 50  0000 C CNN
F 2 "Connector_TE-Connectivity:TE_826576-2_1x02_P3.96mm_Vertical" H 950 1650 50  0001 C CNN
F 3 "~" H 950 1650 50  0001 C CNN
	1    950  1650
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 62DD6640
P 7150 1750
F 0 "J2" H 7068 1425 50  0000 C CNN
F 1 "Conn_01x02" H 7068 1516 50  0000 C CNN
F 2 "Connector_TE-Connectivity:TE_826576-2_1x02_P3.96mm_Vertical" H 7150 1750 50  0001 C CNN
F 3 "~" H 7150 1750 50  0001 C CNN
	1    7150 1750
	1    0    0    1   
$EndComp
$Comp
L Device:D_Schottky_AKA D3
U 1 1 62DD7787
P 5300 1650
F 0 "D3" H 5325 1425 50  0000 C CNN
F 1 "D_Schottky_AKA" H 5325 1516 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5300 1650 50  0001 C CNN
F 3 "~" H 5300 1650 50  0001 C CNN
	1    5300 1650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 62DD98EC
P 4350 2800
F 0 "R5" V 4143 2800 50  0000 C CNN
F 1 "10" V 4234 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4280 2800 50  0001 C CNN
F 3 "~" H 4350 2800 50  0001 C CNN
	1    4350 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 62DDA7FC
P 4850 3400
F 0 "R8" V 4643 3400 50  0000 C CNN
F 1 "100m" V 4734 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_Shunt_Vishay_WSR2_WSR3_KelvinConnection" V 4780 3400 50  0001 C CNN
F 3 "~" H 4850 3400 50  0001 C CNN
	1    4850 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3550 4850 3600
Wire Wire Line
	3400 3600 3400 3400
Wire Wire Line
	3900 2800 4150 2800
Wire Wire Line
	4500 2800 4550 2800
$Comp
L Device:R R6
U 1 1 62DDBC32
P 4350 3200
F 0 "R6" V 4143 3200 50  0000 C CNN
F 1 "1k" V 4234 3200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4280 3200 50  0001 C CNN
F 3 "~" H 4350 3200 50  0001 C CNN
	1    4350 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 3250 4850 3200
Wire Wire Line
	4850 3200 4500 3200
Connection ~ 4850 3200
Wire Wire Line
	4850 3200 4850 3000
$Comp
L Device:L L1
U 1 1 62DDD75E
P 4150 1650
F 0 "L1" V 4340 1650 50  0000 C CNN
F 1 "33u" V 4249 1650 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D12.5mm_P7.00mm_Fastron_09HCP" H 4150 1650 50  0001 C CNN
F 3 "~" H 4150 1650 50  0001 C CNN
	1    4150 1650
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C6
U 1 1 62DDDDEA
P 3300 1850
F 0 "C6" H 3418 1896 50  0000 L CNN
F 1 "500u" H 3418 1805 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P7.50mm" H 3338 1700 50  0001 C CNN
F 3 "~" H 3300 1850 50  0001 C CNN
	1    3300 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 62DDEF9F
P 2950 1850
F 0 "C4" H 3068 1896 50  0000 L CNN
F 1 "500u" H 3068 1805 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P7.50mm" H 2988 1700 50  0001 C CNN
F 3 "~" H 2950 1850 50  0001 C CNN
	1    2950 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 62DE0B01
P 2850 2450
F 0 "C3" H 2968 2496 50  0000 L CNN
F 1 "10u" H 2968 2405 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 2888 2300 50  0001 C CNN
F 3 "~" H 2850 2450 50  0001 C CNN
	1    2850 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C8
U 1 1 62DE16C5
P 5700 1950
F 0 "C8" H 5818 1996 50  0000 L CNN
F 1 "47u" H 5818 1905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 5738 1800 50  0001 C CNN
F 3 "~" H 5700 1950 50  0001 C CNN
	1    5700 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C9
U 1 1 62DE198E
P 6000 1950
F 0 "C9" H 6118 1996 50  0000 L CNN
F 1 "47u" H 6118 1905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 6038 1800 50  0001 C CNN
F 3 "~" H 6000 1950 50  0001 C CNN
	1    6000 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 62DE480B
P 3200 2450
F 0 "C5" H 3315 2496 50  0000 L CNN
F 1 "100n" H 3315 2405 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 3238 2300 50  0001 C CNN
F 3 "~" H 3200 2450 50  0001 C CNN
	1    3200 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 62DE4BBE
P 3650 1850
F 0 "C7" H 3765 1896 50  0000 L CNN
F 1 "100n" H 3765 1805 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 3688 1700 50  0001 C CNN
F 3 "~" H 3650 1850 50  0001 C CNN
	1    3650 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 62DE506B
P 6350 1950
F 0 "C10" H 6465 1996 50  0000 L CNN
F 1 "100n" H 6465 1905 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 6388 1800 50  0001 C CNN
F 3 "~" H 6350 1950 50  0001 C CNN
	1    6350 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3600 2750 3600
Connection ~ 3400 3600
Wire Wire Line
	1150 1650 1500 1650
Connection ~ 2950 1650
Wire Wire Line
	4300 1650 4850 1650
Wire Wire Line
	5700 1800 5700 1650
Connection ~ 5700 1650
Wire Wire Line
	5700 1650 5450 1650
Wire Wire Line
	6000 1800 6000 1650
Connection ~ 6000 1650
Wire Wire Line
	6000 1650 5700 1650
Wire Wire Line
	6350 1800 6350 1650
Wire Wire Line
	6350 1650 6000 1650
Wire Wire Line
	6350 1650 6650 1650
Wire Wire Line
	6950 1750 6950 3250
Wire Wire Line
	5100 1750 5000 1750
Wire Wire Line
	5000 1750 5000 1650
Connection ~ 5000 1650
Wire Wire Line
	5000 1650 5100 1650
Connection ~ 4850 1650
Wire Wire Line
	4850 1650 5000 1650
Wire Wire Line
	2950 1700 2950 1650
Wire Wire Line
	2950 1650 3300 1650
Wire Wire Line
	3300 1700 3300 1650
Connection ~ 3300 1650
Wire Wire Line
	3300 1650 3650 1650
Wire Wire Line
	3650 1700 3650 1650
Connection ~ 3650 1650
Wire Wire Line
	3650 1650 4000 1650
Wire Wire Line
	2850 2300 3200 2300
Wire Wire Line
	3400 2300 3400 2600
Connection ~ 3200 2300
Wire Wire Line
	3200 2300 3400 2300
Wire Wire Line
	3200 2600 3200 2650
Wire Wire Line
	3200 2650 2850 2650
Wire Wire Line
	2850 2600 2850 2650
Wire Wire Line
	3650 2000 3650 2100
Wire Wire Line
	3650 2100 3300 2100
Wire Wire Line
	2950 2000 2950 2100
Connection ~ 3300 2100
Wire Wire Line
	3300 2100 2950 2100
Wire Wire Line
	3300 2000 3300 2100
Text Label 2550 1650 0    50   ~ 0
Vin
Text Label 4600 1650 0    50   ~ 0
Vsw
Text Label 6100 1650 0    50   ~ 0
Vout
Wire Wire Line
	4850 1650 4850 2600
Text Label 4850 3200 0    50   ~ 0
CS
Text Label 4000 3200 0    50   ~ 0
CS_flt
Text Label 4550 2800 1    50   ~ 0
Gate_M
Text Label 3900 2800 0    50   ~ 0
Gate_IC
Text Label 3400 2300 0    50   ~ 0
Vin
Text Label 5200 3600 0    50   ~ 0
GND
$Comp
L Device:C C1
U 1 1 62E2848B
P 1950 3450
F 0 "C1" H 1700 3500 50  0000 L CNN
F 1 "100n" H 1650 3400 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 1988 3300 50  0001 C CNN
F 3 "~" H 1950 3450 50  0001 C CNN
	1    1950 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3100 2500 3100
Wire Wire Line
	1950 3100 1950 3250
$Comp
L Device:C C2
U 1 1 62E33AAF
P 2750 3450
F 0 "C2" H 2865 3496 50  0000 L CNN
F 1 "1n5" H 2865 3405 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 2788 3300 50  0001 C CNN
F 3 "~" H 2750 3450 50  0001 C CNN
	1    2750 3450
	1    0    0    -1  
$EndComp
Connection ~ 2750 3600
Wire Wire Line
	2750 3600 1950 3600
$Comp
L Device:R R2
U 1 1 62E3427C
P 2350 3250
F 0 "R2" V 2143 3250 50  0000 C CNN
F 1 "15k" V 2234 3250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2280 3250 50  0001 C CNN
F 3 "~" H 2350 3250 50  0001 C CNN
	1    2350 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 3250 1950 3250
Connection ~ 1950 3250
Wire Wire Line
	1950 3250 1950 3300
Wire Wire Line
	2500 3250 2750 3250
Wire Wire Line
	2750 3250 2750 3300
Wire Wire Line
	2750 3250 2750 3200
Wire Wire Line
	2750 3200 2900 3200
Connection ~ 2750 3250
$Comp
L Device:R R1
U 1 1 62E4BCD2
P 2100 2800
F 0 "R1" V 1893 2800 50  0000 C CNN
F 1 "68k" V 1984 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2030 2800 50  0001 C CNN
F 3 "~" H 2100 2800 50  0001 C CNN
	1    2100 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 2800 2250 2800
$Comp
L Diode:1N4148 D1
U 1 1 62E50CF6
P 1050 2900
F 0 "D1" H 1050 2684 50  0000 C CNN
F 1 "1N4148" H 1050 2775 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1050 2725 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1050 2900 50  0001 C CNN
	1    1050 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	600  2800 1950 2800
Wire Wire Line
	600  2900 900  2900
Wire Wire Line
	600  2900 600  2800
Wire Wire Line
	1600 3100 1650 3100
Connection ~ 1950 3100
$Comp
L Device:R R11
U 1 1 62E7C44A
P 6950 3400
F 0 "R11" V 6743 3400 50  0000 C CNN
F 1 "220m" V 6834 3400 50  0000 C CNN
F 2 "Resistor_THT:R_Radial_Power_L7.0mm_W8.0mm_Px2.40mm_Py2.30mm" V 6880 3400 50  0001 C CNN
F 3 "~" H 6950 3400 50  0001 C CNN
	1    6950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 3550 6950 3600
Text Label 3550 3600 0    50   ~ 0
GND
Text Label 2900 2650 0    50   ~ 0
GND
Text Label 3050 2100 0    50   ~ 0
GND
Text Label 1150 1750 0    50   ~ 0
GND
Text Label 6950 3100 0    50   ~ 0
Load_CS
Wire Wire Line
	4850 3600 6650 3600
Wire Wire Line
	5700 2100 5700 2250
Wire Wire Line
	5700 2250 6000 2250
Wire Wire Line
	6350 2250 6350 2100
Connection ~ 6000 2250
Wire Wire Line
	6000 2250 6350 2250
Wire Wire Line
	6000 2100 6000 2250
Text Label 6050 2250 0    50   ~ 0
GND
Text Label 2750 3200 0    50   ~ 0
RtCt
Text Label 2750 3100 0    50   ~ 0
Vref
Text Label 2750 2900 0    50   ~ 0
FB
Text Label 650  2900 0    50   ~ 0
FB_OV
Text Label 2650 2800 0    50   ~ 0
COMP
Wire Wire Line
	1300 3100 1200 3100
Text Label 650  3100 0    50   ~ 0
Load_CS
$Comp
L Device:R R10
U 1 1 62EA0273
P 6650 3400
F 0 "R10" V 6443 3400 50  0000 C CNN
F 1 "2k2" V 6534 3400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6580 3400 50  0001 C CNN
F 3 "~" H 6650 3400 50  0001 C CNN
	1    6650 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 62EA1F6B
P 6650 2850
F 0 "R9" V 6443 2850 50  0000 C CNN
F 1 "26k7" V 6534 2850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6580 2850 50  0001 C CNN
F 3 "~" H 6650 2850 50  0001 C CNN
	1    6650 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3000 6650 3250
Wire Wire Line
	6650 3550 6650 3600
Connection ~ 6650 3600
Wire Wire Line
	6650 3600 6950 3600
Wire Wire Line
	6650 2700 6650 1650
Connection ~ 6650 1650
Wire Wire Line
	6650 1650 6950 1650
Connection ~ 6350 1650
Text Label 6650 3100 0    50   ~ 0
FB_OV
$Comp
L Device:D_Schottky D2
U 1 1 6330D90E
P 4350 2500
F 0 "D2" H 4350 2716 50  0000 C CNN
F 1 "D_Schottky" H 4350 2625 50  0000 C CNN
F 2 "Diode_THT:D_DO-15_P12.70mm_Horizontal" H 4350 2500 50  0001 C CNN
F 3 "~" H 4350 2500 50  0001 C CNN
	1    4350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2500 4550 2500
Wire Wire Line
	4550 2500 4550 2800
Wire Wire Line
	4150 2800 4150 2500
Wire Wire Line
	4150 2500 4200 2500
Connection ~ 4150 2800
Wire Wire Line
	4150 2800 4200 2800
Connection ~ 4550 2800
$Comp
L Device:Q_NMOS_GDS Q2
U 1 1 62DD8F41
P 4750 2800
F 0 "Q2" H 4954 2846 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 4954 2755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4950 2900 50  0001 C CNN
F 3 "~" H 4750 2800 50  0001 C CNN
	1    4750 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 63313D3A
P 4550 2950
F 0 "R7" V 4343 2950 50  0000 C CNN
F 1 "22k" V 4434 2950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4480 2950 50  0001 C CNN
F 3 "~" H 4550 2950 50  0001 C CNN
	1    4550 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 3100 4550 3600
Wire Wire Line
	3400 3600 4550 3600
Wire Wire Line
	3900 3200 4050 3200
$Comp
L Device:R R4
U 1 1 6331A5E3
P 4150 3350
F 0 "R4" V 3943 3350 50  0000 C CNN
F 1 "DNP 27k" V 4034 3350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4080 3350 50  0001 C CNN
F 3 "~" H 4150 3350 50  0001 C CNN
	1    4150 3350
	-1   0    0    1   
$EndComp
Connection ~ 4150 3200
Wire Wire Line
	4150 3200 4200 3200
$Comp
L Device:R R3
U 1 1 6331AC98
P 4050 3350
F 0 "R3" V 3843 3350 50  0000 C CNN
F 1 "10k" V 3934 3350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3980 3350 50  0001 C CNN
F 3 "~" H 4050 3350 50  0001 C CNN
	1    4050 3350
	1    0    0    -1  
$EndComp
Connection ~ 4050 3200
Wire Wire Line
	4050 3200 4150 3200
Wire Wire Line
	4150 3500 4150 3550
Wire Wire Line
	4150 3550 4400 3550
Wire Wire Line
	4050 3500 4050 3550
Wire Wire Line
	4050 3550 3800 3550
Text Label 4200 3550 0    50   ~ 0
Vref
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 63337270
P 2300 3500
F 0 "Q1" H 2491 3546 50  0000 L CNN
F 1 "BC547" H 2491 3455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2500 3425 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 2300 3500 50  0001 L CNN
	1    2300 3500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2200 3300 2200 3250
Connection ~ 2200 3250
Wire Wire Line
	2500 3500 2500 3250
Connection ~ 2500 3250
Wire Wire Line
	2200 3700 3800 3700
Wire Wire Line
	3800 3700 3800 3550
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6334EA2A
P 1500 1650
F 0 "#FLG0101" H 1500 1725 50  0001 C CNN
F 1 "PWR_FLAG" H 1500 1823 50  0000 C CNN
F 2 "" H 1500 1650 50  0001 C CNN
F 3 "~" H 1500 1650 50  0001 C CNN
	1    1500 1650
	1    0    0    -1  
$EndComp
Connection ~ 1500 1650
Wire Wire Line
	1500 1650 2950 1650
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 63350E2D
P 1150 1750
F 0 "#FLG0102" H 1150 1825 50  0001 C CNN
F 1 "PWR_FLAG" H 1150 1923 50  0000 C CNN
F 2 "" H 1150 1750 50  0001 C CNN
F 3 "~" H 1150 1750 50  0001 C CNN
	1    1150 1750
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 63356676
P 2500 3100
F 0 "#FLG0103" H 2500 3175 50  0001 C CNN
F 1 "PWR_FLAG" H 2500 3250 50  0000 C CNN
F 2 "" H 2500 3100 50  0001 C CNN
F 3 "~" H 2500 3100 50  0001 C CNN
	1    2500 3100
	1    0    0    -1  
$EndComp
Connection ~ 2500 3100
Wire Wire Line
	2500 3100 1950 3100
$Comp
L Device:R R12
U 1 1 63322922
P 1050 3100
F 0 "R12" V 843 3100 50  0000 C CNN
F 1 "68k" V 934 3100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 980 3100 50  0001 C CNN
F 3 "~" H 1050 3100 50  0001 C CNN
	1    1050 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	900  3100 650  3100
$Comp
L Device:R_POT RV1
U 1 1 62E5B1F6
P 1450 3100
F 0 "RV1" V 1335 3100 50  0000 C CNN
F 1 "5k" V 1244 3100 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296X_Horizontal" H 1450 3100 50  0001 C CNN
F 3 "~" H 1450 3100 50  0001 C CNN
	1    1450 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1200 2900 1450 2900
Wire Wire Line
	1450 2950 1450 2900
Connection ~ 1450 2900
Wire Wire Line
	1450 2900 2900 2900
$Comp
L Device:R R13
U 1 1 63345065
P 1800 3100
F 0 "R13" V 1593 3100 50  0000 C CNN
F 1 "80k" V 1684 3100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1730 3100 50  0001 C CNN
F 3 "~" H 1800 3100 50  0001 C CNN
	1    1800 3100
	0    1    1    0   
$EndComp
$EndSCHEMATC