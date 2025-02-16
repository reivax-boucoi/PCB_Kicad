#include "CMDParser.h"




Parser::Parser(M590 *gsm, Horaires *rtc,Ration *feeder){
    _gsm=gsm;
    _rtc=rtc;
    _feeder=feeder;
}
Parser::parse(String msg){
    
}
Parser::update(){
    uint8_t nbMsg=gsm->newSMSAvailable();
    while(nbMsg-- > 0){
        parse(gsm->getSMS());
    }
}
