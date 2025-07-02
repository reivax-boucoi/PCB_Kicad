#include "M590.h"

void display_freeram() {
    Serial1.print(F("- SRAM left: "));
    Serial1.println(freeRam());
}


int freeRam() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0  ? (int)&__heap_start : (int) __brkval);
}


void M590::queueSMS() {
    Serial1.println("queued new sms");
}

M590::M590() {
    pinMode(SIM_RST, INPUT);
    digitalWrite(SIM_RST, LOW);
    status = 255;
    replyNumber.reserve(13);
    response.reserve(255);
    replyNumber = DFLT_PHONE_NUMBER;
}

void M590::togglePWR() {
    digitalWrite(SIM_RST, LOW);
    pinMode(SIM_RST, OUTPUT);
    delay(500);
    pinMode(SIM_RST, INPUT);
    delay(500);
}
uint8_t M590::initialize(uint8_t retries, uint8_t errorCode) {
    display_freeram();
    if (retries == 0) {
        status = errorCode;
        return errorCode;
    }
    M590_SERIAL.begin(115200);
    serial_flush();

    if (sendCommand("AT", "OK")) {
        if (sendCommand("AT+CMGF=1", "OK")) {
            if (sendCommand("AT+CSCS=\"8859-1\"", "OK")) {
                if (sendCommand("AT+CREG?", "+CREG: 0,1", 20000)) {
                    delay(500);
                    status = 0;
                    display_freeram();
                    return 0;

                } else
                    initialize(retries - 1, 4);
            } else
                initialize(retries - 1, 3);
        } else
            initialize(retries - 1, 2);
    } else {
        togglePWR();
        initialize(retries - 1, 1);
    }
}

bool M590::sendCommand(const String& cmd, const String& expected, unsigned long timeout) {

    delay(50);
    if (cmd != "") {
#ifdef DEBUG_EN
        Serial1.print(F("\r\nSMS:\t"));
        Serial1.print(cmd);
        Serial1.print(F("\t\t Resp:\t"));
#endif
        M590_SERIAL.println(cmd);
    }
    delay(50);
    response = "";
    unsigned long start = millis();

    while (millis() - start < timeout) {
        if (M590_SERIAL.available()) {
            char c = (char)M590_SERIAL.read();
#ifdef DEBUG_EN
            if (c != '\r' && c != '\n')
                Serial1.write(c);
            else
                Serial1.write(' ');
#endif
            response += c;
            if (response.indexOf(expected) != -1) {
#ifdef DEBUG_EN
                Serial1.println(F("\tSMS OK"));
#endif
                return true;
            }
        }
    }
#ifdef DEBUG_EN
    Serial1.println(F("\ttimeout"));
#endif
    return false;
}

void M590::readResponse(unsigned long timeout) {
    response = "";
    unsigned long start = millis();
    uint8_t str_len = 0;

    display_freeram();
    while ((millis() - start < timeout) && str_len < 254) {
        while (M590_SERIAL.available()) {
            char c = (char)M590_SERIAL.read();
#ifdef DEBUG_EN
            if (c != '\r' && c != '\n')
                Serial1.write(c);
            else
                Serial1.write(' ');
#endif
            response += c;
            str_len++;
            if (response.indexOf("OK") != -1) {
                return;
            }
        }
    }

    return;
}

uint8_t M590::newSMSAvailable() {
    if (status != 0)return 0;
    delay(150);
    serial_flush();
    M590_SERIAL.println("AT+CPMS?");
    readResponse();

    //Serial1.print(F("newsms response"));
    //Serial1.println(response);
    int idx = response.indexOf("+CPMS:");
    if (idx == -1) {
        status = 11;
        return 0;
    }

    int start = response.indexOf(",", idx);
    int end = response.indexOf(",", start + 1);
    if (start == -1 || end == -1) {
        status = 12;
        return 0;
    }

    String unreadStr = response.substring(start + 1, end);
    return unreadStr.toInt();
    delay(50);
}

