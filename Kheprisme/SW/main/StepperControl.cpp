#include "StepperControl.h"

BasicStepperDriver stepper(STEPPER_STEPS_PER_REV, STEPPER_PIN_DIR, STEPPER_PIN_STEP, STEPPER_PIN_EN);
bool stepper_lastDir;

// Function to initialize stepper motor
void stepper_init(){
    stepper_lastDir=false;
    //pinMode(STEPPER_PIN_SLEEP, OUTPUT);
    stepper_wakeup();
    stepper.begin(STEPPER_SPEED, 1);
    stepper.setEnableActiveState(LOW);
    stepper.setSpeedProfile(stepper.LINEAR_SPEED, STEPPER_ACCEL, STEPPER_ACCEL);
}

// Function to move to the target angle (in degrees)
void stepper_moveAngle(double targetAngle, double currentAngle){
    double movement = targetAngle-currentAngle;
    if (abs(movement)<STEPPER_MIN_MOVE_ANGLE){
        //Serial.println("Stepper movement too small, skipping");
        return;
    }
    if(stepper_lastDir != (movement>0)){
        //Serial.println("Stepper: direction change detected !");
        //TODO implement backlash correction here
    }
    stepper_lastDir = movement>0;
    
    stepper.enable();
    stepper.rotate(movement);
    stepper.disable();
}

void stepper_sleep(){
    //digitalWrite(STEPPER_PIN_SLEEP,LOW);
}
void stepper_wakeup(){
    //digitalWrite(STEPPER_PIN_SLEEP,HIGH);
    delay(STEPPER_WAKEUP_TIME);
}
