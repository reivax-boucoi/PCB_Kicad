#include "CMDParser.h"




Parser::Parser() {
}
/*  M590 *gsm, Horaires *rtc,Ration *feeder){

    _gsm=gsm;
    _rtc=rtc;
    _feeder=feeder;*/

void Parser::update() {
    /*  uint8_t nbMsg=gsm->newSMSAvailable();
        while(nbMsg-- > 0){
        parse(gsm->getSMS());
        }*/
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
                uint16_t qty = uint16_t(restOfString.toFloat()*1000.0);
                rationSet(qty);
            } else if (keyword == "gain") {
                gainSet(restOfString.toInt());
            } else if (keyword == "numero") {
                if(restOfString.length()==12 || restOfString.length()==10)setNumber(restOfString);
                else parseFailed("New number must be either 10 or 12 digits, not " + String(restOfString.length()));
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
    Serial1.println("Date query called");
}

void Parser::dateSet(String date, String time) {
    Serial1.print("Date set to: ");
    Serial1.print(date);
    Serial1.print(" Time: ");
    Serial1.println(time);
}

void Parser::rationQuery() {
    Serial1.println("Ration query called");
}

void Parser::rationSet(uint16_t qty) {
    Serial1.print("Ration set to: ");
    Serial1.println(qty);
}

void Parser::statusQuery() {
    Serial1.println("Status query called");
}

void Parser::advancedStatusQuery() {
    Serial1.println("Advanced status query called");
}

void Parser::statusReset() {
    Serial1.println("Status reset called");
}

void Parser::horaireQuery(uint8_t alarmNb) {
    Serial1.print("Horaire query called for N°");
    Serial1.println(alarmNb);
}

void Parser::horaireSet(uint8_t alarmNb, bool state, String time) {
    Serial1.print("Horaire set for N°");
    Serial1.print(alarmNb);
    Serial1.print(", state: ");
    Serial1.print(state ? "ON" : "OFF");
    Serial1.print(", time: ");
    Serial1.println(time);
}

void Parser::modeVacancesSet() {
    Serial1.println("Vacances set");
}

void Parser::modeSemaineSet() {
    Serial1.println("Semaine set");
}

void Parser::modeManuelSet() {
    Serial1.println("Manual mode");
}

void Parser::manualDistribute() {
    Serial1.println("Manual distribution started");
}

void Parser::gainQuery() {
    Serial1.println("Gain query called");
}

void Parser::gainSet(uint8_t gain) {
    Serial1.print("Gain set to: ");
    Serial1.println(gain);
}


void Parser::setNumber(String nb) {
    Serial1.print("Gain set to: " + nb);
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
