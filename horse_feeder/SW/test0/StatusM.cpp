#include "StatusM.h"


StatusM::StatusM(DateTime now) {
    for (uint8_t i = 0; i < ERRORTypeNB; i++) {
        err_cnt[i] = EEPROM.read(EEPROM_STATUS_ADDR + i);
    }
    startupTime = ((now.year - 2025) * 365 + now.month * 31 + now.day) * 24 + now.hours;

    pinMode(BATT_MON, INPUT);
    pinMode(BTN_USR1, INPUT_PULLUP);
    pinMode(BTN_USR2, INPUT_PULLUP);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    pinMode(LED_R, OUTPUT);
    setLED(0, LED_ON);
    setLED(1, LED_OFF);
    setLED(2, LED_OFF);
    setLED(3, LED_OFF);
    ledFastTime = millis();
    ledSlowTime = 0;
    buttonStates = digitalRead(BTN_USR1) << 1 | digitalRead(BTN_USR2);

}

void StatusM::setLED(uint8_t led, LED_STATUS s) {
    leds[led] = s;
    if (s == LED_ON) {
        digitalWrite(LEDS_pinMap[led], HIGH);
    } else if (s == LED_OFF) {
        digitalWrite(LEDS_pinMap[led], LOW);
    }
}

void StatusM::animateLEDs() {
    if ((millis() - ledFastTime) < LED_FASTBLINK_PERIOD)return;
    ledFastTime = millis();
    ledSlowTime++;
    for (uint8_t l = 0; l < 4; l++) {
        if ( leds[l] == LED_FASTBLINK || ( leds[l] == LED_SLOWBLINK && ledSlowTime == LED_SLOWBLINK_PERIOD)) {
            digitalWrite(LEDS_pinMap[l], !digitalRead(LEDS_pinMap[l]));
        }
    }
}

void StatusM::getReport(char *text_content) {
    uint16_t uptime = ((nowTime.year - 2025) * 365 + nowTime.month * 31 + nowTime.day) * 24 + nowTime.hours;
    uptime -= startupTime;
    uint8_t text_length = 0;
    uint8_t SMS_TEXT_BUF = 255;
    text_length += sprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("SIM SW restart: %u, Mot:%u/%u/%u, RTC: %u, "), err_cnt[SIM_ERROR], err_cnt[M1_ERROR], err_cnt[M2_ERROR], err_cnt[M12_ERROR], err_cnt[RTC_ERROR]);
    text_length += sprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("%ud,%uh"), uptime / 24, uptime % 24);
    text_length += sprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("%d/%d/%d, %dh%02d"), nowTime.day, nowTime.month, nowTime.year, nowTime.hours, nowTime.minutes);
}

void StatusM::resetStats() {
    for (uint8_t i = 0; i < ERRORTypeNB; i++) {
        err_cnt[i] = 0;
        EEPROM.update(EEPROM_STATUS_ADDR + i, 0);
    }
}

void StatusM::update(DateTime now) {
    nowTime = now;
    batt_level = (batt_level * 15 + (analogRead(BATT_MON) * BATT_ADC_GAIN)) / 16;
}


void StatusM::increaseErrorCnt(ErrorType err) {
    err_cnt[err]++;
    EEPROM.update(EEPROM_STATUS_ADDR + err, err_cnt[err]);
}


uint8_t StatusM::handleButtons() { //returns 0: no buttons, 1: green pressed, 2: green depressed, 3: yellow pressed
    if ((buttonStates & 0x01) != digitalRead(BTN_USR2)) {
        uint8_t cntr = (buttonStates >> 2) & 0x7;
        if (cntr == 7) {
            buttonStates = (buttonStates & 0b11100010) | digitalRead(BTN_USR2);
            if (! (buttonStates & 0x01)) {
                //Button Yellow pressed
                return 3;
            }
        } else {
            cntr++;
            buttonStates = (buttonStates & 0b11100011) | ((cntr << 2) & 0b11100);
        }
    }
    if (((buttonStates & 0x02) >> 1) != digitalRead(BTN_USR1)) {
        uint8_t cntr = (buttonStates >> 5) & 0x7;
        if (cntr == 7) {
            buttonStates = (buttonStates & 0b00011101) | digitalRead(BTN_USR1) << 1;
            if ( (buttonStates & 0x02)) {
                //Green button De-pressed
                return 2;
            } else {
                //Green Button pressed
                return 1;
            }
        } else {
            cntr++;
            buttonStates = (buttonStates & 0b00011111) | ((cntr << 5) & 0b11100000);
        }
    }
}
