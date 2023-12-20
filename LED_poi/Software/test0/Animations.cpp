#include "Animations.h"

#include <Adafruit_NeoPixel.h>


uint32_t pixel_data[PIXEL_COUNT];
Adafruit_NeoPixel led_strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void LEDs_init() {

    led_strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
    led_strip.show();  // Initialize all pixels to 'off'
}

void LEDs_setColor(uint32_t c) {
    led_strip.clear();
    uint32_t color = led_strip.Color(  0,   0, 127);
    uint32_t index = led_strip.numPixels() - 3;
    led_strip.setPixelColor(index, c);
    led_strip.show();
}

void LEDS_showMode(uint8_t mode) {
    led_strip.fill(led_strip.ColorHSV(mode <<13), 0, mode);
    led_strip.fill(0x000000, mode, 0);

    led_strip.show();

}
