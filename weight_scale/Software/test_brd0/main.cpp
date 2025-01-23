#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdlib.h> //for itoa

#include "state_machine.h"
#include "LCD.h"
#include "UART.h"

#define LED0_ON (PORTD|=(1<<6))
#define LED0_OFF (PORTD&=~(1<<6))
#define LED0_Toggle (PORTD^=(1<<6))

#define LED1_ON (PORTD|=(1<<7))
#define LED1_OFF (PORTD&=~(1<<7))
#define LED1_Toggle (PORTD^=(1<<7))

#define BTN0 (PIND&(1<<4))
#define BTN1 (PIND&(1<<5))

#define IRQ_STATE (PINE&(1<<7))

#define PWR_en_ON (PORTE|=(1<<5))
#define PWR_en_OFF (PORTE&=~(1<<6))
#define LoadCell_en_ON (PORTE|=(1<<7))
#define LoadCell_en_OFF (PORTE&=~(1<<7))

#define BATT_CUTOUT 295
#define BATT_EMPTY 305
#define BATT_ONEBAR 315
#define BATT_TWOBAR 325
#define BATT_FULL 335

UART uart;
LCD myLCD=LCD(0);//Use 1 for lowest power LCD mode
//Scale myScale=Scale(&uart);
//SM mySM(&uart, &myScale,&myLCD);

//Fuses -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xfd:m 
//Int RC osc, 6CK+65ms startup time
//No Clock div by 8
//Brown out detection enabled, 1.8V
//For BoD at 2.7V, use Efuse=FB instead of FD

volatile uint8_t loop_cnt=0;
volatile uint8_t btn_state=0;

int main(void){
	
	DDRD=0b11000000; 	//LED0, LED1 as outputs, BTN 0/1 as inputs
	PORTD=0b00110000;			//LED initial state:low, enable BTN pullups
	
	DDRE=0b01100011;//IRQ as input, LoadCell_en/PWR_en as outputs, TX as output, RX as input
	PORTE=0b11100000;//Enable IRQ pullup, set LoadCell_en/PWR_en to 1
	
	LED0_ON;
	LED1_ON;
	//PRR|=(1<<PRTIM1);//Shut down clock to Timer1
	
	ADMUX|=(1<<REFS0)|0b11110;//Set AVCC as reference voltage for ADC, ADC MUX input to 1.1V BG
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS1);//Enable conversin complete interrupt, Clock prescaler 12MHz/64=187kHz
	sei();
	
	myLCD.setNb(12345,5);
	myLCD.setBattery(LCD::FULL);
	
	while(1){
	
		_delay_ms(10);
		loop_cnt++;
		if(loop_cnt>9){
			loop_cnt=0;
			//mySM.update();
		}

		if(BTN0!=btn_state){
			btn_state=BTN0;
			if(btn_state){
				LED0_Toggle;
			}
		}
		if(uart.isDataAvailable()){
			char *cmd=uart.retrieve();
			uart.sendString("Start verbose streaming",true);
		}
	}

	return 0;
}




ISR(ADC_vect){
	uint16_t ADC_val=ADCL;
	ADC_val+=ADCH<<8;
	
	//CNT=1.1*1024/Vref
	//Vref=1.1*1024/CNT
	//1.02578
	//1.0127
	//
	uint32_t cnt=(109875.0)/ADC_val;// in tens of mV, i.e. 330=>3.30V
	myLCD.setNb(cnt,3);
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

ISR(USART0_RX_vect){
	uart.receive();
}
