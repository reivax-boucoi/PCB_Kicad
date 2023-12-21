#ifndef animations_h
#define animations_h

#include <Arduino.h>

#define PIXEL_PIN 13 //PC7
#define PIXEL_COUNT 7

void LEDs_init();
void LEDs_setColor(uint32_t c);
void LEDS_showMode(uint8_t mode);

#endif
