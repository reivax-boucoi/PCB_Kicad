#ifndef PARSER_H
#define PARSER_H

#include <Arduino.h>

class Parser{
    public:
        Parser(M590 *gsm, Horaires *rtc,Ration *feeder);
        update();
    private:
        M590 *_gsm;
        Horaires *_rtc;
        Ration *_feeder;
        parse(String msg);
}

#endif