String M590::getSMS() {
    if (status != 0)return "";
    delay(50);
    serial_flush();
    M590_SERIAL.println("AT+CMGL=0");//get unread 1st
    readResponse();//'+CMGL: 1,"REC UNREAD","+33605006547","","25/06/29,17:56:10+08"\r\n

    int cmglIndex = response.indexOf("+CMGL:");
    if (cmglIndex == -1) {
        status = 6;
#ifdef DEBUG_EN
        Serial1.print(F("trying delete all"));
#endif
        delay(150);
        M590_SERIAL.println("AT+CMGD=1,4");
        return "";
    }

    //get message index (for further deletion);
    int indexStart = cmglIndex + 6;
    int indexEnd = response.indexOf(",", indexStart);
    if (indexEnd == -1) {
        status = 7;
        return "";
    }

    int msgIndex = response.substring(indexStart, indexEnd).toInt();
    //Get incoming number
    int numberStart = response.indexOf(",", indexEnd + 3);//find start of incoming number
    if (numberStart == -1) {
        status = 8;
        return "";
    }
    int numberEnd = response.indexOf(",", numberStart + 1); //find end of incoming number
    if (numberEnd == -1) {
        status = 9;
        return "";
    }
    replyNumber = response.substring(numberStart + 1, numberEnd);

#ifdef DEBUG_EN
    Serial1.print(F("incoming number:"));
    Serial1.print(replyNumber);
    Serial1.print(F("\tmsg index:"));
    Serial1.println(msgIndex);
#endif

    // Get message content
    int msgStart = response.indexOf("\n", numberEnd);
    int msgEnd = response.indexOf("\r", msgStart + 1);
    if (msgStart == -1 || msgEnd == -1) {
        status = 10;
        return "";
    }

    String ucs2msg = response.substring(msgStart + 1, msgEnd);

    // Delete SMS
    delay(150);
    M590_SERIAL.print("AT+CMGD=");
    M590_SERIAL.println(msgIndex);

    delay(150);
    serial_flush();
    return ucs2msg;
}

bool M590::sendSMS(const String& msg) {
    if (status != 0)return 0;

    if (replyNumber.length() < 10) {
        replyNumber = DFLT_PHONE_NUMBER;
    }

    M590_SERIAL.print(F("AT+CMGS=\""));
    M590_SERIAL.print(replyNumber);
    M590_SERIAL.println(F("\""));
#ifdef DEBUG_EN
    Serial1.print(F("SEND SMS:"));
#endif

    if (!sendCommand("", ">")) {
        Serial1.println(F("Sending SMS got no >"));
        status = 5;
        return false;
    }

    M590_SERIAL.print(LatinEncode(msg));
    serial_flush();
    M590_SERIAL.write(0x1A); // CTRL+Z

    readResponse(7000);
#ifdef DEBUG_EN
    Serial1.print(msg);
#endif
    return response.indexOf("OK") != -1;
}

String M590::LatinEncode(String input) {
    String output = "";
    for (uint16_t i = 0; i < input.length(); i++) {
        unsigned char c = input[i];
        if (c == 0xC3 && i + 1 < input.length()) {
            unsigned char next = input[i + 1];
            switch (next) {
                // Lowercase
                case 0xA0: output += (char)0xE0; break; // à
                case 0xA2: output += (char)0xE2; break; // â
                case 0xA7: output += (char)0xE7; break; // ç
                case 0xA8: output += (char)0xE8; break; // è
                case 0xA9: output += (char)0xE9; break; // é
                case 0xAA: output += (char)0xEA; break; // ê
                case 0xB9: output += (char)0xF9; break; // ù
                default: output += '?'; break; // Unrecognized UTF-8 sequence
            }
            i++; // Skip the second byte of the UTF-8 character
        } else {
            output += (char)c;
        }
    }
    return output;
}

void M590::serial_flush() {
    while (M590_SERIAL.available()) M590_SERIAL.read();
}
