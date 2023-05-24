#include "state_machine.h"

const uint8_t SM::states_duration[] = {0, 40, 30, 0};

SM::SM(UART* u, Scale *s, LCD *l){
	uart=u;
	myScale=s;
	myLCD=l;
	current_state=STATE_OFF;
	current_duration=1;
	uart_flags=0;
	uart->sendString("\r\n\nInit\n",true);
}


SM::~SM(void){
}


void SM::stream(bool enable, bool verbose){
	uart_flags=enable | (verbose<<1);
}

void SM::update(void){
	if(current_duration!=0){//States with 0 duration stay on indefinitely
		if(--current_duration==0){
			nextState();
		}
	}
	switch(current_state){
		case STATE_OFF:
			//this should not occur
			break;
			
		case STATE_WAKEUP:
			//show some infos?
			//check batt voltage
			if(current_duration==30){
				myLCD->setDigit(0,LCD::V);
				myLCD->setDigit(1,LCD::Equal);
				myLCD->setDigit(2,LCD::b);
				myLCD->setDigit(3,LCD::A);
				myLCD->setDigit(4,LCD::t);
				myLCD->setDigit(5,LCD::t);
				
			}else if(current_duration==20){
				ADCSRA|=(1<<ADSC); //Start single ADC conversion
				myLCD->setDigit(0,LCD::V);
				myLCD->setDigit(1,LCD::Equal);
				myLCD->setDigit(2,LCD::Blank);
				myLCD->setDP(true);
			}else if(current_duration<20){
				ADCSRA|=(1<<ADSC); //Start single ADC conversion
			}
			
			break;
			
		case STATE_TARE:
			//measure and accumulate result
			if(current_duration==20){
				myLCD->clear(false);
				myLCD->setDigit(0,LCD::t);
				myLCD->setNb(myScale->tare(),5);
			}else if(current_duration<20){
				myLCD->setNb(myScale->tare(),5);
			}
			
			break;
			
		case STATE_IDLE:
			//measure and show result
			myLCD->setNb(myScale->getWeight());
			if(uart_flags & UART_STREAM)
				myScale->showWeight(uart_flags & UART_STREAM_VERBOSE);
			
			break;
	}
}

void SM::nextState(void){
	switch(current_state){
		case STATE_OFF:
			uart->sendString("SM:Wakeup",true);
			myLCD->setDigit(0,LCD::H);
			myLCD->setDigit(1,LCD::E);
			myLCD->setDigit(2,LCD::L);
			myLCD->setDigit(3,LCD::L);
			myLCD->setDigit(4,0);
			myLCD->setDigit(5,LCD::Blank);
			//show splash screen
			break;
		case STATE_WAKEUP:
			uart->sendString("SM:Tare",true);
			myLCD->setDP(false);
			myLCD->setDigit(0,LCD::t);
			myLCD->setDigit(1,LCD::A);
			myLCD->setDigit(2,LCD::r);
			myLCD->setDigit(3,LCD::E);
			myLCD->setDigit(4,LCD::Blank);
			myLCD->setDigit(5,LCD::Blank);
			
			//show tare, initialize accumulator
			break;
		case STATE_TARE:
			
			uart->sendString("\tTare completed: ");
			uart->sendNb(myScale->offset);
			uart->sendString("SM:Idle",true);
			myLCD->clear(false);
			myLCD->setDP(true);
			//switch to meas mode with tare offset
			break;
			
		case STATE_IDLE: //goto sleep
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
			PRR&=~(1<<PRADC)|(1<<PRSPI)|(1<<PRUSART0);//Enable power to ADC, UART and SPI  again
			ADCSRA|=(1<<ADEN);//Enable ADC again
			sei();
		break;
	}
	
	current_state++;
	current_duration=states_duration[current_state];
}

