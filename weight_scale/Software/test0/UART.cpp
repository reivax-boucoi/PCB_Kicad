#include "UART.h"

UART::UART(void){
    UBRRH = (UART_BAUD>>8);
    UBRRL = UART_BAUD;	// set baud rate
    UCSRB|= (1<<TXEN)|(1<<RXEN);	// enable receiver and transmitter
    // Async. mode, 8bit, No parity, 1 stop bit
    UCSRC = (0<<UMSEL)|(0<<UPM0)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
    
    dataReady=false;
    data_len=0;
    
    UCSRB |= (1<<RXCIE);
}

UART::~UART(void){
    
}

void UART::sendByte(char b){
    while (!( UCSRA & (1<<UDRE)));	// wait while register is free
    UDR = b;	// load data in the register
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
    char d=UDR;
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
