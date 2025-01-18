#include "UART.h"

UART::UART(void){
    UBRR0H = (UART_BAUD>>8);
    UBRR0L = UART_BAUD;	// set baud rate
    UCSR0B|= (1<<TXEN0)|(1<<RXEN0);	// enable receiver and transmitter
    // Async. mode, 8bit, No parity, 1 stop bit
    UCSR0C = (0<<UMSEL0)|(0<<UPM00)|(0<<USBS0)|(3<<UCSZ00)|(0<<UCPOL0);
    
    dataReady=false;
    data_len=0;
    
    UCSR0B |= (1<<RXCIE0);
}

UART::~UART(void){
    
}

void UART::sendByte(char b){
    while (!( UCSR0A & (1<<UDRE0)));	// wait while register is free
    UDR0 = b;	// load data in the register
}

void UART::sendString(char* data){
    while(*data>0){
		sendByte(*data++);
	}
}

void UART::sendString(char* data, bool lineReturn){
    while(*data>0){
		sendByte(*data++);
	}
    if(lineReturn){
        sendByte('\r');
        sendByte('\n');
    }
}

void UART::sendNb(int32_t nb,uint8_t base, bool lineReturn){
    char buffer [35];
    ltoa(nb,buffer,base);
    sendString(buffer,lineReturn);
}

void UART::sendNb(int32_t nb){
    char buffer [12];//32 bits in decimal is 4milions, 10 digits
    ltoa(nb,buffer,10);
    sendString(buffer);
    sendByte('\r');
    sendByte('\n');
}

char UART::getChar(void){
    //while(!(UCSRA) & (1<<RXC));	// wait while data is being received
    char d=UDR0;
#ifdef UART_ECHO
    sendByte(d);
#endif
    return d;	// return 8-bit data
}

void UART::receive(void){
    char d=getChar();
    if(d=='\r'){
        dataReady=true;
    }else{    
        data[data_len]=d;
        data_len++;
    }
}

char* UART::retrieve(void){
    data[data_len]='\0';
    dataReady=false;
    data_len=0;
    return data;
}

bool UART::isDataAvailable(void){
    return dataReady & (data_len!=0);
}
