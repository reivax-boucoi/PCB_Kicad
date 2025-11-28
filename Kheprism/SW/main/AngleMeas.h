#ifndef ANGLE_MEASUREMENT_H
#define ANGLE_MEASUREMENT_H


#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

#define RAD_TO_DEG 57.295779513082320876798154814105
#define ACCELEROMETER_COUNTS 4096.0     //accelerometer sensitivity in counts per G * scale
#define ACCELEROMETER_MAG_TH 600000     //thresold for acceleration plausibility check
#define MEAS_AVG_CNT 50                 //number of accelerometer measurements to average
#define ANGLE_OFFSET 90
#define ANGLE_MEAS_POLLINTERVAL 20   //time in ms for every accelerometer polling event. Must be set in accordance to MMA8451_DATARATE_50_HZ

struct AcceleroData{
    double measured_angle;      //last good measured angle value
    double accumulated_angle;   //holds accumulated angle for averaging
    int avg_counter;            //counts the number of accumulated samples
    bool valueUpdated;          //true if new angle was acquired since last reading
};

extern Adafruit_MMA8451 mma;
extern struct AcceleroData acc_data;
extern unsigned long acc_nextPollTime;


// Function to initialize the accelerometer
void accelero_init();

// Function to accumulate accelero results
void accelero_update();

// Function to get the current tilt/angle of the panel (in degrees)
double accelero_getAngle();

#endif
