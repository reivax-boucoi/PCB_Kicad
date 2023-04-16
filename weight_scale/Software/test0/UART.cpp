#include "UART.h"

UART::UART(void){
    /*UBRR0H = (UART_BAUD>>8);
    UBRR0L = UART_BAUD;	// set baud rate
    UCSR0B|= (1<<TXEN0)|(1<<RXEN0);	// enable receiver and transmitter
    UCSR0C|= (1<<UMSEL01)|(1<<UCSZ00)|(1<<UCSZ01);	// 8bit data format    */
    
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

