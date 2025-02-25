#ifndef accelero_h
#define accelero_h
#include <Arduino.h>

#define ACC_DECAY 50

class ACC {
    private:
        int16_t maxY;
        int16_t minY;
        int16_t value_f;
        uint8_t periodPos;
        uint8_t periodNeg;
        uint8_t cntPos;
        uint8_t cntNeg;

    public:
        bool newHalfCycleFlag;
        bool cycleState;
        ACC(uint8_t rate, uint8_t gees);
        int16_t getY();
        void printRaw();
        void printPeriod();
};

#endif
