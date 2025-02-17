#include "CMDParser.h"




Parser::Parser(M590 *gsm, Horaires *rtc, Ration *feeder) {
    _gsm = gsm;
    _rtc = rtc;
    _feeder = feeder;
    _gsm->_text_ptr = text_content;
}
void Parser::update() {
    uint8_t nbMsg = _gsm->newSMSAvailable();
    while (nbMsg-- > 0) {
        parse(_gsm->getSMS());
    }
}

void Parser::parse(String msg) {
    msg = collapseSpaces(msg);// Remove leading, trailing and duplicate whitespace
    msg.toLowerCase();  //uniform case
    int8_t spaceIndex1 = msg.indexOf(' ');
    if (msg.endsWith("?")) {
        msg.remove(msg.length() - 1);
        if (msg.charAt(msg.length() - 1) == ' ')msg.remove(msg.length() - 1);
        spaceIndex1 = msg.indexOf(' ');
        if (spaceIndex1 == -1) {
            //Serial1.println("Getter with no space detected");
            if (msg == "status") {
                statusQuery();
            } else if (msg == "date") {
                dateQuery();
            } else if (msg == "ration") {
                rationQuery();
            } else if (msg == "gain") {
                gainQuery();
            } else if (msg == "status") {
                statusQuery();
            } else if (msg == "sstatus") {
                advancedStatusQuery();
            } else {
                parseFailed("Unknown keyword for query with no arguments: \"" + msg + "\"");
            }
        } else {
            //Serial1.println("Getter with space detected");
            String keyword = msg.substring(0, spaceIndex1);
            String restOfString = msg.substring(spaceIndex1 + 1);
            if (keyword == "horaire") {
                int alarmNB = restOfString[0] - 'a';
                uint8_t MAXALARMS = 3; //TODO
                if (alarmNB >= 0 && alarmNB < MAXALARMS)horaireQuery(alarmNB);
                else parseFailed("Numero d'horaire invalide: [A : " + String((char)('A' + MAXALARMS - 1)) + "]");
            } else {
                parseFailed("Unknown keyword for query with 1 argument \"" + keyword + "\"");
            }
        }
    } else if (spaceIndex1 == -1) {// Case: No space, just "Keyword"
        //Serial1.println("Setter with no space detected");
        if (msg == "statusr") {
            statusReset();
        } else if (msg == "vacances" || msg == "vacance") {
            modeVacancesSet();
        } else if (msg == "semaine") {
            modeSemaineSet();
        } else if (msg == "off") {
            modeManuelSet();
        } else if (msg == "manuel") {
            manualDistribute();
        } else {
            parseFailed("Unknwon keyword for single word setter \"" + msg + "\"");
        }
    } else {
        String keyword = msg.substring(0, spaceIndex1);
        String restOfString = msg.substring(spaceIndex1 + 1);
        spaceIndex1 = restOfString.indexOf(' ');
        if (spaceIndex1 == -1) {
            //Serial1.println("Setter with 1 argument detected");
            if (keyword == "ration") {
                if (restOfString.charAt(restOfString.length() - 1) == 'l')restOfString.remove(restOfString.length() - 1);
                restOfString.replace(',', '.');
                uint16_t qty = uint16_t(restOfString.toFloat() * 100.0);
                rationSet(qty);
            } else if (keyword == "gain") {
                gainSet(restOfString.toInt());
            } else if (keyword == "numero") {
                if (restOfString.length() == 12 || restOfString.length() == 10)setNumber(restOfString);
                else parseFailed("New number must be either 10 or 12 digits, not " + String(restOfString.length()));
            }  else if (keyword == "pin") {
                if (restOfString.length() > 3)_gsm->setSIMPin(restOfString);
                else parseFailed("New PIN must at least be 4 digits long");
            } else {
                parseFailed("Unknown keyword for setter with 1 argument \"" + keyword + "\"");
            }
        } else {
            //Serial1.println("Setter with 2 arguments detected");
            String arg1 = restOfString.substring(0, spaceIndex1);
            String arg2 = restOfString.substring(spaceIndex1 + 1);
            if (keyword == "date") {
                dateSet(arg1, arg2);
            } else if (keyword == "horaire") {
                int alarmNB = restOfString[0] - 'a';
                uint8_t MAXALARMS = 3; //TODO
                if (alarmNB < 0 && alarmNB > MAXALARMS) {
                    parseFailed("Numero d'horaire invalide: [A : " + String((char)('A' + MAXALARMS - 1)) + "]");
                    return;
                }
                spaceIndex1 = arg2.indexOf(' ');
                String time = "";
                bool state = true;
                if (spaceIndex1 > -1) {
                    String arg2a = arg2.substring(0, spaceIndex1);
                    String arg2b = arg2.substring(spaceIndex1 + 1);
                    if (isDigit(arg2[0])) {
                        time = arg2a;
                        arg2 = arg2b;
                    } else {
                        time = arg2b;
                        arg2 = arg2a;
                    }
                } else {
                    if (isDigit(arg2[0])) time = arg2;
                }
                if (arg2 == "off") {
                    horaireSet(alarmNB, 0, time);
                } else if (arg2 == "on") {
                    horaireSet(alarmNB, 1, time);
                } else {
                    horaireSet(alarmNB, state, time);
                }
            } else {
                parseFailed("Unknown keyword for setter with 1 argument \"" + keyword + "\"");
            }
        }
    }
}



