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
L Connector:6P6C_Shielded J1
U 1 1 60846E15
P 3500 3550
F 0 "J1" H 3557 4117 50  0000 C CNN
F 1 "6P6C_Shielded" H 3557 4026 50  0000 C CNN
F 2 "Connector_RJ:RJ12_Amphenol_54601" V 3500 3575 50  0001 C CNN
F 3 "~" V 3500 3575 50  0001 C CNN
	1    3500 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_PIC_ICSP_ICD J2
U 1 1 60847A64
P 5550 3500
F 0 "J2" H 5220 3546 50  0000 R CNN
F 1 "Conn_PIC_ICSP_ICD" H 5220 3455 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 5600 3650 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/devicedoc/30277d.pdf" V 5250 3350 50  0001 C CNN
	1    5550 3500
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 6084848E
P 6850 3200
F 0 "D1" V 6889 3083 50  0000 R CNN
F 1 "LED" V 6798 3083 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6850 3200 50  0001 C CNN
F 3 "~" H 6850 3200 50  0001 C CNN
	1    6850 3200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 60848F40
P 6850 3650
F 0 "R1" H 6920 3696 50  0000 L CNN
F 1 "470" H 6920 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6780 3650 50  0001 C CNN
F 3 "~" H 6850 3650 50  0001 C CNN
	1    6850 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3900 6850 3900
Wire Wire Line
	6850 3900 6850 3800
Wire Wire Line
	6850 3500 6850 3350
Wire Wire Line
	6850 3050 6850 3000
Wire Wire Line
	6850 3000 5750 3000
Wire Wire Line
	5750 3000 5750 3100
Wire Wire Line
	3500 3950 4200 3950
Wire Wire Line
	5750 3950 5750 3900
Connection ~ 5750 3900
Wire Wire Line
	3900 3550 4200 3550
Wire Wire Line
	4200 3550 4200 3950
Connection ~ 4200 3950
Wire Wire Line
	4200 3950 5750 3950
Wire Wire Line
	3900 3750 4250 3750
Wire Wire Line
	4250 3750 4250 3300
Wire Wire Line
	4250 3300 5050 3300
Wire Wire Line
	3900 3650 4300 3650
Wire Wire Line
	4300 3650 4300 3000
Wire Wire Line
	4300 3000 5750 3000
Connection ~ 5750 3000
Wire Wire Line
	3900 3450 5050 3450
Wire Wire Line
	5050 3450 5050 3500
Wire Wire Line
	3900 3350 4350 3350
Wire Wire Line
	4350 3350 4350 3600
Wire Wire Line
	4350 3600 5050 3600
Wire Wire Line
	3900 3250 4400 3250
Wire Wire Line
	4400 3250 4400 3700
Wire Wire Line
	4400 3700 5050 3700
$EndSCHEMATC
