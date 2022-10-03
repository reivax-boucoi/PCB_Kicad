EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Z+ HV discharge, series and meter circuit"
Date "2021-11-02"
Rev "A"
Comp "NXP Toulouse"
Comment1 "Xavier Bourlot"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R_POT RV1
U 1 1 6187DFE2
P 4300 5000
F 0 "RV1" H 4231 5046 50  0000 R CNN
F 1 "200k" H 4231 4955 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 4300 5000 50  0001 C CNN
F 3 "~" H 4300 5000 50  0001 C CNN
	1    4300 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6187E586
P 3200 3050
F 0 "R3" V 2993 3050 50  0000 C CNN
F 1 "2k2" V 3084 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0614_L14.3mm_D5.7mm_P20.32mm_Horizontal" V 3130 3050 50  0001 C CNN
F 3 "~" H 3200 3050 50  0001 C CNN
	1    3200 3050
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D3
U 1 1 6187F216
P 3200 3450
F 0 "D3" H 3200 3234 50  0000 C CNN
F 1 "1N4007" H 3200 3325 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3200 3275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3200 3450 50  0001 C CNN
	1    3200 3450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 618804FA
P 3500 3050
F 0 "R5" V 3293 3050 50  0000 C CNN
F 1 "2k2" V 3384 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0614_L14.3mm_D5.7mm_P20.32mm_Horizontal" V 3430 3050 50  0001 C CNN
F 3 "~" H 3500 3050 50  0001 C CNN
	1    3500 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 61880B2B
P 2900 3050
F 0 "R1" V 2693 3050 50  0000 C CNN
F 1 "2k2" V 2784 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0614_L14.3mm_D5.7mm_P20.32mm_Horizontal" V 2830 3050 50  0001 C CNN
F 3 "~" H 2900 3050 50  0001 C CNN
	1    2900 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 3450 3050 3450
Wire Wire Line
	3350 3450 3650 3450
Wire Wire Line
	3650 3450 3650 3050
Connection ~ 2750 3450
$Comp
L Diode:1N4007 D1
U 1 1 618815D1
P 2750 3600
F 0 "D1" V 2704 3679 50  0000 L CNN
F 1 "1N4007" V 2795 3679 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2750 3425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2750 3600 50  0001 C CNN
	1    2750 3600
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D2
U 1 1 6188292C
P 2750 5050
F 0 "D2" V 2704 5129 50  0000 L CNN
F 1 "1N4007" V 2795 5129 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2750 4875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2750 5050 50  0001 C CNN
	1    2750 5050
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D4
U 1 1 6188303B
P 3200 5200
F 0 "D4" H 3250 5100 50  0000 R CNN
F 1 "1N4007" H 3350 5000 50  0000 R CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3200 5025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3200 5200 50  0001 C CNN
	1    3200 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 5200 2750 5200
Wire Wire Line
	2750 3450 2500 3450
Wire Wire Line
	2750 5200 2500 5200
Connection ~ 2750 5200
$Comp
L Device:R R4
U 1 1 6188A844
P 3200 5600
F 0 "R4" V 2993 5600 50  0000 C CNN
F 1 "2k2" V 3084 5600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0614_L14.3mm_D5.7mm_P20.32mm_Horizontal" V 3130 5600 50  0001 C CNN
F 3 "~" H 3200 5600 50  0001 C CNN
	1    3200 5600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 6188A84A
P 2900 5600
F 0 "R2" V 2693 5600 50  0000 C CNN
F 1 "2k2" V 2784 5600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0614_L14.3mm_D5.7mm_P20.32mm_Horizontal" V 2830 5600 50  0001 C CNN
F 3 "~" H 2900 5600 50  0001 C CNN
	1    2900 5600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 6188A850
