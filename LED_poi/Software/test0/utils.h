#ifndef utils_h
#define utils_h

#include <Arduino.h>
#include "Animations.h"

extern Animations* myAnimations;
#define KEY 5           //PC6 (output, active high)
#define BTN 10          //PB6 (input, active high)
#define ACC_INT1 8      //PB4 (input, active high, 3.3V)
#define ACC_INT2 9      //PB5 (input, active high, 3.3V)

void IO_initialize();

void supply_ON();
void supply_OFF();

#endif
