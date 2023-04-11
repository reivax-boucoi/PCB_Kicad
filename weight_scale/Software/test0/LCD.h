#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

class LCD {
public:
	LCD();
	~LCD();
	enum Symbol {A=0x77,b=0x7C,C=0x39,d=0x5E,E=0x79,F=0x71,H=0x76,L=0x38,P=0x73,U=0x3E,
		Minus=0x40,Blank=0x00,Equal=0x48,Degree=0xC3};
	enum Battery {NONE,EMPTY,FIRST,SECOND,THIRD,ONEBAR,TWOBAR,FULL};



	static void setDigit(uint8_t dig, Symbol s);
	static void setDigit(uint8_t dig, uint8_t nb);
	static void setBattery(Battery b);
	static void setDP(bool b);
	static void setClk(bool b);
	static bool getDP(void);
	static bool getClk(void);
	static uint8_t setNb(int32_t nb);
	static void clear(void);
	static void blink(uint16_t t);
private:
	struct digit{
		uint8_t s[7];
		volatile uint8_t* dr[7];
	};
	static digit digits[6];
	static const uint8_t NbMap[10];

};

#endif
