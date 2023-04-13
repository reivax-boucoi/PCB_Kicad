#ifndef SM_H_
#define SM_H_

class SM {
public:
	SM();
	~SM();
	enum states {OFF,WAKEUP,TARE,IDLE}
	enum states_duration {OFF_d=0, WAKEUP_d=10, TARE_d=20, IDLE_d=256};
	void update(void);
private:
	static states current_state;
	static uint8_t current_duration;
	void nextState(void);
};

#endif