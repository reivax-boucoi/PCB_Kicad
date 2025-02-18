#ifndef STATUSM_H
#define STATUSM_H

#include <Arduino.h>
#include <EEPROM.h> 
#include "Horaires.h"

#define EEPROM_STATUS_ADDR 80  // EEPROM start address to store status
#define BATT_ADC_GAIN (100.0/1024.0*5*10/(10+39)) //TODO change 5V to actual VCC or better use 1V BG ref

#define ERRORTypeNB 5
enum ErrorType {
    SIM_ERROR,
    RTC_ERROR,
    M1_ERROR,
    M2_ERROR,
    M12_ERROR
};

Class StatusM{
public:
	StatusM(DateTime now);
	void getReport(char *text_content);
	void resetStats();
	void update(DateTime now);
	void increaseErrorCnt(ErrorType err);
private:
	uint8_t err_cnt[ERRORTypeNB];	
	uint16_t startupTime; //in hours since 2025
	DateTime nowTime;
	uint16_t batt_level; //in 10mV LSB, i.e. 1200 = 12.00V
};


#endif