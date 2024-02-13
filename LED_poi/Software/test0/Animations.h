#ifndef animations_h
#define animations_h

#include <Arduino.h>

#define PIXEL_PIN 13 //PC7
#define PIXEL_COUNT 7

#define ANIM_COUNT 7
//#define ANIM_VERBOSE

void LEDs_init();
void LEDs_setColor(uint32_t c);
void LEDS_showMode(uint8_t mode);

typedef void(*Anim)(uint8_t step);

void Anim_blink(uint8_t step);
void Anim_rainbow(uint8_t step);
void Anim_quarters(uint8_t step);
void Anim_blank(uint8_t step);

class Animations {

    private:
        uint16_t animStep;
        bool displayingAnimId;
        bool accSyncEnabled;
        Anim animList[ANIM_COUNT];
    public:
        Animations(void);
        uint8_t animId;
        uint16_t animSpeed;
        void setAnim(uint8_t new_animId);
        void nextAnim(bool dir);
        void update();
};

#endif
