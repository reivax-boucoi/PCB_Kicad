#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdlib.h> //for itoa

#define UART_BAUDRATE 9600
#define UART_ECHO true //enable console echo on type
#define UART_BAUD ((F_CPU)/(UART_BAUDRATE*16UL)-1)            // set baud rate value for UBRR

#define UART_RXBUF_SIZE 20

class UART{
public:
    UART(void);
    ~UART(void);
    
    void sendByte(char b);
    void sendString(char* data);
    void sendString(char* data, bool lineReturn);
    void sendNb(int32_t nb);
    void sendNb(int32_t nb,uint8_t base, bool lineReturn);
    bool isDataAvailable(void);
    void receive(void);
    char* retrieve(void);
private:
    char data[UART_RXBUF_SIZE];
    bool dataReady;
    uint8_t data_len;
    char getChar(void);
    
};

#endif
