#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD.h"
LCD myLCD;

//Fuses -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xfd:m 
//Int RC osc, 6CK+65ms startup time
//No Clock div by 8
//Brown out detection enabled, 1.8V
//For BoD at 2.7V, use Efuse=FB instead of FD

#define LED0_ON (PORTD|=(1<<6))
#define LED0_OFF (PORTD&=~(1<<6))
#define LED1_ON (PORTD|=(1<<7))
#define LED1_OFF (PORTD&=~(1<<7))
#define BTN0 (PIND&(1<<4))
#define BTN1 (PIND&(1<<5))

#define BATT_CUTOUT 3200
#define BATT_EMPTY 3500
#define BATT_ONEBAR 3600
#define BATT_TWOBAR 3750
#define BATT_FULL 3900

volatile uint32_t cnt=59650;

int main(void){
	//myLCD.setClk(true);
	DDRD=0b11000000; //LED0, LED1 as outputs, BTN0, BTN1 as inputs
	PORTD=0b00110000; //BTN0, BTN1 activate internal pullups
	
	ADMUX|=(1<<REFS0)|0b11110;//Set AVCC as reference voltage for ADC, ADC MUX input to 1.1V BG
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS1);//Enable conversin complete interrupt, Clock prescaler 12MHz/64=187kHz
	
	sei();
	while(1){
		_delay_ms(200);
		ADCSRA|=(1<<ADSC);
		LED0_ON;
		myLCD.setNb(cnt);
		if(cnt>=5000){
			myLCD.setBattery(LCD::FULL);
		}else if(cnt>=4000){
			myLCD.setBattery(LCD::TWOBAR);
		}else if(cnt>=3000){
			myLCD.setBattery(LCD::ONEBAR);
		}else if(cnt>=2000){
			myLCD.setBattery(LCD::EMPTY);
		}else{
			myLCD.setBattery(LCD::NONE);
		}
	}

	return 0;
}

//CNT=1.1*1024/Vref
//Vref=1.1*1024/CNT

ISR(ADC_vect){
	uint16_t ADC_val=ADCL;
	ADC_val+=ADCH<<8;
	cnt=(1024.0*1100.0)/ADC_val;
	LED0_OFF;
}
