#ifndef STATUSM_H
#define STATUSM_H

#include <Arduino.h>
#include <EEPROM.h>
#include "Horaires.h"

#define EEPROM_STATUS_ADDR 80  // EEPROM start address to store status
#define BATT_ADC_GAIN 5.405//(100.0/1024.0*3.87*3/(3+39)) //3.8V Vcc, Rdiv top 39k, bot 10k//4k3=3k TODO use 1V BG ref
#define BATT_MON PIN_PA0
#define BTN_USR1 PIN_PC3    //blue button
#define BTN_USR2 PIN_PC2    //yellow button
#define LED_B PIN_PA3
#define LED_G PIN_PA4
#define LED_Y PIN_PA5
#define LED_R PIN_PA6

#define LED_REDBUTTON 1
#define LED_BLUEBUTTON 2
#define LED_YELLOWBUTTON 3
#define LED_REDBOARD 0

const uint8_t LEDS_pinMap[4]={LED_B,LED_G,LED_Y,LED_R};
//4th LED is OFF: OK, FASTBLINK = Parsing error, SLOWBLINK=send error

#define ERRORTypeNB 5
#define LED_FASTBLINK_PERIOD 150 //period in ms
#define LED_SLOWBLINK_PERIOD 7 //number of fastblink periods

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
        uint16_t update(DateTime now);
        void increaseErrorCnt(ErrorType err);
        void animateLEDs();
        void setLED(uint8_t led, LED_STATUS s);
        uint8_t handleButtons();//returns 0: no buttons, 1: blue pressed, 2: blue depressed, 3: yellow pressed
        uint16_t batt_level; //in 10mV LSB, i.e. 1200 = 12.00V
    private:
        LED_STATUS leds[4];
        unsigned long ledFastTime;
        uint8_t ledSlowTime;
        uint8_t buttonStates;

        uint8_t err_cnt[ERRORTypeNB];
        uint16_t startupTime; //in hours since 2025
        DateTime nowTime;
};


#endif
