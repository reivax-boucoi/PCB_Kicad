#include "Animations.h"

#include <Adafruit_NeoPixel.h>



uint32_t pixel_data[PIXEL_COUNT];
Adafruit_NeoPixel led_strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void Anim_blink(uint8_t step) {
#ifdef ANIM_VERBOSE
    Serial.print("\tBlink\tstep:");
    Serial.println(step);
#endif
    if (step < 127) {
        led_strip.fill(0xFF0000);
    } else {
        led_strip.fill(0x000000);
    }

    led_strip.show();
}

void Anim_rainbow(uint8_t step) {
#ifdef ANIM_VERBOSE
    Serial.print("\tRainbow\tstep:");
    Serial.println(step);
#endif
    led_strip.fill(led_strip.ColorHSV(step << 8));
    led_strip.show();
}

void Anim_blank(uint8_t step) {

#ifdef ANIM_VERBOSE
    Serial.print("\tBLANK\tstep:");
    Serial.println(step);
#endif
}

void Anim_quarters(uint8_t step){

#ifdef ANIM_VERBOSE
    Serial.print("\tQuarters\tstep:");
    Serial.println(step);
#endif
    if (step < 64) {
        led_strip.fill(0xFF0000);
    } else if(step <128){
        led_strip.fill(0x0000FF);
    } else if(step <192){
        led_strip.fill(0x00FF00);
    } else {
        led_strip.fill(0xFFFF00);
    }

    led_strip.show();
}


Animations::Animations(void) {
    animId = 0;    
    animList[animId++] = Anim_blank;
    animList[animId++] = Anim_blink;
    animList[animId++] = Anim_rainbow;
    animList[animId++] = Anim_quarters;
    
    for(;animId<ANIM_COUNT;animId++){
        animList[animId] = animList[0];
    }

    animStep = 0;
    animId = 0;
    animSpeed = 1<<8;
    displayingAnimId = true;
    accSyncEnabled = false;
}

void Animations::setAnim(uint8_t new_animId) {
    Serial.print("Anim set to ");
    Serial.println(new_animId);
    LEDS_showMode(new_animId);

    animId = new_animId;
    animStep = 0;
    displayingAnimId = true;
}

void Animations::update() {

    if (displayingAnimId) {
        if (100 < animStep) {
            displayingAnimId = false;
            animStep=0;
            //Serial.print("Exiting displayingAnimId");
        } else {
            animStep++;
            return;
        }
    }
    animStep += animSpeed;

#ifdef ANIM_VERBOSE
    Serial.print("Id:");
    Serial.print(animId);
    Serial.print("\tsp:");
    Serial.print(animSpeed);
#endif

    animList[animId](animStep>>8);
}

void Animations::nextAnim(bool dir) {
    uint8_t id = animId;
    if (dir) {
        if (++id >= ANIM_COUNT) id = 0;
    } else {
        if (--id == 255) id = ANIM_COUNT-1;
    }
    setAnim(id);
}

void LEDs_init() {
    led_strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
    led_strip.show();  // Initialize all pixels to 'off'
}

void LEDs_setColor(uint32_t c) {
    led_strip.clear();
    led_strip.setPixelColor(0, c);
    led_strip.show();
}

void LEDS_showMode(uint8_t mode) {
    led_strip.fill(led_strip.ColorHSV(map(mode, 0, ANIM_COUNT, 0, 0xFFFF), 0, mode));
    led_strip.fill(0x000000, mode, 0);
    led_strip.show();
}
