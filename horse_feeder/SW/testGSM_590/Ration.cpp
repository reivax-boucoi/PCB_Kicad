#include "Ration.h"

// **Static instance pointer**
Ration* Ration::instance = nullptr;


// **Interrupt Service Routine (ISR) for INT1 (Motor2)**
void Ration::INT1_isr() {
    if (instance) {
        if (instance->modeBourrageActive)return;
        if ((millis() - instance->startTime) < LAP_MINTIME_MS) { //Too short interval between ISRs, discard.
            Serial1.println(F("ISR too soon, discarded"));
            return;
        }
        //noInterrupts();
        instance->startTime = millis();
        if (instance->status == ONGOING_M1) {
            instance->countM1++;
            //Serial1.print(F("ISR M1:"));
            //Serial1.println(instance->countM1);
            if (instance->countM1 >= instance->effective_ration_qty) {
                instance->instance->status = CHANGING_DIR;
            }else if(instance->countM1 == instance->effective_ration_qty-1){//last round, slow down
                instance->mot_max_speed=MOTOR_APPROACH_SPEED;
            }
        } else if (instance->status == ONGOING_M2) {
            instance->countM2++;
            //Serial1.print(F("ISR M2:"));
            //Serial1.println(instance->countM2);
            // Stop Motor2 if it has distributed the required amount
            if (instance->countM2 >= instance->effective_ration_qty) {
                instance->stopAll();
                if (instance->countM1 >= instance->ration_qty) {
                    instance->status = COMPLETED;
                } else {
                    instance->status = TIMED_OUT_M1;
                }
            }else if(instance->countM2 == instance->effective_ration_qty-1){//last round, slow down
                instance->mot_max_speed=MOTOR_APPROACH_SPEED;
            }
        } else {
            Serial1.println(F("unexpected ISR firing"));
        }
        //interrupts();
    }
}

// **Constructor - Load ration quantity from EEPROM**
Ration::Ration() {
    modeBourrageActive = false;
    ration_qty = 0;
    countM1 = 0;
    countM2 = 0;
    startTime = 0;
    status = COMPLETED;

    pinMode(MOT_PWM, OUTPUT);
    pinMode(MOT_DIR, OUTPUT);
    pinMode(PROXI_PWR, OUTPUT);
    analogWrite(MOT_PWM, 0);
    digitalWrite(MOT_DIR, LOW);
    digitalWrite(PROXI_PWR, LOW); //shutdown proxi supply, saves ~6mA
    instance = this; // Assign instance pointer for ISR access
    pinMode(MOT2_PROXI, INPUT);
    attachInterrupt(digitalPinToInterrupt(MOT2_PROXI), INT1_isr, RISING); // Enable INT1 (PD3) for Motor2
    //pinMode(MOT1_PROXI, INPUT);
    //attachInterrupt(digitalPinToInterrupt(MOT1_PROXI), INT0_isr, FALLING); // Enable INT0 (PD2) for Motor1
}
Ration::initialize() {
    loadRationFromEEPROM(); // Load saved ration quantity from EEPROM
    Serial1.print(F("Initialized ration with "));
    Serial1.println(ration_qty);
}

// **Destructor**
Ration::~Ration() {
    //detachInterrupt(digitalPinToInterrupt(MOT1_PROXI)); // Disable INT0
    detachInterrupt(digitalPinToInterrupt(MOT2_PROXI)); // Disable INT1
    stopAll();
}

// **Load ration quantity from EEPROM**
void Ration::loadRationFromEEPROM() {
    ration_qty = EEPROM.read(EEPROM_RATION_ADDR);
    ration_gain = EEPROM.read(EEPROM_RATIONGain_ADDR);
    if (ration_qty == 255) {
        ration_qty = RATION_QTY_DFLT;
        ration_gain = RATION_GAIN_DFLT;
    }
}

// **Save ration quantity to EEPROM (only if changed)**
void Ration::saveRationToEEPROM() {
    if (EEPROM.read(EEPROM_RATION_ADDR) != ration_qty) { // Avoid unnecessary writes
        EEPROM.write(EEPROM_RATION_ADDR, ration_qty);
        Serial1.print(F("Updated ration to "));
        Serial1.println(ration_qty);
    }
}
void Ration::saveGainToEEPROM() {
    if (EEPROM.read(EEPROM_RATIONGain_ADDR) != ration_gain) { // Avoid unnecessary writes
        EEPROM.write(EEPROM_RATIONGain_ADDR, ration_gain);
    }
}

void Ration::setGain(uint16_t g) {
    ration_gain = g;
    saveGainToEEPROM();
}

void Ration::setRation(uint16_t qty) {
    ration_qty = qty;
    saveRationToEEPROM(); // Save to EEPROM
}