P 3500 5600
F 0 "R6" V 3293 5600 50  0000 C CNN
F 1 "2k2" V 3384 5600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0614_L14.3mm_D5.7mm_P20.32mm_Horizontal" V 3430 5600 50  0001 C CNN
F 3 "~" H 3500 5600 50  0001 C CNN
	1    3500 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3650 5600 3650 5200
Wire Wire Line
	2750 5200 2750 5250
Wire Wire Line
	3350 5200 3650 5200
$Comp
L Device:R R12
U 1 1 6188C341
P 4300 4700
F 0 "R12" H 4370 4746 50  0000 L CNN
F 1 "2M" H 4370 4655 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4230 4700 50  0001 C CNN
F 3 "~" H 4300 4700 50  0001 C CNN
	1    4300 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 6188C839
P 4300 4400
F 0 "R11" H 4370 4446 50  0000 L CNN
F 1 "2M" H 4370 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4230 4400 50  0001 C CNN
F 3 "~" H 4300 4400 50  0001 C CNN
	1    4300 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 6188CD12
P 4300 4100
F 0 "R10" H 4370 4146 50  0000 L CNN
F 1 "2M" H 4370 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4230 4100 50  0001 C CNN
F 3 "~" H 4300 4100 50  0001 C CNN
	1    4300 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 6188ED69
P 4300 3800
F 0 "R9" H 4370 3846 50  0000 L CNN
F 1 "2M" H 4370 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4230 3800 50  0001 C CNN
F 3 "~" H 4300 3800 50  0001 C CNN
	1    4300 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 6188ED6F
P 4300 3500
F 0 "R8" H 4370 3546 50  0000 L CNN
F 1 "2M" H 4370 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4230 3500 50  0001 C CNN
F 3 "~" H 4300 3500 50  0001 C CNN
	1    4300 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 6188ED75
P 4300 3200
F 0 "R7" H 4370 3246 50  0000 L CNN
F 1 "2M" H 4370 3155 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4230 3200 50  0001 C CNN
F 3 "~" H 4300 3200 50  0001 C CNN
	1    4300 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3050 3650 3050
Connection ~ 3650 3050
Connection ~ 3650 5600
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 6198BDE5
P 2000 5200
F 0 "J4" H 1950 5000 50  0000 C CNN
F 1 "A-" H 2050 5000 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_D4.0mm_Drill2.0mm" H 2000 5200 50  0001 C CNN
F 3 "~" H 2000 5200 50  0001 C CNN
	1    2000 5200
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 6198FC05
P 2000 4650
F 0 "J2" H 1900 4850 50  0000 L CNN
F 1 "A+" H 2000 4850 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D4.0mm_Drill2.0mm" H 2000 4650 50  0001 C CNN
F 3 "~" H 2000 4650 50  0001 C CNN
	1    2000 4650
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 61994B8D
P 2000 3900
F 0 "J1" H 1950 3750 50  0000 R CNN
F 1 "B-" H 2050 3750 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_D4.0mm_Drill2.0mm" H 2000 3900 50  0001 C CNN
F 3 "~" H 2000 3900 50  0001 C CNN
	1    2000 3900
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 619952C1
P 2000 3450
F 0 "J3" H 1900 3600 50  0000 C CNN
F 1 "B+" H 2050 3600 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_D4.0mm_Drill2.0mm" H 2000 3450 50  0001 C CNN
F 3 "~" H 2000 3450 50  0001 C CNN
	1    2000 3450
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 6199894B
P 4750 3050
F 0 "J8" H 4830 3092 50  0000 L CNN
F 1 "O+" H 4830 3001 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D4.0mm_Drill2.0mm" H 4750 3050 50  0001 C CNN
F 3 "~" H 4750 3050 50  0001 C CNN
	1    4750 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3050 4300 3050
Connection ~ 4300 3050
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 6199B472
P 4650 5900
F 0 "J7" H 4730 5942 50  0000 L CNN
F 1 "O-" H 4730 5851 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D4.0mm_Drill2.0mm" H 4650 5900 50  0001 C CNN
F 3 "~" H 4650 5900 50  0001 C CNN
	1    4650 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 5600 4300 5600
