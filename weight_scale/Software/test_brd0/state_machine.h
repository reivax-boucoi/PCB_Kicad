#ifndef SM_H_
#define SM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "UART.h"
#include "scale.h"
#include "LCD.h"


#define STATE_OFF 0
#define STATE_WAKEUP 1
#define STATE_TARE 2
#define STATE_IDLE 3

#define UART_STREAM (1<<0)
#define UART_STREAM_VERBOSE (1<<1)

class SM {
public:
	SM(UART *u, Scale *s, LCD *l);
	~SM();
	void update(void);
	void stream(bool enable, bool verbose);
	Scale *myScale;
private:
	uint8_t current_state;
	uint8_t uart_flags;
	
	static const uint8_t states_duration[4];
	uint8_t current_duration;
	void nextState(void);
	UART *uart;
	LCD *myLCD;
	
};


#endif
