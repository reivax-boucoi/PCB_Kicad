#include "Ration.h"

// **Static instance pointer**
Ration* Ration::instance = nullptr;

// **Interrupt Service Routine (ISR) for INT0 (Motor1)**
void Ration::INT0_isr() {
    if (instance) {
        instance->countM1++;
        // Stop Motor1 if it has distributed the required amount
        if (instance->countM1 >= instance->ration_qty) {
            digitalWrite(instance->motorPin1, LOW); // Stop Motor1
        }
    }
}

// **Interrupt Service Routine (ISR) for INT1 (Motor2)**
void Ration::INT1_isr() {
    if (instance) {
        instance->countM2++;
        // Stop Motor2 if it has distributed the required amount
        if (instance->countM2 >= instance->ration_qty) {
            digitalWrite(instance->motorPin2, LOW); // Stop Motor2
        }
    }
}

// **Constructor - Load ration quantity from EEPROM**
Ration::Ration(uint8_t motorPin1, uint8_t motorPin2) 
    : motorPin1(motorPin1), motorPin2(motorPin2), ration_qty(0), 
      countM1(0), countM2(0), startTime(0), status(ONGOING) {

    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    digitalWrite(motorPin1, LOW); // Ensure motors are off initially
    digitalWrite(motorPin2, LOW);
    instance = this; // Assign instance pointer for ISR access
    pinMode(10,INPUT_PULLUP);
    pinMode(11,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(10), INT0_isr, FALLING); // Enable INT0 (PD2) for Motor1
    attachInterrupt(digitalPinToInterrupt(11), INT1_isr, FALLING); // Enable INT1 (PD3) for Motor2
    loadRationFromEEPROM(); // Load saved ration quantity from EEPROM
    Serial.print("Initialized ration with ");
    Serial.println(ration_qty);
}

// **Destructor**
Ration::~Ration() {
    detachInterrupt(digitalPinToInterrupt(2)); // Disable INT0
    detachInterrupt(digitalPinToInterrupt(3)); // Disable INT1
    digitalWrite(motorPin1, LOW); // Ensure motors are off
    digitalWrite(motorPin2, LOW);
}

// **Load ration quantity from EEPROM**
void Ration::loadRationFromEEPROM() {
    uint8_t stored_ration = EEPROM.read(EEPROM_RATION_ADDR);
    if (stored_ration > 0 && stored_ration < 255) { // Basic validation
        ration_qty = stored_ration;
    }
}

// **Save ration quantity to EEPROM (only if changed)**
void Ration::saveRationToEEPROM() {
    if (EEPROM.read(EEPROM_RATION_ADDR) != ration_qty) { // Avoid unnecessary writes
        EEPROM.write(EEPROM_RATION_ADDR, ration_qty);
    }
}

// **Set ration quantity using a float**
void Ration::setRation(float qty) {
    uint8_t new_ration_qty = static_cast<uint8_t>(qty * RATION_SCALE);
    if (new_ration_qty != ration_qty) { // Only update if changed
        ration_qty = new_ration_qty;
        saveRationToEEPROM(); // Save to EEPROM
        Serial.print("Updated ration to ");
        Serial.println(ration_qty);
    }
}

// **Get ration quantity as a float (inverse calculation)**
float Ration::getRation() const {
    return static_cast<float>(ration_qty) / RATION_SCALE;
}

// **Start ration distribution (Non-blocking)**
void Ration::startDistribution() {
    if (ration_qty == 0) return; // Do nothing if ration is zero

    countM1 = 0; // Reset Motor1 pulse count
    countM2 = 0; // Reset Motor2 pulse count
    digitalWrite(motorPin1, HIGH); // Turn on Motor1
    digitalWrite(motorPin2, HIGH); // Turn on Motor2
    startTime = millis(); // Start timeout counter
    status = ONGOING; // Set status to ongoing
    //Serial.print("Started ration");
}

// **Update function to check for ration completion (Non-blocking)**
RationStatus Ration::update() {
    if (status == COMPLETED || status == TIMED_OUT_M1 || status == TIMED_OUT_M2) {
        return status; // Already finished, return current status
    }

    // Check for timeout
    if ((millis() - startTime) > TIMEOUT_MS) {
        if (countM1 < ration_qty) {
            status = TIMED_OUT_M1;
        } else if (countM2 < ration_qty) {
            status = TIMED_OUT_M2;
        }
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
    }

    // Check if both motors have completed their ration
    if (countM1 >= ration_qty && countM2 >= ration_qty) {
        status = COMPLETED;
    }

    return status;
}
