#include "utils.h"


void IO_initialize(){
    digitalWrite(KEY,LOW);
    digitalWrite(BTN,LOW);
    digitalWrite(LED_ONBRD,LOW);
    pinMode(LED_ONBRD,OUTPUT);
    pinMode(KEY,OUTPUT);
    pinMode(BTN,INPUT);
    
    pinMode(ACC_INT1,INPUT);
    pinMode(ACC_INT2,INPUT);
    digitalWrite(ACC_INT1,LOW);
    digitalWrite(ACC_INT2,LOW);
    
}

void supply_ON(){
    digitalWrite(KEY,HIGH);
    delay(60);
    digitalWrite(KEY,LOW);
    
}

void supply_OFF(){
    delay(60);
    digitalWrite(KEY,HIGH);
    delay(60);
    digitalWrite(KEY,LOW);
    delay(100);    
    digitalWrite(KEY,HIGH);
    delay(60);
    digitalWrite(KEY,LOW);
    while(1){}
}