Wire Wire Line
	4450 5000 4450 5150
Wire Wire Line
	4450 5150 4300 5150
$Comp
L Device:D D10
U 1 1 6199D9F8
P 4450 5350
F 0 "D10" V 4404 5429 50  0000 L CNN
F 1 "D" V 4495 5429 50  0000 L CNN
F 2 "Diode_SMD:D_MiniMELF" H 4450 5350 50  0001 C CNN
F 3 "~" H 4450 5350 50  0001 C CNN
	1    4450 5350
	0    1    1    0   
$EndComp
$Comp
L Device:D D9
U 1 1 6199E806
P 4300 5350
F 0 "D9" V 4350 5150 50  0000 L CNN
F 1 "D" V 4250 5150 50  0000 L CNN
F 2 "Diode_SMD:D_MiniMELF" H 4300 5350 50  0001 C CNN
F 3 "~" H 4300 5350 50  0001 C CNN
	1    4300 5350
	0    1    -1   0   
$EndComp
Wire Wire Line
	4300 5200 4300 5150
Connection ~ 4300 5150
Wire Wire Line
	4450 5200 4450 5150
Connection ~ 4450 5150
Wire Wire Line
	4450 5500 4450 5600
Connection ~ 4450 5600
Wire Wire Line
	4450 5600 4450 5900
Wire Wire Line
	4300 5500 4300 5600
Connection ~ 4300 5600
Wire Wire Line
	4300 5600 4450 5600
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 619A70CF
P 4650 5600
F 0 "J6" H 4730 5642 50  0000 L CNN
F 1 "M-" H 4730 5551 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D2.5mm_Drill1.2mm" H 4650 5600 50  0001 C CNN
F 3 "~" H 4650 5600 50  0001 C CNN
	1    4650 5600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 619A7443
P 4650 5150
F 0 "J5" H 4730 5192 50  0000 L CNN
F 1 "M+" H 4730 5101 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D2.5mm_Drill1.2mm" H 4650 5150 50  0001 C CNN
F 3 "~" H 4650 5150 50  0001 C CNN
	1    4650 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D7
U 1 1 619ACE79
P 2750 3250
F 0 "D7" V 2789 3133 50  0000 R CNN
F 1 "LED" V 2698 3133 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 3250 50  0001 C CNN
F 3 "~" H 2750 3250 50  0001 C CNN
	1    2750 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2750 3100 2750 3050
Wire Wire Line
	2750 3400 2750 3450
$Comp
L Device:LED D8
U 1 1 619AF353
P 2750 5400
F 0 "D8" V 2789 5283 50  0000 R CNN
F 1 "LED" V 2698 5283 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2750 5400 50  0001 C CNN
F 3 "~" H 2750 5400 50  0001 C CNN
	1    2750 5400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2750 5550 2750 5600
$Comp
L Device:D D6
U 1 1 619B2CD3
P 2500 5400
F 0 "D6" V 2454 5479 50  0000 L CNN
F 1 "D" V 2545 5479 50  0000 L CNN
F 2 "Diode_SMD:D_MiniMELF" H 2500 5400 50  0001 C CNN
F 3 "~" H 2500 5400 50  0001 C CNN
	1    2500 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 5550 2500 5600
Wire Wire Line
	2500 5600 2750 5600
Connection ~ 2750 5600
Wire Wire Line
	2500 5250 2500 5200
Connection ~ 2500 5200
Wire Wire Line
	2500 5200 2200 5200
$Comp
L Device:D D5
U 1 1 619BCB63
P 2500 3250
F 0 "D5" V 2454 3329 50  0000 L CNN
F 1 "D" V 2545 3329 50  0000 L CNN
F 2 "Diode_SMD:D_MiniMELF" H 2500 3250 50  0001 C CNN
F 3 "~" H 2500 3250 50  0001 C CNN
	1    2500 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 3450 2500 3400
