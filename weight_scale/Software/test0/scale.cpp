#include "scale.h"

Scale::Scale(UART* u){
    uart=u;
    gain=1;
    while(DATA_READY){
        _delay_ms(1);
    }
    offset=myADC.getDirectData();
}

Scale::~Scale(void){
    
}


int32_t Scale::tare(void){
    while(DATA_READY){
        _delay_ms(1);
    }
    offset=(myADC.getDirectData()+offset)>>1;
    return offset;
}


int32_t Scale::getWeight(void){
    value=myADC.getDirectData();
    value_scl=(value-offset)*gain;
 return value_scl;
}

void Scale::showWeight(bool verbose){
    
    if(verbose){
        uart->sendNb(value_scl,10,false);
        uart->sendByte('\t');
        uart->sendNb(value,2,true);
    }else{
        uart->sendNb(value_scl);
    }
}
