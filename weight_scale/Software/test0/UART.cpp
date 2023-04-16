#include "UART.h"

UART::UART(void){
    UBRRH = (UART_BAUD>>8);
    UBRRL = UART_BAUD;	// set baud rate
    UCSRB|= (1<<TXEN)|(1<<RXEN);	// enable receiver and transmitter
    UCSRC|= (1<<UMSEL)|(1<<UCSZ0)|(1<<UCSZ1);	// 8bit data format    
    
}

UART::~UART(void){
    
}

void UART::sendByte(uint8_t b){
    while (!( UCSRA & (1<<UDRE)));	// wait while register is free
    UDR = b;	// load data in the register
}

void UART::sendString(char* data){
    while(*data>0){
		sendByte(*data++);
	}
}

uint8_t UART::getChar(void){
    if(isDataAvailable()){
        while(!(UCSRA) & (1<<RXC));	// wait while data is being received
        return UDR;	// return 8-bit data
    }else{
        return 0;
    }
    
}

bool UART::isDataAvailable(void){
    return 1;
}