Connection ~ 2500 3450
Wire Wire Line
	2500 3450 2200 3450
Wire Wire Line
	2500 3100 2500 3050
Wire Wire Line
	2500 3050 2750 3050
Connection ~ 2750 3050
$Comp
L Connector:DB9_Female J9
U 1 1 61BE1B69
P 7450 4200
F 0 "J9" H 7350 4900 50  0000 L CNN
F 1 "DB9_Female" H 7300 4800 50  0000 L CNN
F 2 "" H 7450 4200 50  0001 C CNN
F 3 " ~" H 7450 4200 50  0001 C CNN
	1    7450 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3800 6100 3800
Wire Wire Line
	6100 3900 7150 3900
Wire Wire Line
	7150 4100 6100 4100
Wire Wire Line
	6100 4200 7150 4200
Wire Wire Line
	7150 4500 6100 4500
Wire Wire Line
	6100 4600 7150 4600
Text Notes 6150 3800 0    50   ~ 0
Red (Red/Black)
Text Notes 6150 3900 0    50   ~ 0
Black (Red/Black)
Text Notes 6150 4100 0    50   ~ 0
Black (Orange/Black)
NoConn ~ 7150 4000
Text Notes 6150 4200 0    50   ~ 0
Orange (Orange/Black)
NoConn ~ 7150 4300
NoConn ~ 7150 4400
Text Notes 6150 4500 0    50   ~ 0
Black (Red/Black)
Text Notes 6150 4600 0    50   ~ 0
Red (Red/Black)
Text Label 6100 4200 2    50   ~ 0
A+
Text Label 6100 4100 2    50   ~ 0
A-
Text Label 6100 4500 2    50   ~ 0
B-
Text Label 6100 4600 2    50   ~ 0
B+
Text Label 6100 3800 2    50   ~ 0
O+
Text Label 6100 3900 2    50   ~ 0
O-
Text Notes 4900 5650 0    50   ~ 0
White (Red/White)
Text Notes 4900 5200 0    50   ~ 0
Red (Red/White)
Wire Wire Line
	2750 4900 2750 4650
Wire Wire Line
	2200 4650 2750 4650
Connection ~ 2750 4650
Wire Wire Line
	2750 4650 2750 3900
Wire Wire Line
	2200 3900 2750 3900
Connection ~ 2750 3900
Wire Wire Line
	2750 3900 2750 3750
Wire Wire Line
	8250 3800 9300 3800
Wire Wire Line
	9300 3900 8250 3900
Wire Wire Line
	8250 4100 9300 4100
Wire Wire Line
	9300 4200 8250 4200
Wire Wire Line
	8250 4500 9300 4500
Wire Wire Line
	9300 4600 8250 4600
NoConn ~ 8250 4000
NoConn ~ 8250 4300
NoConn ~ 8250 4400
$Comp
L Connector:DB9_Male J10
U 1 1 61C9ABE3
P 7950 4200
F 0 "J10" H 7868 3508 50  0000 C CNN
F 1 "DB9_Male" H 7868 3599 50  0000 C CNN
F 2 "" H 7950 4200 50  0001 C CNN
F 3 " ~" H 7950 4200 50  0001 C CNN
	1    7950 4200
	-1   0    0    1   
$EndComp
Text Notes 6650 4950 0    100  ~ 0
Internal
Text Notes 7950 4950 0    100  ~ 0
External
Text Notes 8550 3800 0    50   ~ 0
White/Black
Text Notes 8550 3900 0    50   ~ 0
Black/White
Text Notes 8550 4100 0    50   ~ 0
Black
Text Notes 8550 4200 0    50   ~ 0
Orange Dark
Text Notes 8550 4500 0    50   ~ 0
Blue
Text Notes 8550 4600 0    50   ~ 0
Orange light
$EndSCHEMATC
