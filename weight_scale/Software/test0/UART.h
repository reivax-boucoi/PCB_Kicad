#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define UART_BAUDRATE 9600

#define UART_BAUD ((F_CPU)/(UART_BAUDRATE*16UL)-1)            // set baud rate value for UBRR

class UART{
public:
    UART(void);
    ~UART(void);
    
    void sendByte(uint8_t b);
    void sendString(char* data);
    uint8_t getChar(void);
    bool isDataAvailable(void);
    
    
};

#endif
