#include "state_machine.h"

const uint8_t SM::states_duration[] = {0, 10, 20, 255};

SM::SM(void){
	current_state=STATE_WAKEUP;
	current_duration=states_duration[current_state];
}


SM::~SM(void){
}

void SM::update(void){
	if(current_duration--==0){
		nextState();
	}
	switch(current_state){
		case STATE_OFF:
			//this should not occur
			break;
		case STATE_WAKEUP:
			//show some infos?
			//check batt voltage
			break;
		case STATE_TARE:
			//measure and accumulate result
			break;
		case STATE_IDLE:
			//measure and show result
			break;
	}
}

void SM::nextState(void){
	switch(current_state){
		case STATE_OFF:
			//show splash screen
			break;
		case STATE_WAKEUP:
			//show tare, initialize accumulator
			break;
		case STATE_TARE:
			//switch to meas mode with tare offset
			break;
		case STATE_IDLE:
			//goto sleep
		break;
	}
	
	current_state++;
	current_duration=states_duration[current_state];
}

