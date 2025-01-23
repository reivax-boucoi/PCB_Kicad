#ifndef PROGRAMS_H_
#define PROGRAMS_H_

#include <avr/io.h>
#include "LCD.h"
#include <stdlib.h> //for itoa
#define PGM_CNT 5


#define LED0_ON (PORTD|=(1<<6))
#define LED0_OFF (PORTD&=~(1<<6))
#define LED0_Toggle (PORTD^=(1<<6))

#define LED1_ON (PORTD|=(1<<7))
#define LED1_OFF (PORTD&=~(1<<7))
#define LED1_Toggle (PORTD^=(1<<7))

class Beep{
public:
    Beep();
    ~Beep();
    void singleB(void);
    void dualB(void);
    void longB(void);
    void update(void);
private:
    uint8_t cnt;
    void on(void);
    void off(void);
};

class Program {
public:
	Program(LCD *l);
	~Program();
    Beep myBeep;

    uint8_t selectedProgram;
    bool started;

	void start(uint32_t time);
	void stop(void);
	void update(uint32_t time);
    void show(void);
    
private:
	LCD *myLCD;
	static const LCD::Symbol Sym1[PGM_CNT];
	static const uint8_t Sym2[PGM_CNT];
    static const uint16_t LL_Tnext[13];//timestamp form iitial test start to switch to next palier
    static const uint8_t LL_Tlap[13];//lap duration for each palier
    uint16_t lapTime;//current lap duration, fixed for fractionne, reducing for LL
    uint32_t pTime; //timestamp form last lap change
    uint32_t startTime;//for LL, timestamp fo overall test start
    uint8_t lapNb;//Fractionne: number of cycles. LL: palier

};

#endif
