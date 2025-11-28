#ifndef ANGLE_CALC_H
#define ANGLE_CALC_H

#include <Wire.h>
#include <RTClib.h>

//#define DEBUG_ANGLECALC //prints verbose info on solar angle calculations
#define ANGLE_CALC_POLLINTERVAL 5000   //time in ms for every RTC polling/sunPos calc event

// Degree to radian and vice versa
#define degToRad(deg) ((deg) * M_PI / 180.0)
#define radToDeg(rad) ((rad) * 180.0 / M_PI)

struct Location{
    double latitude;        // Positive towards north
    double longitude;       // Positive towards east
    int timezone;           // Positive towards east
};

struct SunPosition{
    double azimuth;
    double elevation;
};


extern RTC_DS3231 rtc;
extern DateTime currentDate;
extern struct Location geoLoc;
extern struct SunPosition sunPos;
extern unsigned long rtc_nextPollTime;

//Function to init the DS3231 RTC module
void rtc_init();

// Function to get the current date and time
void rtc_updateDateTime();

// Function to set a specific date and time
void setDateTime(int day, int month, int year, int hour, int minute, int second);

// Function to calculate the optimal angle for the panel based on date, time, and location (latitude/longitude)
struct SunPosition getSunPosition(DateTime date,struct Location loc);

#endif
