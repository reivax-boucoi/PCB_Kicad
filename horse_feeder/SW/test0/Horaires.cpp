#include "Horaires.h"

// **Constructor: Initializes I2C and loads alarms from EEPROM**
Horaires::Horaires() {
    Wire.begin();  // Initialize I2C
    loadAlarmsFromEEPROM(); // Load saved alarms into RAM

    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        lastClearedTime[i] = 0; // Initialize last cleared times
    }
}

// **Set full date and time on DS3231 RTC**
void Horaires::setDate(uint8_t day, uint8_t month, uint16_t year, uint8_t hours, uint8_t minutes, uint8_t seconds) {
    uint8_t year_short = year % 100; // DS3231 only stores last 2 digits of the year

    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x00);  // Set register pointer to start at Seconds register
    Wire.write(decToBcd(seconds));
    Wire.write(decToBcd(minutes));
    Wire.write(decToBcd(hours));
    Wire.write(decToBcd(1));  // Day of the week (placeholder, DS3231 handles this)
    Wire.write(decToBcd(day));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year_short));
    Wire.endTransmission();
}

// **Get full date and time from DS3231 RTC**
DateTime Horaires::getDate() {
    DateTime currentDate;

    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x00);  // Set register pointer to start at Seconds register
    Wire.endTransmission();

    Wire.requestFrom(DS3231_I2C_ADDRESS, 7);  // Request 7 bytes (seconds, minutes, hours, day, date, month, year)
    if (Wire.available() >= 7) {
        currentDate.seconds = bcdToDec(Wire.read());
        currentDate.minutes = bcdToDec(Wire.read());
        currentDate.hours   = bcdToDec(Wire.read());
        Wire.read(); // Skip day-of-week
        currentDate.day     = bcdToDec(Wire.read());
        currentDate.month   = bcdToDec(Wire.read());
        currentDate.year    = 2000 + bcdToDec(Wire.read()); // DS3231 stores only last 2 digits of year
    }

    return currentDate;
}

void Horaires::printDate(){
    DateTime currentDate=getDate();
    Serial1.print(currentDate.day);
    Serial1.write('/');
    Serial1.print(currentDate.month);
    Serial1.write('/');
    Serial1.print(currentDate.year);
    Serial1.write(',');
    Serial1.print(currentDate.hours);
    Serial1.write('h');
    Serial1.print(currentDate.minutes);
    Serial1.write(':');
    Serial1.print(currentDate.seconds);
    Serial1.println('s');
}

// **Set an alarm time and enable it automatically**
void Horaires::setAlarm(uint8_t alarmNumber, uint8_t hours, uint8_t minutes) {
    if (alarmNumber >= MAX_ALARMS) return; // Ensure valid alarm number

    alarms[alarmNumber] = { hours, minutes, true, false }; // Automatically enable
    saveAlarmToEEPROM(alarmNumber);
}

// **Get an alarm's details**
Alarm Horaires::getAlarmTime(uint8_t alarmNumber) {
    if (alarmNumber >= MAX_ALARMS) return {0, 0, false, false}; // Return default disabled alarm
    return alarms[alarmNumber];
}

void Horaires::printAlarm(uint8_t alarmNumber){
    Serial1.print("Alarme ");
    Serial1.print(alarmNumber);
    if(alarms[alarmNumber].enabled){
        Serial1.print(" Active,");
    }else{
        Serial1.print(" Inactive,");
    }
    Serial1.print(alarms[alarmNumber].hours);
    Serial1.write('h');
    Serial1.println(alarms[alarmNumber].minutes);
}
void Horaires::printAlarms(){
    for(uint8_t i = 0; i < MAX_ALARMS; i++) {
        printAlarm(i);
    }
}

// **Disable an alarm**
void Horaires::disableAlarm(uint8_t alarmNumber) {
    if (alarmNumber >= MAX_ALARMS) return;
    alarms[alarmNumber].enabled = false;
    saveAlarmToEEPROM(alarmNumber);
}

// **Disable all alarms**
void Horaires::disableAllAlarms() {
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        disableAlarm(i);
    }
}

// **Stop a ringing alarm**
void Horaires::clearAlarm(uint8_t alarmNumber) {
    if (alarmNumber >= MAX_ALARMS) return;
    alarms[alarmNumber].ringing = false;
    
    DateTime currentDate=getDate();
    lastClearedTime[alarmNumber] = currentDate.minutes+currentDate.hours*60;
}

// **Check if any alarm is ringing, return alarm number or -1**
int Horaires::checkAlarms() {
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        if (alarms[i].ringing) {
            return i;
        }
    }
    return -1; // No alarms are ringing
}

// **Regularly called to check and update alarm status**
void Horaires::update() {
    DateTime now = getDate();
    unsigned long currentTimeMinutes = now.hours * 60 + now.minutes;

    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        if (!alarms[i].enabled) continue;

        unsigned long alarmTimeMinutes = alarms[i].hours * 60 + alarms[i].minutes;

        // Check if alarm should ring (current time is within ALARM_WINDOW minutes after alarm time)
        if (!alarms[i].ringing && (currentTimeMinutes >= alarmTimeMinutes) && (currentTimeMinutes < alarmTimeMinutes + ALARM_WINDOW) && (currentTimeMinutes >= lastClearedTime[i] + ALARM_BLANKING_WINDOW)) {
                alarms[i].ringing = true;
        }
    }
}

// **Load all alarms from EEPROM once at startup**
void Horaires::loadAlarmsFromEEPROM() {
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        uint8_t addr = EEPROM_ALARM_ADDR + (i * 3);  // Each alarm takes 3 bytes
        alarms[i].hours = EEPROM.read(addr);
        alarms[i].minutes = EEPROM.read(addr + 1);
        alarms[i].enabled = EEPROM.read(addr + 2);
        alarms[i].ringing = false; // Reset ringing state on boot
    }
}

// **Save an alarm to EEPROM**
void Horaires::saveAlarmToEEPROM(uint8_t alarmNumber) {
    uint8_t addr = EEPROM_ALARM_ADDR + (alarmNumber * 3);
    EEPROM.update(addr, alarms[alarmNumber].hours);
    EEPROM.update(addr + 1, alarms[alarmNumber].minutes);
    EEPROM.update(addr + 2, alarms[alarmNumber].enabled);
}

// **Helper functions to convert BCD and Decimal**
uint8_t Horaires::bcdToDec(uint8_t val) {
    return (val / 16 * 10) + (val % 16);
}

uint8_t Horaires::decToBcd(uint8_t val) {
    return (val / 10 * 16) + (val % 10);
}
