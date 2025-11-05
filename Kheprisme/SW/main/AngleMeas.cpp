#include "AngleMeas.h"


Adafruit_MMA8451 mma = Adafruit_MMA8451();
struct AcceleroData acc_data;
unsigned long acc_nextPollTime;


// Function to initialize the accelerometer
void accelero_init() {
    if (!mma.begin()) {
        Serial.println("Couldnt start accelerometer");
        return;
    }
    mma.setRange(MMA8451_RANGE_2_G);
    mma.setDataRate(MMA8451_DATARATE_50_HZ);
    Serial.println("Accelero sucessfully initialized !");
    acc_data.measured_angle = 0;
    acc_data.accumulated_angle = 0;
    acc_data.avg_counter = 0;
    acc_data.valueUpdated = false;
}

// Function to accumulate accelero results
void accelero_update(){
    
    acc_nextPollTime = millis() + ANGLE_MEAS_POLLINTERVAL;
    mma.read();
    
    long magnitude = mma.x*mma.x+mma.y*mma.y+mma.z*mma.z;
    //Serial.println(magnitude);
    
    if (abs(magnitude - (ACCELEROMETER_COUNTS*ACCELEROMETER_COUNTS)) < ACCELEROMETER_MAG_TH) {// if Magnitude OK
      double angle;
      if (mma.x == 0) {
        angle = ((mma.y + ACCELEROMETER_COUNTS) / ACCELEROMETER_COUNTS) * 90.000;
      } else if (mma.y == 0) {
        angle = ((mma.x + ACCELEROMETER_COUNTS) / ACCELEROMETER_COUNTS) * 90.000 + 90;
      } else {
        double tempv = atan((double)mma.x / (double)mma.y) * RAD_TO_DEG;
         angle= mma.y < 0 ? tempv : 180 + tempv;
      }
      /*Serial.print(angle);
      Serial.print(',');
      Serial.println(acc_data.measured_angle);*/
      acc_data.accumulated_angle+=angle;
      acc_data.avg_counter++;
    } else {// if Magnitude rejected
      //Serial.print("Rejected");
    }
    if(acc_data.avg_counter >= MEAS_AVG_CNT){
      acc_data.measured_angle = acc_data.accumulated_angle/acc_data.avg_counter;
      acc_data.measured_angle += ANGLE_OFFSET;
      acc_data.valueUpdated = true;
      acc_data.accumulated_angle = 0;
      acc_data.avg_counter = 0;
      /*Serial.print("New angle : ");
      Serial.print(acc_data.measured_angle);
      Serial.println("°");
      */
    }
}

// Function to get the current tilt/angle of the panel (in degrees)
double accelero_getAngle(){
    acc_data.valueUpdated = false;
    return acc_data.measured_angle;
}
