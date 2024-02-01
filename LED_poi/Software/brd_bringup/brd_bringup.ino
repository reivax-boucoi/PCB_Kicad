
#include <Adafruit_NeoPixel.h>


#define PIXEL_PIN 13 //PC7
#define PIXEL_COUNT 15

uint32_t pixel_data[PIXEL_COUNT];
Adafruit_NeoPixel led_strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint8_t mode = 0;

void setup() {
    led_strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
    led_strip.show();  // Initialize all pixels to 'off'

}

void loop() {
    led_strip.fill(0x000000, mode++, 0);
    if (mode > 13)mode = 0;
    led_strip.show();
    delay(500);
}
