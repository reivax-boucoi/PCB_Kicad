#ifndef PARSER_H
#define PARSER_H

#include <Arduino.h>
#include "Ration.h"
#include "Horaires.h"
#include "M590.h"
#include "StatusM.h"

#define SMS_TEXT_BUF 255


class Parser {
    public:
        Parser(M590 *gsm, Horaires *rtc, Ration *feeder, DateTime now);
        StatusM status;
        void update(DateTime now);
        bool parse(String msg);

        uint8_t text_length = 0;
        char text_content[SMS_TEXT_BUF];

        void sendRationStatus(uint8_t alarmIdx); //used when a ration completes
        void sendLowBattery(uint16_t batt);//batt=tension en mV *64
        void sendSystemRestarted();

    private:
        M590 *_gsm;
        Horaires *_rtc;
        Ration *_feeder;

        void dateQuery();
        void dateSet(String date, String time);
        void rationQuery();
        void rationSet(uint16_t qty);
        void statusQuery();
        void advancedStatusQuery();
        void statusReset();
        void horaireQuery(uint8_t alarmNb);
        void horaireSet(uint8_t alarmNb, bool state, String time);
        void modeManuelSet();
        void modeSemaineSet();
        void modeVacancesSet();
        void manualDistribute();
        void gainQuery();
        void gainSet(uint8_t gain);
        void setNumber(String nb);
        void parseFailed(String errorMsg);
        String collapseSpaces(String input);
};

#endif
