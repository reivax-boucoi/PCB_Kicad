//To flash & burn fuses:
// avrdude -c usbtiny -p t45 -B 250 -U flash:w:"/home/user/Documents/PCB/transistor_clock/MCU_clk_extension/main.hex":a -U lfuse:w:0xE6:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m


#include <avr/io.h>
#include <avr/sleep.h>
#define F_CPU (32768/8)
int main(void){
    
    CLKPR=0x80;//Unlock clock prescaler
    CLKPR=0x01;//set clock prescaler to 16 (within 4 clock cycles)
    
    DDRB=0x01;//Set PINB0 (OC0A pin) as output, push pull.
    PORTB=0x00;
    
    //Fast PWM mode: Fpwm=Fclk/(N*256) where N=1,8,64,256,1024
    //Fclk=2048Hz, N=8 -> Fpwm=1Hz
	TCCR0A =(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);//Fast PWM mode: Clear OC0A on compare match, set OC0A at bottom
    OCR0A=2;//8.5ms=2.17
    TCCR0B = (1<<CS01)|(1<<CS00); //Set prescaler to N=80
    
    ADCSRA=0x00;//Disable ADC, save power
    PRR=0x0B;//Shut down Timer1, ADC, USI. Keep Timer0 running
    
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_mode();
    
	while(1){

	}

	return 0;
}