// **Start ration distribution (Non-blocking)**
void Ration::startDistribution() {
    if (ration_qty == 0) return; // Do nothing if ration is zero

    countM1 = 0; // Reset Motor1 pulse count
    countM2 = 0; // Reset Motor2 pulse count
    digitalWrite(PROXI_PWR, HIGH);
    delay(PROXI_PWR_DELAY);
    if(digitalRead(MOT2_PROXI)!=HIGH){//need to count 1 additionnal turn since we were not stopped aligned
        effective_ration_qty=ration_qty+1;
        //Serial1.println("not hgih");
    }else{
        effective_ration_qty=ration_qty;
        //Serial1.println("hgih");
    }
    mot_speed = MOTOR_START_SPEED;
    mot_max_speed=MOTOR_MAX_SPEED;
    startTime = millis(); // Start timeout counter
    status = ONGOING_M1; // Set status to ongoing
    analogWrite(MOT_PWM, mot_speed);
}

void Ration::startMotor(bool dir){
    
    digitalWrite(PROXI_PWR, HIGH);
    digitalWrite(MOT_DIR, dir);
    _delay_ms(50);
    mot_speed = MOTOR_START_SPEED;
    mot_max_speed=MOTOR_MAX_SPEED;
    while (mot_speed < (mot_max_speed - MOTOR_SPEED_RAMP)) {
        mot_speed += MOTOR_SPEED_RAMP;
        analogWrite(MOT_PWM, mot_speed);
        _delay_ms(5);
    }
   analogWrite(MOT_PWM, MOTOR_MAX_SPEED);
}


void Ration::stopMotor() {
    while (mot_speed > 2*MOTOR_SPEED_RAMP) {
        mot_speed = mot_speed - 2*MOTOR_SPEED_RAMP;
        analogWrite(MOT_PWM, mot_speed);
        _delay_ms(5);
    }
    _delay_ms(50);
    mot_speed=MOTOR_START_SPEED;
}
void Ration::stopAll() {
    if(mot_speed>MOTOR_START_SPEED)stopMotor();
    analogWrite(MOT_PWM, 0); // Stop Motor    
    digitalWrite(MOT_DIR, LOW);
    digitalWrite(PROXI_PWR, LOW); //shutdown proxi supply, saves ~6mA
}

void Ration::reverseMotorDir() {
    //Serial1.println(F("Reversing"));
    stopMotor();
    analogWrite(MOT_PWM, 0); // Stop Motor    
    digitalWrite(MOT_DIR, HIGH); // Reverse dir
    _delay_ms(500);
      if(digitalRead(MOT2_PROXI)!=HIGH){//need to count 1 additionnal turn since we were not stopped aligned
        effective_ration_qty=ration_qty+1;
    }else{
        effective_ration_qty=ration_qty;
    }
    mot_max_speed=MOTOR_MAX_SPEED;
    analogWrite(MOT_PWM, mot_speed);
    startTime = millis();
    instance->status = ONGOING_M2;
}

// **Update function to check for ration completion (Non-blocking)**
RationStatus Ration::update() {
    if (status == COMPLETED || status == TIMED_OUT_M1 || status == TIMED_OUT_M2 || status == TIMED_OUT_M12) {
        return status; // Already finished, return current status
    }
    if (mot_speed < (mot_max_speed - MOTOR_SPEED_RAMP)) {
        mot_speed += MOTOR_SPEED_RAMP;
        analogWrite(MOT_PWM, mot_speed);
    } else if(mot_speed > mot_max_speed){
        mot_speed = mot_max_speed;
        //Serial1.println(F("Reduced max speed"));
        analogWrite(MOT_PWM, mot_speed);
    }else if (mot_speed < mot_max_speed) {
        mot_speed = mot_max_speed;
        //Serial1.println(F("Reached max speed"));
        analogWrite(MOT_PWM, mot_speed);
    }
    if(status==CHANGING_DIR){
        reverseMotorDir();
    }
    // Check for timeout
    if ((millis() - startTime) > LAP_TIMEOUT_MS) {
        if (countM1 < effective_ration_qty && status==ONGOING_M1) {
            reverseMotorDir();
        } else if (countM2 < effective_ration_qty) {
            if(countM1 < ration_qty){
                status = TIMED_OUT_M12;
            }else{
                status = TIMED_OUT_M2;
            }
            stopAll();
        }
    }
    return status;
}


void Ration::modeBourrage(bool active) {
    modeBourrageActive = active;
    if (!active) {
        stopAll();
        status = COMPLETED;
        countM1 = 0; // Reset Motor1 pulse count
        countM2 = 0; // Reset Motor2 pulse count
    }
}
