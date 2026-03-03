#include "AngleCalc.h"
#include "AngleMeas.h"
#include "StepperControl.h"

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("\r\n\r\nInit start:\r\n");

    rtc_init();
    accelero_init();
    stepper_init();
    pinMode(D5, INPUT_PULLUP);
    pinMode(D6, INPUT_PULLUP);

    Serial.println("\r\nInit complete");
}

void loop() {
    
    unsigned long t = millis();

    if (t > acc_nextPollTime) {
        accelero_update();
    }

    if (t > rtc_nextPollTime) {
        rtc_updateDateTime();

        if (acc_data.valueUpdated == true) {
            Serial.print("Time: ");
            Serial.print(currentDate.hour());
            Serial.print("h");
            Serial.print(currentDate.minute());
            Serial.print("m");
            Serial.print(currentDate.second());
            Serial.print("s\tTarget angle: ");
            Serial.print(sunPos.elevation);
            Serial.print("\tCurrent angle: ");
            Serial.println(acc_data.measured_angle);
            stepper_moveAngle(sunPos.elevation, accelero_getAngle());
        }
    }
    if(digitalRead(D5)==LOW){
        if(digitalRead(D6)==LOW){
            stepper_moveAngle(5,0);
            Serial.println("pos");
        }else{
            stepper_moveAngle(-5,0);
            Serial.println("neg");
        }
    }
}
