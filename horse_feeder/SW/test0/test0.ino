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

#define TEXT_BUF 255
uint8_t text_length = 0;
char text_content[TEXT_BUF];

M590 gsm(text_content);

void setup() {
    Serial1.begin(115200);
    while (!Serial1); // Wait for Serial to initialize
    Serial1.println("Restarted DEBUG");
    gsm.begin(115200, &Serial); //connect to M590 with 9600 baud, RX pin 3, TX pin 2
    gsm.enableDebugSerial(&Serial1); //optionally output debug information on Serial
    gsm.initialize("0000"); //enter your PIN here, leave empty for no pin
    rtc.setDate(15, 2, 2025, 20, 10, 50);
    feeder.setRation(1);
    rtc.printDate();
    rtc.printAlarms();
    //rtc.setAlarm(0, 20, 11);
    //rtc.setAlarm(1, 20, 12);
    //rtc.setAlarm(2, 20, 13);


    //feeder.startDistribution();
}

void loop() {
    gsm.loop(); //the loop method needs to be called often
    rtc.printDate();
    rtc.update();
    rtc.getAlarmTime(0);
    int ringingAlarm = rtc.checkAlarms();
    if (ringingAlarm != -1) {
        Serial1.print(F("Declenchement distribution "));
        Serial1.write('A' + ringingAlarm);
        Serial1.println();
        rtc.clearAlarm(ringingAlarm);
        feeder.startDistribution();
        text_length = 0;
        text_length += snprintf(text_content + text_length, TEXT_BUF - text_length, "Distribution %c", 'A' + ringingAlarm);
        while (Rstatus == ONGOING) {
            RationStatus Rstatus = feeder.update();
            delay(50);
        }
        if (Rstatus == COMPLETED) {
            text_length += snprintf(text_content + text_length, TEXT_BUF - text_length, " effectuee avec succes.");
        } else if (Rstatus == TIMED_OUT_M1) {
            text_length += snprintf(text_content + text_length, TEXT_BUF - text_length, " ratee: pbm moteur 1 !");
        } else if (Rstatus == TIMED_OUT_M2) {
            text_length += snprintf(text_content + text_length, TEXT_BUF - text_length, " ratee: pbm moteur 2 !");
        }
        Serial1.print(text_content);
        if (gsm.queueSMS()) {
            Serial1.println("\tSMS success");
        } else {
            Serial1.println("\tSMS fail");
            gsm.reInit();
        }
    }
    delay(1000); // Wait before starting again
}
