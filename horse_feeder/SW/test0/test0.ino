#include "Ration.h"
#include "Horaires.h"

#define BATT_MON PA0
#define MOT1_I PA1
#define MOT2_I PA2
#define LED_B PA3
#define LED_G PA4
#define LED_Y PA5
#define LED_R PA6
#define RTC_SQW PB2
#define BTN_USR1 PC2
#define BTN_USR2 PC3
#define PROXI_PWR PC4
#define SIM_PWR PC5
#define MOT1_PWM PD4
#define MOT2_PWM PD5
#define SIM_RST PD6

Ration feeder(MOT1_I, MOT2_I);
Horaires rtc;

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for Serial to initialize

    feeder.setRation(10);

    rtc.setAlarm(0, 7, 30);
    rtc.setAlarm(1, 12, 0);
    rtc.setAlarm(2, 18, 45);

    feeder.startDistribution();
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
    delay(500); // Wait before starting again
}
