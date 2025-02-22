#include "Ration.h"

// **Static instance pointer**
Ration* Ration::instance = nullptr;

// **Interrupt Service Routine (ISR) for INT0 (Motor1)**
void Ration::INT0_isr() {
    if (instance) {
        if (instance->modeBourrageActive)return;
        instance->countM1++;
        // Stop Motor1 if it has distributed the required amount
        if (instance->countM1 >= instance->ration_qty) {
            digitalWrite(MOT1_PWM, LOW); // Stop Motor1
        }
    }
}

// **Interrupt Service Routine (ISR) for INT1 (Motor2)**
void Ration::INT1_isr() {
    if (instance) {
        if (instance->modeBourrageActive)return;
        instance->countM2++;
        // Stop Motor2 if it has distributed the required amount
        if (instance->countM2 >= instance->ration_qty) {
            digitalWrite(MOT2_PWM, LOW); // Stop Motor2
        }
    }
}

// **Constructor - Load ration quantity from EEPROM**
Ration::Ration() {
    ration_qty = 0;
    countM1 = 0;
    countM2 = 0;
    startTime = 0;
    status = COMPLETED;

    pinMode(MOT1_PWM, OUTPUT);
    pinMode(MOT2_PWM, OUTPUT);
    stopMotors();
    instance = this; // Assign instance pointer for ISR access
    pinMode(MOT1_PROXI, INPUT_PULLUP);
    pinMode(MOT2_PROXI, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(MOT1_PROXI), INT0_isr, FALLING); // Enable INT0 (PD2) for Motor1
    attachInterrupt(digitalPinToInterrupt(MOT2_PROXI), INT1_isr, FALLING); // Enable INT1 (PD3) for Motor2
    loadRationFromEEPROM(); // Load saved ration quantity from EEPROM
    Serial1.print(F("Initialized ration with "));
    Serial1.println(ration_qty);
}

// **Destructor**
Ration::~Ration() {
    detachInterrupt(digitalPinToInterrupt(MOT1_PROXI)); // Disable INT0
    detachInterrupt(digitalPinToInterrupt(MOT2_PROXI)); // Disable INT1
    stopMotors();
}

// **Load ration quantity from EEPROM**
void Ration::loadRationFromEEPROM() {
    uint8_t stored_ration = EEPROM.read(EEPROM_RATION_ADDR);
    if (stored_ration > 0 && stored_ration < 255) { // Basic validation
        ration_qty = stored_ration;
    }
    ration_gain = EEPROM.read(EEPROM_RATIONGain_ADDR);
}

// **Save ration quantity to EEPROM (only if changed)**
void Ration::saveRationToEEPROM() {
    if (EEPROM.read(EEPROM_RATION_ADDR) != ration_qty) { // Avoid unnecessary writes
        EEPROM.write(EEPROM_RATION_ADDR, ration_qty);
    }
}
void Ration::saveGainToEEPROM() {
    if (EEPROM.read(EEPROM_RATIONGain_ADDR) != ration_gain) { // Avoid unnecessary writes
        EEPROM.write(EEPROM_RATIONGain_ADDR, ration_gain);
    }
}

void Ration::setGain(uint8_t g) {
    ration_gain = g;
    saveGainToEEPROM();
}
// **Set ration quantity using a float**
void Ration::setRation(uint8_t qty) {
    uint8_t new_ration_qty = qty;
    if (new_ration_qty != ration_qty) { // Only update if changed
        ration_qty = new_ration_qty;
        saveRationToEEPROM(); // Save to EEPROM
        Serial1.print(F("Updated ration to "));
        Serial1.println(ration_qty);
    }
}

// **Start ration distribution (Non-blocking)**
void Ration::startDistribution() {
    if (ration_qty == 0) return; // Do nothing if ration is zero

    countM1 = 0; // Reset Motor1 pulse count
    countM2 = 0; // Reset Motor2 pulse count
    startMotors();
    startTime = millis(); // Start timeout counter
    status = ONGOING; // Set status to ongoing
    //Serial.print("Started ration");
}

void Ration::startMotors() {
    digitalWrite(MOT1_PWM, HIGH); // Turn on Motor1
    digitalWrite(MOT2_PWM, HIGH); // Turn on Motor2
}
void Ration::stopMotors() {
    digitalWrite(MOT1_PWM, LOW);
    digitalWrite(MOT2_PWM, LOW);
}
// **Update function to check for ration completion (Non-blocking)**
RationStatus Ration::update() {
    if (status == COMPLETED || status == TIMED_OUT_M1 || status == TIMED_OUT_M2) {
        return status; // Already finished, return current status
    }

    // Check for timeout
    if ((millis() - startTime) > TIMEOUT_MS) {
        if (countM1 < ration_qty) {
            if (countM2 < ration_qty) status = TIMED_OUT_M12;
            else status = TIMED_OUT_M1;
        } else if (countM2 < ration_qty) {
            status = TIMED_OUT_M2;
        }
        stopMotors();
    }

    // Check if both motors have completed their ration
    if (countM1 >= ration_qty && countM2 >= ration_qty) {
        status = COMPLETED;
    }

    return status;
}


void Ration::modeBourrage(bool active) {
    modeBourrageActive = active;
    if (!active) {
        stopMotors();
        status = COMPLETED;
        countM1 = 0; // Reset Motor1 pulse count
        countM2 = 0; // Reset Motor2 pulse count
    }
}
