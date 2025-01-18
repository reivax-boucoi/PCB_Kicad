#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
//#include <util/delay.h>
#include <stdlib.h> //for itoa

#include "LCD.h"
#include "UART.h"
#include "Programs.h"

#define BTN0 (PIND&(1<<4))
#define BTN1 (PIND&(1<<5))

#define IRQ_STATE (PINE&(1<<7))

#define PWR_en_ON (PORTE|=(1<<5))
#define PWR_en_OFF (PORTE&=~(1<<5))
#define LoadCell_en_OFF (PORTE|=(1<<6))
#define LoadCell_en_ON (PORTE&=~(1<<6))

#define BATT_CUTOUT 290
#define BATT_EMPTY 300
#define BATT_ONEBAR 310
#define BATT_TWOBAR 320
#define BATT_FULL 330

UART uart;
LCD myLCD=LCD(0);//Use 1 for lowest power LCD mode
Program myProgram(&myLCD);

//Fuses -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xfd:m 
//Int RC osc, 6CK+65ms startup time
//No Clock div by 8
//Brown out detection enabled, 1.8V
//For BoD at 2.7V, use Efuse=FB instead of FD

void writeTime(void);

volatile uint8_t loop_cnt=1;
volatile uint8_t flags_state=0;
volatile uint8_t btn0_state=BTN0;
volatile uint8_t btn1_state=BTN1;
volatile uint8_t btn0_pressDuration=0;
volatile uint32_t total_time_ts=65535; // in tenths of second

int main(void){
	
	DDRD=0b11000000; 	//LED0, LED1 as outputs, BTN 0/1 as inputs
	PORTD=0b00110000;			//LED initial state:low, enable BTN pullups
	
	DDRE=0b01100011;//IRQ as input, LoadCell_en/PWR_en as outputs, TX as output, RX as input
	PORTE=0b10100000;//Enable IRQ pullup, set LoadCell_en/PWR_en to 1
	
	ADMUX|=(1<<REFS0)|0b11110;//Set AVCC as reference voltage for ADC, ADC MUX input to 1.1V BG
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS1);//Enable conversion complete interrupt, Clock prescaler 12MHz/64=187kHz
	PRR|=(1<<PRSPI)|(1<<PRUSART0);//Disable SPI and UART to save power
	
	TCCR1B |=(1<<WGM12)|(1<<CS12);// prescaler=clk/256, OCR1A is top.
	OCR1A=3332; // 8MHz/256 = 31250Hz -> COMPA_ISR every 100ms
	TIMSK1|=(1<<OCIE1A);
	
	
	myLCD.setDP(1);
	myLCD.setClk(1);
	myLCD.setBattery(LCD::FULL);
	
	while(--total_time_ts);
	
	btn0_state=BTN0;
	btn1_state=BTN1;
	LoadCell_en_OFF;
	sei();
	
	while(1){
	
		

		if(BTN0!=btn0_state){
			btn0_state=BTN0;
			if(btn0_state){
				if(!myProgram.started){
					myProgram.selectedProgram++;
					if(myProgram.selectedProgram>=PGM_CNT)myProgram.selectedProgram=0;
				}
				loop_cnt=1;
			}
		}
		if(BTN1!=btn1_state){
			btn1_state=BTN1;
			if(btn1_state){
				LED1_Toggle;
				if(myProgram.started){
					myProgram.stop();
				}else{
					myProgram.start(total_time_ts);
				}
				loop_cnt=1;
			}
		}
		if(flags_state&0x01){
			flags_state&=~0x01;
			if(myProgram.started){
				myProgram.update(total_time_ts);
			}
			if(--loop_cnt==0){
				loop_cnt=9;
				LED1_ON;
				ADCSRA|=(1<<ADSC); //Start single ADC conversion
				writeTime();
				myProgram.show();
				LED0_OFF;
				LED1_OFF;
			}
			if(BTN0==0){
				btn0_pressDuration++;
				if(btn0_pressDuration>20)PWR_en_OFF;
			}else{
				btn0_pressDuration=0;
			}			
		}
		if(uart.isDataAvailable()){
			char *cmd=uart.retrieve();
			uart.sendString("Start verbose streaming",true);
		}
		ADCSRA&=~(1<<ADEN);//Disable ADC
		PRR|=(1<<PRSPI)|(1<<PRUSART0)|(1<<PRADC);//Shut down clock to Timer1, SPI, UART, ADC
		set_sleep_mode(SLEEP_MODE_IDLE);
		//set_sleep_mode(SLEEP_MODE_PWR_SAVE);
		//set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		cli();
		if (1){
			sleep_enable();
			sei();
			sleep_cpu();
			sleep_disable();
		}
		PRR&=~(1<<PRADC);//Enable power to ADC, UART and SPI  again
		ADCSRA|=(1<<ADEN);//Enable ADC again
		sei();
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

ISR(TIMER1_COMPA_vect){//every 100ms
	total_time_ts++;
	myProgram.myBeep.update();
	flags_state|=0x01;
}

ISR(USART0_RX_vect){
	uart.receive();
}

void writeTime(void){
	uint8_t mins=total_time_ts/600;
	uint8_t secs=(total_time_ts/10)%60;
	if(mins>9){
		myLCD.setDigit(0,mins/10);
	}else{
		myLCD.setDigit(0,LCD::Blank);
	}
	myLCD.setDigit(1,mins%10);
	myLCD.setDigit(2,secs/10);
	myLCD.setDigit(3,secs%10);
	myLCD.setClk(secs%2);
}
