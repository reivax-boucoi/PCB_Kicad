#ifndef STATUSM_H
#define STATUSM_H

#include <Arduino.h>
#include <EEPROM.h>
#include "Horaires.h"

#define EEPROM_STATUS_ADDR 80  // EEPROM start address to store status
#define BATT_ADC_GAIN (100.0/1024.0*5*10/(10+39)) //TODO change 5V to actual VCC or better use 1V BG ref
#define BATT_MON PIN_PA0
#define BTN_USR1 PIN_PC2
#define BTN_USR2 PIN_PC3
#define LED_B PIN_PA3
#define LED_G PIN_PA4
#define LED_Y PIN_PA5
#define LED_R PIN_PA6

const uint8_t LEDS_pinMap[4]={LED_B,LED_G,LED_Y,LED_R};
//4th LED is OFF: OK, FASTBLINK = Parsing error

#define ERRORTypeNB 5
#define LED_FASTBLINK_PERIOD 250 //period in ms
#define LED_SLOWBLINK_PERIOD 4 //number of fastblink periods

enum ErrorType {
    SIM_ERROR,
    RTC_ERROR,
    M1_ERROR,
    M2_ERROR,
    M12_ERROR
};
enum LED_STATUS {
    LED_OFF,
    LED_FASTBLINK,
    LED_SLOWBLINK,
    LED_ON
};

class StatusM {
    public:
        StatusM(DateTime now);
        void getReport(char *text_content);
        void resetStats();
        void update(DateTime now);
        void increaseErrorCnt(ErrorType err);
        void animateLEDs();
        void setLED(uint8_t led, LED_STATUS s);
        uint8_t handleButtons();//returns 0: no buttons, 1: green pressed, 2: green depressed, 3: yellow pressed
    private:
        LED_STATUS leds[4];
        unsigned long ledFastTime;
        uint8_t ledSlowTime;
        uint8_t buttonStates;

        uint8_t err_cnt[ERRORTypeNB];
        uint16_t startupTime; //in hours since 2025
        DateTime nowTime;
        uint16_t batt_level; //in 10mV LSB, i.e. 1200 = 12.00V
};


#endif
