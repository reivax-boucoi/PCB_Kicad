#include "Ration.h"
#include "Horaires.h"
#include "M590.h"
#include "CMDParser.h"

#define BATT_MON PIN_PA0
#define MOT1_I PIN_PA1
#define MOT2_I PIN_PA2
#define LED_B PIN_PA3
#define LED_G PIN_PA4
#define LED_Y PIN_PA5
#define LED_R PIN_PA6
#define RTC_SQW PIN_PB2
#define BTN_USR1 PIN_PC2
#define BTN_USR2 PIN_PC3
#define PROXI_PWR PIN_PC4
#define SIM_PWR PIN_PC5
#define MOT1_PWM PIN_PD4
#define MOT2_PWM PIN_PD5
#define SIM_RST PIN_PD6

Ration feeder(MOT1_PWM, MOT2_PWM);
Horaires rtc;


M590 gsm(NULL);

Parser SMShandler(&gsm, &rtc,&feeder);
String input = "";

void setup() {
    Serial1.begin(115200);
    while (!Serial1); // Wait for Serial to initialize
    gsm.begin(115200, &Serial); //connect to M590 with 9600 baud, RX pin 3, TX pin 2
    gsm.enableDebugSerial(&Serial1); //optionally output debug information on Serial
    gsm.initialize("0000"); //enter your PIN here, leave empty for no pin
    rtc.printDate();
    rtc.printAlarms();
    //rtc.setAlarm(0, 20, 11);
    //rtc.setAlarm(1, 20, 20);
    //rtc.setAlarm(2, 8, 55);
    SMShandler.sendLowBattery(12435);
    SMShandler.sendSystemRestarted();

}

void loop() {
    gsm.loop();
    rtc.update();
    rtc.getAlarmTime(0);
    int ringingAlarm = rtc.checkAlarms();
    if (ringingAlarm != -1) {
        Serial1.print(F("Declenchement distribution "));
        Serial1.write('A' + ringingAlarm);
        Serial1.print(" ");
        rtc.clearAlarm(ringingAlarm);
        feeder.startDistribution();
        while (feeder.update() == ONGOING) {
            delay(50);
        }
        SMShandler.sendRationStatus(ringingAlarm);
    }
    delay(500); // Wait before starting again
    while (Serial1.available() > 0) {
        char c = Serial1.read();
        if (c == '\r' || c == '\n') {
            SMShandler.parse(input);
            input = "";
        } else {
            input += c;
        }
    }
}
