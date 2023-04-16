#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdlib.h> //for itoa

#include "LCD.h"
#include "UART.h"
#include "ADC.h"
#include "state_machine.h"

UART uart;
MCP3462 myADC;
SM mySM;
LCD myLCD(0);//Use 1 for lowest power LCD mode

//Fuses -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xfd:m 
//Int RC osc, 6CK+65ms startup time
//No Clock div by 8
//Brown out detection enabled, 1.8V
//For BoD at 2.7V, use Efuse=FB instead of FD

#define LED0_ON (PORTD|=(1<<6))
#define LED0_OFF (PORTD&=~(1<<6))
#define LED0_Toggle (PORTD^=(1<<6))

#define LED1_ON (PORTD|=(1<<7))
#define LED1_OFF (PORTD&=~(1<<7))
#define LED1_Toggle (PORTD^=(1<<7))

#define BTN0 (PINB&(1<<6)) //PCINT14
#define BTN1 (PINB&(1<<7)) //PCINT15

#define BATT_CUTOUT 3200
#define BATT_EMPTY 3500
#define BATT_ONEBAR 3600
#define BATT_TWOBAR 3750
#define BATT_FULL 3900



volatile uint32_t cnt=59650;
volatile uint8_t state=1;

int main(void){
	
	DDRD=0b11000000; 	//LED0, LED1 as outputs
	PORTD=0x00;			//LED initial state:low
	DDRB=0x00; 			//BTN0, BTN1 as inputs
	PORTB=0b11000000;	//BTN0, BTN1 activate internal pullups
	
	DDRE=0x00;
	PORTE=0xFF;
	DDRB=0x00;
	PORTB=0xFF;
	
	LED0_ON;
	PRR|=(1<<PRTIM1)|(1<<PRSPI)|(1<<PRUSART0);//Shut down clock to Timer1, SPI, UART
	
	ADMUX|=(1<<REFS0)|0b11110;//Set AVCC as reference voltage for ADC, ADC MUX input to 1.1V BG
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS1);//Enable conversin complete interrupt, Clock prescaler 12MHz/64=187kHz
	EIMSK=0b00100000;//Enable pin change interrupt PCINT8-15 WARNING Avrdude is not up to date with changelog from P to PA: PCIE1 has changed location from bit 7 to 5 
	PCMSK1=(1<<PCINT14);//Enable BTN0 interrupt
	sei();
	
	
	while(1){
	
		_delay_ms(100);
		switch(state){
			case 0:
				ADCSRA&=~(1<<ADEN);//Disable ADC
				PRR|=(1<<PRTIM1)|(1<<PRSPI)|(1<<PRUSART0)|(1<<PRADC);//Shut down clock to Timer1, SPI, UART, ADC
				
				set_sleep_mode(SLEEP_MODE_PWR_SAVE);
				//set_sleep_mode(SLEEP_MODE_PWR_DOWN);
				cli();
				if (1){
					sleep_enable();
					sei();
					sleep_cpu();
					sleep_disable();
				}
				PRR&=~(1<<PRADC);//Enable power to ADC again
				ADCSRA|=(1<<ADEN);//Enable ADC again
				sei();
				state=1;
				break;
				
			case 1:
				LED0_Toggle;
				ADCSRA|=(1<<ADSC); //Start single ADC conversion
				if(myADC.isDataReady()){
					uint32_t d=myADC.getDirectData();
					char buffer [11];//32 bits in decimal is 4milions, 10 digits
					ultoa(d,buffer,10);
					uart.sendString(buffer);
				}
		}
		
		if(cnt>=BATT_FULL){
			myLCD.setBattery(LCD::FULL);
		}else if(cnt>=BATT_TWOBAR){
			myLCD.setBattery(LCD::TWOBAR);
		}else if(cnt>=BATT_ONEBAR){
			myLCD.setBattery(LCD::ONEBAR);
		}else if(cnt>=BATT_EMPTY){
			myLCD.setBattery(LCD::EMPTY);
		}else{
			myLCD.setBattery(LCD::NONE);
			//we should shutdown here
		}
	}

	return 0;
}



ISR(PCINT1_vect){
	if(BTN0){
		if(state==1){
			LED0_OFF;
			state=0;
		}else{
			LED0_ON;
		}
	}
}

ISR(ADC_vect){
	uint16_t ADC_val=ADCL;
	ADC_val+=ADCH<<8;
	
	//CNT=1.1*1024/Vref
	//Vref=1.1*1024/CNT
	cnt=(1024.0*1100.0)/ADC_val;
	myLCD.setNb(cnt);
}

ISR(USART_RX_vect){
	uint8_t data=uart.getChar();
}
