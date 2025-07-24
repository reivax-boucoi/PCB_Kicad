//ATMEGA644PA running at 16MHz 4V
//Fuses: -U lfuse:w:0xff:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

#include "Ration.h"
#include "Horaires.h"
#include "M590.h"
#include "CMDParser.h"

#define MOT1_I PIN_PA1
#define MOT2_I PIN_PA2
#define RTC_SQW PIN_PB2
#define SIM_PWR PIN_PC5
#define SIM_RST PIN_PD6

Ration feeder;
Horaires rtc;


M590 gsm(NULL);
Parser *SMShandler;//(&gsm, &rtc, &feeder, rtc.getDate());
String input = "";

void setup() {
    Serial1.begin(115200);
    //while (!Serial1); // Wait for Serial to initialize
    delay(1000);
    gsm.begin(115200, &Serial); //connect to M590 with 9600 baud, RX pin 3, TX pin 2
    delay(1000);
    gsm.enableDebugSerial(&Serial1); //optionally output debug information on Serial
    //gsm.initialize("1234"); //enter your PIN here, leave empty for no pin
    //rtc.setDate(19,4,2025,11,49,0);
    rtc.printDate();
    rtc.printAlarms();
    SMShandler = new Parser(&gsm, &rtc, &feeder, rtc.getDate());
    rtc.setAlarm(0, 8, 0);
    rtc.setAlarm(1, 12, 0);
    rtc.setAlarm(2, 19, 0);
    SMShandler->sendSystemRestarted();

    feeder.startDistribution();
    while (feeder.update() == ONGOING) {
        delay(50);
    }

}

void loop() {

    gsm.loop();
    delay(100);
    DateTime now = rtc.update();
    SMShandler->update(now);
    int ringingAlarm = rtc.checkAlarms();
    if (ringingAlarm != -1) {
        Serial1.print(F("Declenchement distribution "));
        Serial1.write('A' + ringingAlarm);
        Serial1.print(" ");
        rtc.clearAlarm(ringingAlarm);
        feeder.startDistribution();
        SMShandler->status.setLED(1, LED_ON);
        while (feeder.update() == ONGOING) {
            delay(50);
        }

        SMShandler->sendRationStatus(ringingAlarm);
    }
    delay(500); // Wait before starting again
    while (Serial1.available() > 0) {
        char c = Serial1.read();
        Serial1.write(c);
        if (c == '\r' || c == '\n') {
            SMShandler->parse(input);
            input = "";
        } else {
            input += c;
        }
    }
}
