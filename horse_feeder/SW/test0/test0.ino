#include "Ration.h"
#include "Horaires.h"

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

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for Serial to initialize
    Serial.println("Restarted");
    //rtc.setDate(13,2,2025,20,55,00);
    feeder.setRation(1);

    rtc.printDate();
    rtc.printAlarms();
    //rtc.setAlarm(0, 21, 34);
    //rtc.setAlarm(1, 21, 37);
    //rtc.setAlarm(2, 21, 41);

    //feeder.startDistribution();
}

void loop() {

    rtc.update();
    rtc.getAlarmTime(0);
    int ringingAlarm = rtc.checkAlarms();
    if (ringingAlarm != -1) {
        Serial.print("Alarm ");
        Serial.print(ringingAlarm);
        Serial.println(" is ringing!");
        rtc.clearAlarm(ringingAlarm);
        rtc.printDate();
        feeder.startDistribution();

        while (true) {
            RationStatus Rstatus = feeder.update();
            if (Rstatus == COMPLETED) {
                Serial.println("Ration Distribution Completed Successfully.");
                break;
            } else if (Rstatus == TIMED_OUT_M1) {
                Serial.println("ERROR: Motor1 (M1) Timed Out!");
                break;
            } else if (Rstatus == TIMED_OUT_M2) {
                Serial.println("ERROR: Motor2 (M2) Timed Out!");
                break;
            }
        }

    }
    delay(2000); // Wait before starting again
}
