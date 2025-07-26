//avrdude -c usbasp -p m644p -B 1.0 -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xFF:m
#include "Ration.h"
#include "Horaires.h"
#include "StatusM.h"
#include "M590.h"
#include "CMDParser.h"

#define MOT1_I PIN_PA1
#define MOT2_I PIN_PA2
#define RTC_SQW PIN_PB2


Horaires rtc;
Ration feeder;
StatusM* status;

M590 sim;
Parser *SMShandler;
String input = "";

void setup() {
    Serial1.begin(115200);
    //while (!Serial1); // Wait for Serial to initialize
    delay(1000);
    Serial1.println(F("\r\n\r\nSystem reset"));

    rtc.initialize();
    feeder.initialize();
    sim.initialize();
    if(sim.status>0){
        Serial1.print(F("SIM init failed: "));
        Serial1.println(sim.status);
    }else{
        Serial1.println(F("SIM init OK"));
    }
    delay(100);
    rtc.printDate();
    rtc.printAlarms();
    SMShandler = new Parser(&sim, &rtc, &feeder, rtc.getDate());
    if (rtc.getAlarmTime(0).hours == 255) {
        rtc.setAlarm(0, 8 , 0);
        rtc.setAlarm(1, 12, 0);
        rtc.setAlarm(2, 19, 0);
        delay(100);
        rtc.printDate();
        rtc.printAlarms();
    }
    SMShandler->sendSystemRestarted();

}

void loop() {

    //gsm.loop();
    DateTime now = rtc.update();
    SMShandler->update(now);

    int ringingAlarm = rtc.checkAlarms();
    if (ringingAlarm != -1) {
        Serial1.print(F("Declenchement distribution "));
        Serial1.write('A' + ringingAlarm);
        Serial1.write(' ');
        rtc.clearAlarm(ringingAlarm);
        feeder.startDistribution();
        status->setLED(LED_BLUEBUTTON, LED_ON);//Distribution ongoing
        while (feeder.update() < 3) {
            delay(15);
        }
        SMShandler->sendRationStatus(ringingAlarm);
    }
    delay(15);
/*
    while (Serial1.available() > 0) {
        char c = Serial1.read();
        Serial1.write(c);
        if (c == '\r' || c == '\n') {
            SMShandler->parse(input);
            input = "";
        } else {
            input += c;
        }
    }*/
}
