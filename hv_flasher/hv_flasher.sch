EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "HV flasher"
Date "2021-11-02"
Rev "A"
Comp "NXP Toulouse"
Comment1 "Xavier Bourlot"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:LED D4
U 1 1 619D76CA
P 3150 4100
F 0 "D4" V 3189 3983 50  0000 R CNN
F 1 "LED" V 3098 3983 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 3150 4100 50  0001 C CNN
F 3 "~" H 3150 4100 50  0001 C CNN
	1    3150 4100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R10
U 1 1 619D82D6
P 4000 2950
F 0 "R10" H 4059 2996 50  0000 L CNN
F 1 "470k" H 4059 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 4000 2950 50  0001 C CNN
F 3 "~" H 4000 2950 50  0001 C CNN
	1    4000 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R9
U 1 1 619D87D1
P 4000 2750
F 0 "R9" H 4059 2796 50  0000 L CNN
F 1 "470k" H 4059 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 4000 2750 50  0001 C CNN
F 3 "~" H 4000 2750 50  0001 C CNN
	1    4000 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R8
U 1 1 619DAC21
P 4000 2550
F 0 "R8" H 4059 2596 50  0000 L CNN
F 1 "470k" H 4059 2505 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 4000 2550 50  0001 C CNN
F 3 "~" H 4000 2550 50  0001 C CNN
	1    4000 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R7
U 1 1 619DAC27
P 4000 2350
F 0 "R7" H 4059 2396 50  0000 L CNN
F 1 "470k" H 4059 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 4000 2350 50  0001 C CNN
F 3 "~" H 4000 2350 50  0001 C CNN
	1    4000 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R6
U 1 1 619DB759
P 4000 2150
F 0 "R6" H 4059 2196 50  0000 L CNN
F 1 "470k" H 4059 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 4000 2150 50  0001 C CNN
F 3 "~" H 4000 2150 50  0001 C CNN
	1    4000 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R5
U 1 1 619DB75F
P 4000 1950
F 0 "R5" H 4059 1996 50  0000 L CNN
F 1 "470k" H 4059 1905 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 4000 1950 50  0001 C CNN
F 3 "~" H 4000 1950 50  0001 C CNN
	1    4000 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 619DBCA6
P 4000 1650
F 0 "J2" V 3964 1562 50  0000 R CNN
F 1 "DC+" V 3873 1562 50  0000 R CNN
F 2 "TestPoint:TestPoint_THTPad_D2.5mm_Drill1.2mm" H 4000 1650 50  0001 C CNN
F 3 "~" H 4000 1650 50  0001 C CNN
	1    4000 1650
	0    -1   -1   0   
$EndComp
$Comp
L Diode:BAT54W D2
U 1 1 619DCC9C
P 2950 3650
F 0 "D2" H 2950 3425 50  0000 C CNN
F 1 "BAT54W" H 2950 3516 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2950 3475 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/BAT54W_SER.pdf" H 2950 3650 50  0001 C CNN
	1    2950 3650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 619DDE92
P 3150 3800
F 0 "R4" H 3220 3846 50  0000 L CNN
F 1 "470" H 3220 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3080 3800 50  0001 C CNN
F 3 "~" H 3150 3800 50  0001 C CNN
	1    3150 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 619DE579
P 2650 3650
F 0 "R3" V 2443 3650 50  0000 C CNN
F 1 "560k" V 2534 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2580 3650 50  0001 C CNN
F 3 "~" H 2650 3650 50  0001 C CNN
	1    2650 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 619DF003
P 2450 3950
F 0 "R2" H 2380 3904 50  0000 R CNN
F 1 "330k" H 2380 3995 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2380 3950 50  0001 C CNN
F 3 "~" H 2450 3950 50  0001 C CNN
	1    2450 3950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 619DFD87
P 2450 3250
F 0 "R1" H 2380 3204 50  0000 R CNN
F 1 "560k" H 2380 3295 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2380 3250 50  0001 C CNN
F 3 "~" H 2450 3250 50  0001 C CNN
	1    2450 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 3400 2450 3650
Wire Wire Line
	2500 3650 2450 3650
Connection ~ 2450 3650
Wire Wire Line
	2450 3650 2450 3800
Wire Wire Line
	2450 3100 2450 3050
Wire Wire Line
	2450 3050 4000 3050
Wire Wire Line
	2450 4100 2450 4300
Wire Wire Line
	3150 4300 3150 4250
Wire Wire Line
	2450 4300 3000 4300
Wire Wire Line
	3100 3650 3150 3650
Text Label 2450 3650 2    50   ~ 0
IN+
Text Label 3150 3650 0    50   ~ 0
OUT
Text Label 3050 3050 0    50   ~ 0
Vdd
Text Label 2650 4300 0    50   ~ 0
Vss
Wire Wire Line
	3650 3650 3150 3650
