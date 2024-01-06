#include "utils.h"
#include "IR_cmd.h"
#include "Accelero.h"
#include "Animations.h"


#define ACC_POLL_RATE 10 //in ms
#define PSU_REFRESH_RATE 7 //in s
#define PSU_REFRESH_CNT (PSU_REFRESH_RATE*1000/ACC_POLL_RATE)

boolean oldState = LOW;
int mode = 0;    // Currently-active animation mode, 0-9
uint32_t pTime = 0;
uint16_t psu_refresh_counter = 0;
ACC* acc;

void setup() {
    IO_initialize();
    LEDs_init();
    acc = new ACC(200, 8);
    Serial.begin(115200);
    /*  while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
        }*/
    LEDs_setColor(0xF0F0F0);
}

void loop() {

    if (millis() - pTime > ACC_POLL_RATE) {
        pTime = millis();
        //      Serial.println(acc->getY());
        acc->getY();
        acc->printRaw();
        //acc->printPeriod();
        digitalWrite(LED_ONBRD, !digitalRead(LED_ONBRD));
        //acc.print();
        if (++psu_refresh_counter > PSU_REFRESH_CNT) {
            psu_refresh_counter = 0;
            supply_ON();
        }


        boolean newState = digitalRead(BTN);
        // Check if state changed from low to hi (button press).
        if ((newState == HIGH) && (oldState == LOW)) {
            // Short delay to debounce button.
            delay(20);
            // Check if button is still low after debounce.
            newState = digitalRead(BTN);
            if (newState == HIGH) {     // Yes, still hi
                if (++mode > 7) mode = 0;
                Serial.println("Mode" + mode);
                LEDS_showMode(mode);/*
                switch (mode) {
                    case 0:
                        LEDs_setColor(0x0000FF);
                        break;
                    case 1:
                        LEDs_setColor(0x00FF00);
                        break;
                    case 2:
                        LEDs_setColor(0xFF0000);
                        break;
                    case 3:
                        LEDs_setColor(0x00FFFF);
                        break;
                    case 4:
                        LEDs_setColor(0xFFFF00);
                        break;
                    case 5:
                        LEDs_setColor(0xFF00FF);
                        break;
                    case 6:
                        LEDs_setColor(0xFFFFFF);
                        break;
                    case 7:
                        LEDs_setColor(0x000000);
                        break;
                    case 8:
                        supply_OFF();
                        break;
                    default:
                        break;

                }*/
                digitalWrite(LED_ONBRD, !digitalRead(LED_ONBRD));

            }
        }
        oldState = newState;
    }
    IR_poll();
}
