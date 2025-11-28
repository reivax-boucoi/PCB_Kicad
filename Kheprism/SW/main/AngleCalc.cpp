#include "AngleCalc.h"


RTC_DS3231 rtc;
DateTime currentDate;
struct Location geoLoc = {43.6, 1.44, 1};
struct SunPosition sunPos = {0, 0};
unsigned long rtc_nextPollTime;


//Function to init the DS3231 RTC module
void rtc_init() {
    if (!rtc.begin()) {
        Serial.println("RTC not found! Check wiring and power.");
        return;
    }
    /*
        // Check if RTC lost power and needs resetting
        if (rtc.lostPower()) {
            Serial.println("RTC lost power, setting default time to compile time.");
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
        Serial.println("RTC initialized successfully.");
    */
}

// Function to get the current date and time
void rtc_updateDateTime() {
    rtc_nextPollTime = millis() + ANGLE_CALC_POLLINTERVAL;
    currentDate = rtc.now();
    //currentDate = currentDate + TimeSpan(0,15,0,0);
    sunPos = getSunPosition(currentDate,geoLoc);
}

// Function to set a specific date and time
void setDateTime(int day, int month, int year, int hour, int minute, int second) {
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
}

// Function to calculate the optimal angle for the panel based on date, time, and location (latitude/longitude)
struct SunPosition getSunPosition(DateTime date, struct Location loc) {
    // Step 1: Julian Day
    // Adjust month and year for Jan and Feb
    int year = date.year();
    int month = date.month();
    if (month <= 2) {
        year -= 1;
        month += 12;
    }

    int A = year / 100;
    int B = 2 - A + (A / 4);

    // Julian Day at 0h = -7 UT
    double JD = (int)(365.25 * (year + 4716)) + (int)(30.6001 * (month + 1)) + date.day() + B - 1524.5;

    // Convert local time to UT: add timezone offset (hours)
    double UT = date.hour() + (date.minute() / 60.0) - loc.timezone;

    // Add fractional day to JD
    JD += UT / 24.0;

    // Step 2: Julian Century
    double T = (JD - 2451545.0) / 36525.0;

    // Step 3: Geometric Mean Longitude of Sun (L0)
    double L0 = fmod(280.46646 + T * (36000.76983 + T * 0.0003032), 360);

    // Step 4: Geometric Mean Anomaly (M)
    double M = 357.52911 + T * (35999.05029 - 0.0001537 * T);

    // Step 5: Eccentricity of Earth's orbit
    double e = 0.016708634 - T * (0.000042037 + 0.0000001267 * T);

    // Step 6: Sun Equation of Center
    double C = sin(degToRad(M)) * (1.914602 - T * (0.004817 + 0.000014 * T)) +
               sin(degToRad(2 * M)) * (0.019993 - 0.000101 * T) +
               sin(degToRad(3 * M)) * 0.000289;

    // Step 7: Sun True Longitude
    double O = L0 + C;

    // Step 8: Apparent Longitude
    double omega = 125.04 - 1934.136 * T;
    double lambda_sun = O - 0.00569 - 0.00478 * sin(degToRad(omega));

    // Step 9: Mean obliquity and corrected obliquity
    double epsilon0 = 23 + (26 + ((21.448 - T * (46.815 + T * (0.00059 - T * 0.001813)))) / 60) / 60;
    double epsilon = epsilon0 + 0.00256 * cos(degToRad(omega));

    // Step 10: Sun Declination
    double sin_delta = sin(degToRad(epsilon)) * sin(degToRad(lambda_sun));
    double delta = radToDeg(asin(sin_delta));

    // Step 11: Equation of Time
    double y_corr = pow(tan(degToRad(epsilon / 2)), 2);
    double EoT = 4 * radToDeg(
                     y_corr * sin(2 * degToRad(L0)) -
                     2 * e * sin(degToRad(M)) +
                     4 * e * y_corr * sin(degToRad(M)) * cos(2 * degToRad(L0)) -
                     0.5 * pow(y_corr, 2) * sin(4 * degToRad(L0)) -
                     1.25 * pow(e, 2) * sin(2 * degToRad(M))
                 );

    // Step 12: True Solar Time
    double minutes = date.hour() * 60 + date.minute();
    double TST = fmod(minutes + EoT + 4 * loc.longitude - 60 * loc.timezone, 1440);

    // Step 13: Hour Angle
    double HA;
    if ((TST / 4) < 0) {
        HA = TST / 4 + 180;
    } else {
        HA = TST / 4 - 180;
    }

    // Step 14: Solar Zenith Angle
    double latRad = degToRad(loc.latitude);
    double deltaRad = degToRad(delta);
    double HARad = degToRad(HA);

    double cos_zenith = sin(latRad) * sin(deltaRad) + cos(latRad) * cos(deltaRad) * cos(HARad);
    double zenith = radToDeg(acos(cos_zenith));
    double elevation = 90 - zenith;

    // Step 15: Solar Azimuth
    double azimuth = radToDeg(acos((sin(latRad) * cos(degToRad(zenith)) - sin(deltaRad)) / (cos(latRad) * sin(degToRad(zenith)))));
    if (HA > 0) {
        azimuth = fmod(azimuth + 180, 360);
    } else {
        azimuth = fmod(540 - azimuth, 360);
    }

    // Print intermediate values
#ifdef DEBUG_ANGLECALC
        printf("GeoLoc: %f, %f, TZ=%d\n", loc.latitude, loc.longitude, loc.timezone );
        printf("Date: %d/%d/%d %dh%d\n", date.year(), date.month(), date.day(), date.hour(), date.minute() );
        printf("Julian Day: %f\n", JD);
        printf("Julian Century: %f\n", T);
        printf("Mean Longitude L0: %f\n", L0);
        printf("Mean Anomaly M: %f\n", M);
        printf("Eccentricity e: %f\n", e);
        printf("Sun Equation of Center C: %f\n", C);
        printf("True Longitude O: %f\n", O);
        printf("Apparent Longitude λ: %f\n", lambda_sun);
        printf("Obliquity ε: %f\n", epsilon);
        printf("Declination δ: %f\n", delta);
        printf("Equation of Time (minutes): %f\n", EoT);
        printf("True Solar Time (minutes): %f\n", TST);
        printf("Hour Angle (HA): %f\n", HA);
        printf("Solar Zenith: %f°\n", zenith);
        printf("Solar Elevation: %f°\n", elevation);
        printf("Solar Azimuth: %f°\n", azimuth);
#endif
    struct SunPosition sunPos = {azimuth, elevation};
    return sunPos;
}
