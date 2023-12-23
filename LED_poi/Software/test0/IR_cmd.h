#ifndef ir_cmd_h
#define ir_cmd_h


#define IR_SMALLD_SIRC12

#define IR_PIN 0 // PD2 //TODO get actual pin in layout
//Pinout: OUT GND VCC (similar to TSOP48xx)
//Library only works with pins 0 RXD, 1 TXD, 2 SDA, 3 SCL, 7 PE6

void IR_poll();

#endif