Connection ~ 3150 3650
Wire Wire Line
	3650 3750 3400 3750
Wire Wire Line
	3400 3750 3400 4300
Wire Wire Line
	3400 4300 3150 4300
Connection ~ 3150 4300
Wire Wire Line
	3650 3850 3450 3850
Wire Wire Line
	5850 3750 5950 3750
Wire Wire Line
	5950 3750 5950 3850
Wire Wire Line
	5950 3850 5850 3850
Wire Wire Line
	5850 3650 5850 3050
Wire Wire Line
	5850 3050 4000 3050
Connection ~ 4000 3050
Text Label 5950 3750 0    50   ~ 0
Vref
Text Label 3450 3850 0    50   ~ 0
IN+
Wire Wire Line
	1900 3850 1900 4300
Wire Wire Line
	1900 4300 2450 4300
Connection ~ 2450 4300
Wire Wire Line
	1900 3550 1900 3050
Wire Wire Line
	1900 3050 2450 3050
Connection ~ 2450 3050
$Comp
L Device:D_Zener D1
U 1 1 619EB446
P 1900 3700
F 0 "D1" V 1800 3750 50  0000 L CNN
F 1 "5V1 DNP" V 2000 3550 50  0000 L CNN
F 2 "Diode_SMD:D_MiniMELF" H 1900 3700 50  0001 C CNN
F 3 "~" H 1900 3700 50  0001 C CNN
	1    1900 3700
	0    1    1    0   
$EndComp
$Comp
L Device:LED D3
U 1 1 619EDDCD
P 3000 4100
F 0 "D3" V 3039 3983 50  0000 R CNN
F 1 "LED" V 2948 3983 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3000 4100 50  0001 C CNN
F 3 "~" H 3000 4100 50  0001 C CNN
	1    3000 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3000 4250 3000 4300
Connection ~ 3000 4300
Wire Wire Line
	3000 4300 3150 4300
Wire Wire Line
	3000 3950 3150 3950
Connection ~ 3150 3950
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 619EFF88
P 3400 4500
F 0 "J1" V 3272 4580 50  0000 L CNN
F 1 "DC-" V 3363 4580 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D2.5mm_Drill1.2mm" H 3400 4500 50  0001 C CNN
F 3 "~" H 3400 4500 50  0001 C CNN
	1    3400 4500
	0    1    1    0   
$EndComp
Connection ~ 3400 4300
$Comp
L Device:C C2
U 1 1 619F36C7
P 1650 3700
F 0 "C2" H 1500 3800 50  0000 L CNN
F 1 "DNP" H 1500 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1688 3550 50  0001 C CNN
F 3 "~" H 1650 3700 50  0001 C CNN
	1    1650 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 619F3E05
P 1400 3700
F 0 "C1" H 1200 3800 50  0000 L CNN
F 1 "10u" H 1200 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1438 3550 50  0001 C CNN
F 3 "~" H 1400 3700 50  0001 C CNN
	1    1400 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 3850 1400 4300
Wire Wire Line
	1400 4300 1650 4300
Connection ~ 1900 4300
Wire Wire Line
	1650 3850 1650 4300
Connection ~ 1650 4300
Wire Wire Line
	1650 4300 1900 4300
Wire Wire Line
	1650 3550 1650 3050
Wire Wire Line
	1650 3050 1900 3050
Connection ~ 1900 3050
Wire Wire Line
	1400 3550 1400 3050
Wire Wire Line
	1400 3050 1650 3050
Connection ~ 1650 3050
$Comp
L MCP65R41T-2402E:MCP65R41T-2402E_CHY U1
U 1 1 619FB8EA
P 3650 3650
F 0 "U1" H 4750 4037 60  0000 C CNN
F 1 "MCP65R41T-2402E_CHY" H 4750 3931 60  0000 C CNN
F 2 "footprints:MCP65R41T-2402E" H 4750 3890 60  0001 C CNN
F 3 "" H 3650 3650 60  0000 C CNN
	1    3650 3650
	1    0    0    -1  
$EndComp
Text Notes 2350 4550 0    50   ~ 0
Vh 4V\nVl 3.2V
Text Notes 4200 4200 0    50   ~ 0
Operating range 1.8V-5.5V
Text Notes 2900 4700 0    50   ~ 0
SMD/Thru\nalternative\n\nIpk=(4-1.8)/470=4.7mA
Text Notes 5950 3850 0    50   ~ 0
1.2V
Text Notes 4350 2450 0    50   ~ 0
200V max/chip
Text Notes 4350 1700 0    50   ~ 0
1300Vdc max
$EndSCHEMATC