void Parser::dateQuery() {
    DateTime d = _rtc->getDate();
    sprintf_P(text_content, PSTR("%d/%d/%d, %dh%02d:%02d"), d.day, d.month, d.year, d.hours, d.minutes, d.seconds);
    _gsm->queueSMS();
}

void Parser::dateSet(String date, String time) {
    int dm = date.indexOf('/');
    if (dm == -1)return;
    String dayStr = date.substring(0, dm);
    uint8_t day = dayStr.toInt();
    if (day > 31)return;
    String remainingStr = date.substring(dm + 1);
    dm = remainingStr.indexOf('/');
    if (dm == -1)return;
    String monthStr = remainingStr.substring(0, dm);
    String yearStr = remainingStr.substring(dm + 1);
    uint8_t month = monthStr.toInt();
    if (month > 12)return;
    uint16_t year = yearStr.toInt();
    if (year > 2200 || year < 2000)return;

    dm = time.indexOf('h');
    if (dm == -1)return;
    String hourStr = time.substring(0, dm);
    String minStr = time.substring(dm + 1);
    uint8_t hour = hourStr.toInt();
    uint8_t mins = minStr.toInt();
    if (hour > 23)return;
    if (mins > 59)return;

    _rtc->setDate(day, month, year, hour, mins, 0);
    dateQuery();
}

void Parser::rationQuery() {
    uint16_t a = _feeder->ration_qty * 100 / _feeder->ration_gain;
    sprintf_P(text_content, PSTR("Ration reglée à %u.%02uL(%up)"), a / 100, a % 100, _feeder->ration_qty);
    _gsm->queueSMS();
}

void Parser::rationSet(uint16_t qty) {
    uint16_t q = qty * _feeder->ration_gain / 100;
    if (q > 254)_feeder->setRation(254);
    else _feeder->setRation(q);
    rationQuery();
}

void Parser::statusQuery() {
    text_length = 0;
    if (_rtc->lastAlarmRung > -1) {
        Alarm al = _rtc->getAlarmTime(_rtc->lastAlarmRung);
        text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("Dernière distribution a eu lieu à %uh%02u, "), al.hours, al.minutes);
    }

    DateTime currentDate =  _rtc->getDate();
    uint16_t currentTime = currentDate.hours * 60 + currentDate.minutes;
    uint16_t minNextTime = 24 * 60;
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        Alarm al = _rtc->getAlarmTime(i);
        if (al.enabled) {
            uint16_t alarmTime = al.hours * 60 + al.minutes;
            uint16_t delta = (alarmTime - currentTime) % (24 * 60);
            if (delta < minNextTime && delta > 0)minNextTime = delta;
        }
    }
    if (minNextTime == 24 * 60) text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("Pas de prochaine distribution prévue."));
    else text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("Prochaine distribution dans %uh%02u."), minNextTime / 60,minNextTime % 60);
    
    int rssi = -40;//TODO getRSSI();
    uint16_t batt = 12345;//TODO getBatt();
    uint16_t LOW_BATT_TH = 12200; //TODO #define
    uint16_t r = _feeder->ration_qty * 100 / _feeder->ration_gain;
    text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("\r\nRation %u%02uL, RSSI %ddBm, Batterie %u.%02uV (%s)"), r / 100, r % 100, rssi, batt / 1000, (batt % 1000) / 10, batt > LOW_BATT_TH ? PSTR("OK") : PSTR("Faible"));
    _gsm->queueSMS();
}

void Parser::advancedStatusQuery() {
    Serial1.println("Advanced status query called");
}

void Parser::statusReset() {
    Serial1.println("Status reset called");
}

void Parser::horaireQuery(uint8_t alarmNb) {
    Alarm a = _rtc->getAlarmTime(alarmNb);
    sprintf_P(text_content, PSTR(" Horaire %c %S à %uh%02u."), 'A' + alarmNb, a.enabled ? PSTR("activé") : PSTR("désactivé"), a.hours, a.minutes);
    _gsm->queueSMS();
}

void Parser::horaireSet(uint8_t alarmNb, bool state, String time) {
    if (time == "") {
        if (state) _rtc->enableAlarm(alarmNb);
        else _rtc->disableAlarm(alarmNb);
        horaireQuery(alarmNb);
        return;
    }
    int hPos = time.indexOf('h');
    if (hPos == -1) {
        parseFailed("incorrect time provided no H:" + time);
        return;
    }
    String hourStr = time.substring(0, hPos);
    String minStr = time.substring(hPos + 1);
    uint8_t hours = hourStr.toInt();
    uint8_t minutes = minStr.toInt();
    if (hours > 23 || minutes > 59) {
        parseFailed("incorrect time provided H/M OOR:" + time);
        return;
    }
    _rtc->setAlarm(alarmNb, hours, minutes);
    if (!state)_rtc->disableAlarm(alarmNb);
    horaireQuery(alarmNb);
}

