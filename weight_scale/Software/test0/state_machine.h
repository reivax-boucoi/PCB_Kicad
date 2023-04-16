#ifndef SM_H_
#define SM_H_

#include <avr/io.h>


#define STATE_OFF 0
#define STATE_WAKEUP 1
#define STATE_TARE 2
#define STATE_IDLE 3

class SM {
public:
	SM();
	~SM();
	void update(void);
private:
	uint8_t current_state;
	static const uint8_t states_duration[4];
	uint8_t current_duration;
	void nextState(void);
	
};


#endif
