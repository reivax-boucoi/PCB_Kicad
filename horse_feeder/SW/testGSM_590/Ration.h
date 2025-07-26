#ifndef RATION_H
#define RATION_H

#include <Arduino.h>
#include <EEPROM.h>  // Include EEPROM library

#define LAP_TIMEOUT_MS 2500       // Timeout for 1 lap in ms
#define LAP_MINTIME_MS 200       // Min plausible time for 1 lap in ms
#define EEPROM_RATION_ADDR 0  // EEPROM address to store ration quantity
#define EEPROM_RATIONGain_ADDR 1  // EEPROM address to store ration gain
#define RATION_QTY_DFLT 3           //default ration qty (if blank eeprom contents)
#define RATION_GAIN_DFLT 1          //default ration gain (if blank eeprom contents)
#define MOTOR_SPEED_RAMP 5          //motor acceleration
#define MOTOR_START_SPEED 20        //motor turn ON initial speed
#define MOTOR_MAX_SPEED 255         //motor max allowed speed
#define MOTOR_APPROACH_SPEED (MOTOR_MAX_SPEED/1.5)  //motor speed at last turn before stopping/reversing
#define PROXI_PWR_DELAY 5 //time for proxi sensor powerup before takng any readings

#define PROXI_PWR PIN_PC4
#define MOT_PWM PIN_PD4
#define MOT_DIR PIN_PD5
#define MOT1_PROXI PIN_PD3
#define MOT2_PROXI PIN_PD2

enum RationStatus {
    ONGOING_M1=0,      // Distribution is currently happening 
    ONGOING_M2=1,      // Distribution is currently happening 
    CHANGING_DIR=2,
    COMPLETED=3,    // Distribution completed successfully
    TIMED_OUT_M1=4, // Timeout occurred for Motor1
    TIMED_OUT_M2=5, // Timeout occurred for Motor2
    TIMED_OUT_M12=6  // Timeout occurred for Motor1&2
};

class Ration {
private:
    unsigned long startTime; // Time when distribution starts
    RationStatus status;  // Current distribution status

    static Ration* instance; // Static pointer to access class in ISR
    static void INT1_isr();  // Interrupt Service Routine for Motor2 (INT1)
    bool modeBourrageActive=false;
    void loadRationFromEEPROM(); // Load ration from EEPROM
    void saveRationToEEPROM();   // Save ration to EEPROM
    void saveGainToEEPROM();    //Save gain to EEPROM*/

public:
    Ration(); // Constructor
    ~Ration(); // Destructor
    initialize();//load ration from eeprom
    void setRation(uint16_t qty);  // Set ration quantity
    void setGain(uint16_t g);  // Set ration gain
    void modeBourrage(bool active);
    uint16_t ration_qty;   // Number of INT0/INT1 interrupts before stopping
    uint16_t effective_ration_qty;
    uint16_t ration_gain;   //volume to # of INT scaling factor, can be updated via GAIN?/Gain x
    volatile uint16_t countM1; // Count of interrupts for Motor1
    volatile uint16_t countM2; // Count of interrupts for Motor2
    volatile uint8_t mot_speed;
    volatile uint8_t mot_max_speed;
    
    void startDistribution();   // Start ration distribution
    void stopMotor();
    void stopAll();
    void reverseMotorDir();
    void startMotor(bool dir);
    RationStatus update();      // Check and return current distribution status
};

#endif
