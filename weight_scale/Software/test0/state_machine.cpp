#include "state_machine.h"

SM::SM(void){
	current_state=WAKEUP;
	current_duration=WAKEUP_d;
}


SM::~SM(void){
}

SM::update(void){
	if(current_duration--==0){
		nextState();
	}
	switch(current_state){
		case OFF:
			//this should not occur
			break;
		case WAKEUP:
			//show some infos?
			//check batt voltage
			break;
		case TARE:
			//measure and accumulate result
			break;
		case IDLE:
			//measure and show result
			break;
	}
}

SM::nextState(void){
	switch(current_state){
		case OFF:
			current_state=WAKEUP;
			current_duration=WAKEUP_d;
			//show splash screen
			break;
		case WAKEUP:
			current_state=TARE;
			current_duration=TARE_d;
			//show tare, initialize accumulator
			break;
		case TARE:
			current_state=IDLE;
			current_duration=IDLE_d;
			//switch to meas mode with tare offset
			break;
		case IDLE:
			current_state=OFF;
			current_duration=OFF_d;
			//goto sleep
		break;
	}
}