void Parser::modeVacancesSet() {
    text_length = 0;
    _rtc->enableAllAlarms();
    text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("Mode auto actif: distributions à "));

    for (uint8_t i = 0; i < MAX_ALARMS - 1; i++) {
        Alarm a = _rtc->getAlarmTime(i);
        text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("%uh%02u, "), a.hours, a.minutes);
    }
    Alarm a = _rtc->getAlarmTime(MAX_ALARMS - 1);
    text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("%uh%02u"), a.hours, a.minutes);
    _gsm->queueSMS();
}

void Parser::modeSemaineSet() {
    _rtc->disableAllAlarms();
    _rtc->enableAlarm(1);
    Alarm a = _rtc->getAlarmTime(1);
    sprintf_P(text_content, PSTR(" Mode semaine actif: distribution à %uh%02u."), a.hours, a.minutes);
    _gsm->queueSMS();
}

void Parser::modeManuelSet() {
    _rtc->disableAllAlarms();
    sprintf_P(text_content, PSTR("Mode auto inactif: toutes les distributions automatiques sont désactivées."));
    _gsm->queueSMS();
}

void Parser::manualDistribute() {
    _feeder->startDistribution();
    while (_feeder->update() == ONGOING) {
        delay(50);
    }
    text_length = 0;
    RationStatus s = _feeder->update();
    text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("Distribution manuelle "));
    if (s == COMPLETED) {
        text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("réalisée avec succès."));
    } else {
        uint8_t moteur = 0;
        switch (s) {
            case TIMED_OUT_M1:
                moteur = 1;
                break;
            case TIMED_OUT_M2:
                moteur = 2;
                break;
            case TIMED_OUT_M12:
                moteur = 12;
                break;
            default:
                moteur = 4;
                break;
        }
        text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("a échoué: pbm moteur %d (%u/%u/%u)"), moteur, _feeder->countM1, _feeder->countM2, _feeder->ration_qty);
    }
    _gsm->queueSMS();
}

void Parser::gainQuery() {
    sprintf_P(text_content, PSTR("Gain set to %u"), _feeder->ration_gain);
    _gsm->queueSMS();
}

void Parser::gainSet(uint8_t gain) {
    uint16_t Pration = _feeder->ration_qty * 1000 / _feeder->ration_gain * gain; //attempt to conserve same target volume with gain change.
    _feeder->ration_qty = Pration / 1000;
    _feeder->setGain(gain);
    gainQuery();
}

void Parser::setNumber(String nb) {
    sprintf_P(text_content, PSTR("Numero set to %s"), nb.c_str());
    _gsm->queueSMS();
    _gsm->setTargetNum(nb);
    sprintf_P(text_content, PSTR("Numero set to %s"), nb.c_str());
    _gsm->queueSMS();
}

void Parser::parseFailed(String errorMsg) {
    Serial1.print(F("Parsing failed: "));
    Serial1.println(errorMsg);
}

String Parser::collapseSpaces(String input) {
    String result = "";
    bool inSpace = false;

    for (uint8_t i = 0; i < input.length(); i++) {
        char currentChar = input.charAt(i);

        if (currentChar != ' ') {
            result += currentChar;  // Add the non-space character
            inSpace = false;
        } else if (!inSpace && result != "") {
            result += ' ';  // Add one space if not already added
            inSpace = true;
        }
    }
    if (result.charAt(result.length() - 1) == ' ')result.remove(result.length() - 1);
    return result;
}


void Parser::sendRationStatus(uint8_t alarmIdx) {
    text_length = 0;
    RationStatus s = _feeder->update();
    text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("Distribution de %dh%02d "), _rtc->getAlarmTime(alarmIdx).hours, _rtc->getAlarmTime(alarmIdx).minutes);
    if (s == COMPLETED) {
        text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("distribuée avec succès."));
    } else {
        uint8_t moteur = 0;
        switch (s) {
            case TIMED_OUT_M1:
                moteur = 1;
                break;
            case TIMED_OUT_M2:
                moteur = 2;
                break;
            case TIMED_OUT_M12:
                moteur = 12;
                break;
            default:
                moteur = 4;
                break;
        }
        text_length += snprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("a échoué: pbm moteur %d (%u/%u/%u)"), moteur, _feeder->countM1, _feeder->countM2, _feeder->ration_qty);
    }
    _gsm->queueSMS();
}

//batt=tension en mV
void Parser::sendLowBattery(uint16_t batt) {
    sprintf_P(text_content, PSTR("Batterie faible ! %u.%02uV"), batt / 1000, (batt % 1000) / 10);
    _gsm->queueSMS();
}

void Parser::sendSystemRestarted() {
    DateTime d = _rtc->getDate();
    sprintf_P(text_content, PSTR("Le système a redémarré ! %d/%d/%d, %dh%02d:%02d"), d.day, d.month, d.year, d.hours, d.minutes, d.seconds);
    _gsm->queueSMS();
}
