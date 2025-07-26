#ifndef M590_H
#define M590_H

#include <Arduino.h>
#include <EEPROM.h>
#include "StatusM.h"

#define EEPROM_NUMBER_ADDR 40
#define M590_SERIAL Serial
#define M590_TIMEOUT 5000  // Global timeout in ms
#define M590_MAXRETRIES 5
#define SIM_RST PIN_PD6
#define DFLT_PHONE_NUMBER "+33605006547"
#define DEBUG_EN

void display_freeram() ;
int freeRam();


class M590 {
    public:
        M590();

        uint8_t initialize(uint8_t retries = M590_MAXRETRIES, uint8_t errorCode = 0);
        uint8_t newSMSAvailable();
        String getSMS();
        bool sendSMS(const String& msg);
        int8_t getRSSI();
        uint8_t status;//255:uninitialized, 0:OK, 1-4:init, 5:sendSMS>, 6-10:getSMS, 11-12:getNbSMS, 13:getRSSI
        String replyNumber;

        void queueSMS();
        char *_text_ptr = NULL;
        StatusM *myStatus=NULL;

    private:
        bool sendCommand(const String& cmd, const String& expected, unsigned long timeout = M590_TIMEOUT);
        void readResponse(unsigned long timeout = M590_TIMEOUT);
        void togglePWR();
        String response;
        String LatinEncode(String input);
        void serial_flush();
};

#endif
