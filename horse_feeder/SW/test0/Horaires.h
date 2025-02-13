#ifndef HORAIRES_H
#define HORAIRES_H

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>  // EEPROM for alarm storage

#define DS3231_I2C_ADDRESS 0x68  // I2C address for DS3231 RTC
#define MAX_ALARMS 3             // Maximum number of alarms
#define EEPROM_ALARM_ADDR 10      // EEPROM start address for alarms
#define ALARM_WINDOW 2            // Alarm rings for 2 minutes
#define ALARM_BLANKING_WINDOW 3   // Alarm cannot ring again for 3 minutes after being cleared

// **Struct to store full date and time**
struct DateTime {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

// **Struct to store alarm settings**
struct Alarm {
    uint8_t hours;
    uint8_t minutes;
    bool enabled;
    bool ringing;
};

class Horaires {
public:
    Horaires();                 // Constructor (initializes I2C and loads alarms)
    void setDate(uint8_t day, uint8_t month, uint16_t year, uint8_t hours, uint8_t minutes, uint8_t seconds);
    DateTime getDate();         // Retrieve full date and time
    void printDate();
    void setAlarm(uint8_t alarmNumber, uint8_t hours, uint8_t minutes); // Set & enable an alarm
    Alarm getAlarmTime(uint8_t alarmNumber); // Retrieve alarm time
    void printAlarm(uint8_t alarmNumber);
    void printAlarms();
    void disableAlarm(uint8_t alarmNumber); // Disable an alarm
    void disableAllAlarms();                // Disable all alarms
    void clearAlarm(uint8_t alarmNumber);   // Stop ringing alarm
    int checkAlarms();                      // Return ringing alarm number or -1
    void update();                           // Regularly called in loop to check alarms

private:
    Alarm alarms[MAX_ALARMS];  // Store alarms in RAM (not in EEPROM)
    unsigned long lastClearedTime[MAX_ALARMS]; // Store last cleared time in minutes
    uint8_t bcdToDec(uint8_t val);  // Convert BCD to Decimal
    uint8_t decToBcd(uint8_t val);  // Convert Decimal to BCD
    void loadAlarmsFromEEPROM(); // Load alarms once at startup
    void saveAlarmToEEPROM(uint8_t alarmNumber); // Save alarm to EEPROM
};

#endif
