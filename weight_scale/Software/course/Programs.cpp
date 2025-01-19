#include "Programs.h"

//0: "r3" fractionné 30s/30s 10reps (10 min)
//1: "r4" fractionné 45s/45s 10reps (15 min)
//2: "F3" fractionné 30s/30s 15reps (15 min)
//3: "F4" fractionné 45s/45s 15reps (22.5min)
//4: "L0" Luc Léger 12 paliers


const LCD::Symbol Program::Sym1[]={LCD::r,LCD::r,LCD::F,LCD::F,LCD::L};
const uint8_t Program::Sym2[]={3,4,3,4,0};

const uint8_t Program::LL_Tlap[]={90,85,80,76,72,69,65,58,55,53,51,50,48};
const uint16_t Program::LL_Tnext[]={1170,1763,2323,2929,3577,4126,4716,5292,5901,6487,7104,7700,8324};

Program::Program(LCD *l){
    myLCD=l;
    selectedProgram=0;
    started=0;
	LED0_OFF;
	LED1_OFF;
}

Program::~Program(){
    
}


void Program::start(uint32_t time){
    myBeep.longB();
    started=1;
    pTime=time;
    LED1_ON;
    LED0_OFF;
    switch(selectedProgram){
        case 0:
            lapNb=20;
            lapTime=300;
        break;
        case 1:
            lapNb=20;
            lapTime=450;
        break;
        case 2:
            lapNb=30;
            lapTime=300;
        break;
        case 3:
            lapNb=30;
            lapTime=450;
        break;
        case 4:
            lapNb=0;
            lapTime=LL_Tlap[lapNb];
            startTime=time;
    }
}
void Program::stop(void){
    myBeep.longB();    
    LED0_ON;
    LED1_OFF;
    started=0;
}
void Program::update(uint32_t time){
    if (time>(pTime+lapTime)){
        switch(selectedProgram){
            case 4:
                pTime+=lapTime;
                if((time-startTime)>LL_Tnext[lapNb]){
                    if(++lapNb>12){
                        stop();
                        return;
                    }
                    lapTime=LL_Tlap[lapNb];
                    myBeep.dualB(); // dual when change of palier
                }else{
                    myBeep.singleB();//single when in same palier
                }
            break;
            default:
                lapNb--;
                pTime+=lapTime;
                if(lapNb==0){
                    stop();
                    return;
                }
                if(lapNb%2){
                    myBeep.singleB();
                }else{
                    myBeep.dualB();
                }
            break;
        }
    }
}

void Program::show(void){
    if(started){
        myLCD->setNb(lapNb,2);        
    }else{
        myLCD->setDigit(4,Sym1[selectedProgram]);
        myLCD->setDigit(5,Sym2[selectedProgram]);
    }
}

Beep::Beep(void){
    DDRB|=(1<<PINB4);//buzzer output is PINB4
    PORTB&=~(1<<PINB4);
    //TCCR0A|=(1<<WGM01)|(1<<COM0A0)|(1<<CS01)|(1<<CS00);//toggle OC0A on compare match, 64 prescaler, start timer
    OCR0A=195;// 8MHz/8 /2 /(191+1) = 2.6kHz
}
Beep::~Beep(void){
    
}

void Beep::singleB(void){
    cnt=3;
    on();
}
void Beep::dualB(void){
    cnt=5;
    on();
}
void Beep::longB(void){
    cnt=7;
    on();
}
void Beep::update(void){
    if(cnt==0)return;
    cnt--;
    if(cnt>6)return;
    if(cnt==6)cnt=1;
    if(cnt%2){
        on();
    }else{
        off();
    }
}
void Beep::on(void){
    
#if (F_CPU==1000000)
    TCCR0A|=(1<<WGM01)|(1<<COM0A0)|(1<<CS00);//toggle OC0A on compare match, 1 prescaler, start timer
#else
    TCCR0A|=(1<<WGM01)|(1<<COM0A0)|(1<<CS01);//toggle OC0A on compare match, 8 prescaler, start timer
#endif
}
void Beep::off(void){
    TCCR0A=0;
}
