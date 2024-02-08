#include "Animations.h"

#include <Adafruit_NeoPixel.h>



uint32_t pixel_data[PIXEL_COUNT];
Adafruit_NeoPixel led_strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void Anim_blink(uint8_t step) {
    Serial.print("Blink ");
    Serial.println(step);
}
void Anim_rainbow(uint8_t step) {
    Serial.print("Rainbow ");
    Serial.println(step);
}
void Anim_blank(uint8_t step) {
    Serial.print("Blank ");
    Serial.println(step);
}
Animations::Animations(void) {
    animList[0] = Anim_blink;
    animList[1] = Anim_rainbow;
    animList[2] = Anim_blank;
    animList[3] = Anim_blank;
    animList[4] = Anim_blank;
    animList[5] = Anim_blank;
    animList[6] = Anim_blank;

    animStep = 0;
    animId = 0;
    animSpeed = 1;
}

void Animations::setAnim(uint8_t new_animId) {
    Serial.print("Anim set to ");
    Serial.println(new_animId);
    animId = new_animId;
    animStep = 0;
}

void Animations::update() {
    animStep += animSpeed;
    animList[animId](animStep);
}

void LEDs_init() {

    led_strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
    led_strip.show();  // Initialize all pixels to 'off'
}

void LEDs_setColor(uint32_t c) {

    led_strip.setPixelColor(0, c);
    led_strip.show();
}

void LEDS_showMode(uint8_t mode) {
    led_strip.fill(led_strip.ColorHSV(mode << 13), 0, mode);
    led_strip.fill(0x000000, mode, 0);

    led_strip.show();

}
