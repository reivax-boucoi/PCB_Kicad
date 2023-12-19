#ifndef accelero_h
#define accelero_h
#include <Arduino.h>



class ACC {
    private:
        int16_t meanY;
        int16_t maxY;
        int16_t minY;
        int16_t value;

    public:
        ACC(uint8_t rate, uint8_t gees);
        int16_t getY();
        void print();
};

#endif
