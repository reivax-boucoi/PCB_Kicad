#include "utils.h"
#include "IR_cmd.h"
#include "Accelero.h"
//#include "Animations.h"


#define ACC_POLL_RATE 10 //in ms
#define PSU_REFRESH_RATE 7 //in s
#define PSU_REFRESH_CNT (PSU_REFRESH_RATE*1000/ACC_POLL_RATE)

boolean oldState = LOW;
uint32_t pTime = 0;
uint16_t psu_refresh_counter = 0;
ACC* acc;

void setup() {
    IO_initialize();
    LEDs_init();
    acc = new ACC(200, 8);
    Serial.begin(115200);
    //    while (!Serial) {}
    Serial.println("Hello!");
    LEDs_setColor(0xFF0000);
    _delay_ms(250);
    LEDs_setColor(0x00FF00);
    _delay_ms(250);
    LEDs_setColor(0x0000FF);
    _delay_ms(250);
    LEDs_setColor(0x000000);
}

void loop() {

    if (millis() - pTime > ACC_POLL_RATE) {
        pTime = millis();
        //      Serial.println(acc->getY());
        acc->getY();
        //acc->printRaw();
        //acc->printPeriod();
        if (acc->newHalfCycleFlag == true) {
            acc->newHalfCycleFlag = false;
            if (acc->cycleState == true) {
                //LEDs_setColor(0x000000);
            } else {
                //LEDs_setColor(0xFF0000);
            }
        }
        //acc.print();

        if (++psu_refresh_counter > PSU_REFRESH_CNT) {
            psu_refresh_counter = 0;
            supply_ON();

        }
        myAnimations->update();

        switch (myBtn.pressed()) {
            case 2:
                supply_OFF();
                break;
            case 1:
                myAnimations->nextAnim(true);
                break;
            default:
                break;
        }
    }
    oldState = newState;
}
IR_poll();
}
