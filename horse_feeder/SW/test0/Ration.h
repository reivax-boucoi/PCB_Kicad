#ifndef RATION_H
#define RATION_H

#include <Arduino.h>
#include <EEPROM.h>  // Include EEPROM library

#define TIMEOUT_MS 10000       // Timeout in milliseconds (5 seconds)
#define RATION_SCALE 8       // Scaling factor for ration quantity conversion
#define EEPROM_RATION_ADDR 0  // EEPROM address to store ration quantity

enum RationStatus {
    ONGOING,      // Distribution is currently happening
    COMPLETED,    // Distribution completed successfully
    TIMED_OUT_M1, // Timeout occurred for Motor1
    TIMED_OUT_M2  // Timeout occurred for Motor2
};

class Ration {
private:
    uint8_t ration_qty;   // Number of INT0/INT1 interrupts before stopping
    volatile uint8_t countM1; // Count of interrupts for Motor1 (INT0)
    volatile uint8_t countM2; // Count of interrupts for Motor2 (INT1)
    uint8_t motorPin1;    // Motor 1 control pin
    uint8_t motorPin2;    // Motor 2 control pin
    unsigned long startTime; // Time when distribution starts
    RationStatus status;  // Current distribution status

    static Ration* instance; // Static pointer to access class in ISR
    static void INT0_isr();  // Interrupt Service Routine for Motor1 (INT0)
    static void INT1_isr();  // Interrupt Service Routine for Motor2 (INT1)

    void loadRationFromEEPROM(); // Load ration from EEPROM
    void saveRationToEEPROM();   // Save ration to EEPROM

public:
    Ration(uint8_t motorPin1, uint8_t motorPin2); // Constructor
    ~Ration(); // Destructor

    void setRation(float qty);  // Set ration quantity using a float
    float getRation() const;    // Get ration quantity as a float
    void startDistribution();   // Start ration distribution
    RationStatus update();      // Check and return current distribution status
};

#endif
