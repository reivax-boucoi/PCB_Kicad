#ifndef PARSER_H
#define PARSER_H

#include <Arduino.h>

class Parser {
    public:
        Parser();/*M590 *gsm, Horaires *rtc,Ration *feeder*/
        void update();
        void parse(String msg);
    private:
        /*  M590 *_gsm;
            Horaires *_rtc;
            Ration *_feeder;*/
        void dateQuery();
        void dateSet(String date, String time);
        void rationQuery();
        void rationSet(uint16_t qty);
        void statusQuery();
        void advancedStatusQuery();
        void statusReset();
        void horaireQuery(uint8_t alarmNb);
        void horaireSet(uint8_t alarmNb, bool state, String time);
        void modeVacancesSet();
        void modeSemaineSet();
        void modeManuelSet();
        void manualDistribute();
        void gainQuery();
        void gainSet(uint8_t gain);
        void setNumber(String nb);
        void parseFailed(String errorMsg);
        String collapseSpaces(String input);
};

#endif
