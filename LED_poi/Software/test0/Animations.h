#ifndef animations_h
#define animations_h

#include <Arduino.h>

#define PIXEL_PIN 13 //PC7
#define PIXEL_COUNT 7

void LEDs_init();
void LEDs_setColor(uint32_t c);
void LEDS_showMode(uint8_t mode);

typedef void(*Anim)(uint8_t step);

void Anim_blink(uint8_t step);
void Anim_rainbow(uint8_t step);
void Anim_blank(uint8_t step);

class Animations {

    private:
        uint8_t animId;
        uint8_t animStep;
        uint8_t animSpeed;
        bool isEnabled;
        Anim animList[7];
    public:
        Animations(void);
        void setAnim(uint8_t new_animId);
        void update();
};

#endif
