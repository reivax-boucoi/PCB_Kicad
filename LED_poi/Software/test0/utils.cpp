#include "utils.h"


Animations* myAnimations = new Animations();

void IO_initialize() {
    digitalWrite(KEY, LOW);
    digitalWrite(BTN, LOW);
    pinMode(KEY, OUTPUT);
    pinMode(BTN, INPUT);

    pinMode(ACC_INT1, INPUT);
    pinMode(ACC_INT2, INPUT);
    digitalWrite(ACC_INT1, LOW);
    digitalWrite(ACC_INT2, LOW);

}

void supply_ON() {
    digitalWrite(KEY, HIGH);
    delay(60);
    digitalWrite(KEY, LOW);
}

void supply_OFF() {
    Serial.println("turn OFF !");
    for (uint8_t i = 255; i > 5; i -= 5) {
        LEDs_setColor(i);
        _delay_ms(30);
    }
    delay(60);
    digitalWrite(KEY, HIGH);
    delay(60);
    digitalWrite(KEY, LOW);
    delay(100);
    digitalWrite(KEY, HIGH);
    delay(60);
    digitalWrite(KEY, LOW);
}




Button::Button(void) {
    pstate = LOW;
    newstate = LOW;
    pressTime = 0;
}
uint8_t Button::wasPressed(void) {
    if (!digitalRead(BTN)) { //Button is not pressed
        newstate = LOW;
        pstate = LOW;
    } else {
        if (newstate == LOW) {
            newstate = HIGH;
            pressTime = millis();
        } else {
            if (pstate == LOW) {
                if ((millis() - pressTime) > BTN_SHORT_PRESS) {
                    //Serial.println("ShortPress!");
                    pstate = HIGH;
                    return 1;
                }
            } else {
                if ((millis() - pressTime) > BTN_LONG_PRESS) {
                    pressTime = millis();
                    //Serial.println("LongPress!");
                    return 2;
                }
            }
        }
    }
    return 0;
}
