#ifndef RATION_H
#define RATION_H

#include <Arduino.h>
#include <EEPROM.h>  // Include EEPROM library

#define TIMEOUT_MS 10000       // Timeout in milliseconds (5 seconds)
#define EEPROM_RATION_ADDR 0  // EEPROM address to store ration quantity
#define EEPROM_RATIONGain_ADDR 1  // EEPROM address to store ration gain

enum RationStatus {
    ONGOING,      // Distribution is currently happening
    COMPLETED,    // Distribution completed successfully
    TIMED_OUT_M1, // Timeout occurred for Motor1
    TIMED_OUT_M2, // Timeout occurred for Motor2
    TIMED_OUT_M12  // Timeout occurred for Motor1&2
};

class Ration {
private:
    uint8_t motorPin1;    // Motor 1 control pin
    uint8_t motorPin2;    // Motor 2 control pin
    unsigned long startTime; // Time when distribution starts
    RationStatus status;  // Current distribution status

    static Ration* instance; // Static pointer to access class in ISR
    static void INT0_isr();  // Interrupt Service Routine for Motor1 (INT0)
    static void INT1_isr();  // Interrupt Service Routine for Motor2 (INT1)

    void loadRationFromEEPROM(); // Load ration from EEPROM
    void saveRationToEEPROM();   // Save ration to EEPROM
    void saveGainToEEPROM();    //Save gain to EEPROM

public:
    Ration(uint8_t motorPin1, uint8_t motorPin2); // Constructor
    ~Ration(); // Destructor

    void setRation(uint8_t qty);  // Set ration quantity
    void setGain(uint8_t g);  // Set ration gain
    uint8_t ration_qty;   // Number of INT0/INT1 interrupts before stopping
    uint8_t ration_gain;   //volume to # of INT scaling factor, can be updated via GAIN?/Gain x
    volatile uint8_t countM1; // Count of interrupts for Motor1 (INT0)
    volatile uint8_t countM2; // Count of interrupts for Motor2 (INT1)
    void startDistribution();   // Start ration distribution
    RationStatus update();      // Check and return current distribution status
};

#endif
