/*
 * GccApplication1.c
 *
 * Created: 4/14/2024 8:01:04 PM
 * Author : lukas-pc
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include "util/delay.h"
#include <avr/interrupt.h>
#include <string.h>

char QUARTER = 4;
char EIGHT = 2;
char SIXTEENTH = 1;

//hi paul the code rn only reflects the first c being played PORTD PIN1
// After you solder all the buttons and conncet them to the 8 realys
//youll have to modify this code so that the Shifted bit is given by what note it is C-C
// so like portD |= (1<<D) where D would be 1 cause its bit 1
//please im begging you dont break the realys, they are rated for 100,000 cycles

void custom_delay_ms(unsigned int ms) {
	unsigned int i;
	for (i = 0; i < ms; i++) {
		_delay_ms(1); // Use built-in delay function for 1 millisecond
	}
}



void shiftOutPORTD(char DATAP, char CLKP, char data){
		for (char i = 0; i < 8; i++) {
			// Output the current bit on the data pin
			if (data & (1 << (7 - i))) {
				PORTD |= (1 << DATAP);  // Set data pin high
				} else {
				PORTD &= ~(1 << DATAP); // Set data pin low
			}
			
			// Pulse the clock pin to shift the next bit
			PORTD |= (1 << CLKP);    // Set clock pin high
			PORTD &= ~(1 << CLKP);   // Set clock pin low
		}
	}
void shiftRegisterDisplay(char bar){
		//data pin SER (1<<0);
		//update clock latch SRCLK (1<<1);
		//Output pin RCLK (1<<2);
		
		PORTD &= ~(1 << 1); // CLKP low
		PORTD &= ~(1 << 2); // RCLK low
		
		PORTD &= ~(1<<2);
		shiftOutPORTD(0,1,bar);
		PORTD |= (1<<2);
		
	}
	
void playNote(float BPM,char noteDuration, char note){
	char shift;
	char octave;
	
	switch(note){
		case 0: shift = 0; octave = 0; break;
		case 1: shift = 1; octave = 0; break;
		case 2: shift = 2; octave = 0; break;
		case 3: shift = 3; octave = 0; break;
		case 4: shift = 4; octave = 0; break;
		case 5: shift = 5; octave = 0; break;
		case 6: shift = 6; octave = 0; break;
		case 7: shift = 7; octave = 0; break;
		case 8: shift = 0; octave = 1; break;
		case 9: shift = 1; octave = 1; break;
		case 10: shift = 2; octave = 1; break;
		case 11: shift = 3; octave = 1; break;
		case 12: shift = 4; octave = 1; break;
		case 13: shift = 5; octave = 1; break;
		case 14: shift = 6; octave = 1; break;
		case 15: shift = 7; octave = 1; break;
		case 16: shift = 0; octave = 2; break;
		case 17: shift = 1; octave = 2; break;
		case 18: shift = 2; octave = 2; break;
		case 19: shift = 3; octave = 2; break;
		case 20: shift = 4; octave = 2; break;
		case 21: shift = 5; octave = 2; break;
        case 22: shift = 6; octave = 2; break;
		case 23: shift = 7; octave = 2; break;
		case 24: shift = 0; octave = 3; break;
		case 25: shift = 1; octave = 3; break;
		case 26: shift = 2; octave = 3; break;
		case 27: shift = 3; octave = 3; break;
		case 28: shift = 4; octave = 3; break;
		case 29: shift = 5; octave = 3; break;
		case 30: shift = 6; octave = 3; break;
		case 31: shift = 7; octave = 3; break;
		case 32: shift = 10; octave = 10; break;
		default: shift = 0; octave = 0;
	
	}
	
	float n = ((60000.0 / BPM) / 4) * noteDuration; // Calculate total duration in milliseconds
	PORTD |= (1<<(octave+3));
	shiftRegisterDisplay(1<<shift);
	custom_delay_ms(n/2); // hey dont remove the delay - spencer
	PORTD &=~(1<<(octave+3));
	shiftRegisterDisplay(0);
	custom_delay_ms(n/2);
	}
	
void OdeToJoy(float BPM) {
	playNote(BPM,QUARTER,7);
	playNote(BPM,QUARTER,7);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,10);
	
	playNote(BPM,QUARTER,10);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,7);
	playNote(BPM,QUARTER,5);
	
	playNote(BPM,QUARTER,3);
	playNote(BPM,QUARTER,3);
	playNote(BPM,QUARTER,5);
	playNote(BPM,QUARTER,7);
	
	playNote(BPM,QUARTER+EIGHT,7);
	playNote(BPM,EIGHT,5);
	playNote(BPM,QUARTER+QUARTER,5);
	
	playNote(BPM,QUARTER,7);
	playNote(BPM,QUARTER,7);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,10);
	
	playNote(BPM,QUARTER,10);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,7);
	playNote(BPM,QUARTER,5);
	
	playNote(BPM,QUARTER,3);
	playNote(BPM,QUARTER,3);
	playNote(BPM,QUARTER,5);
	playNote(BPM,QUARTER,7);
	
	playNote(BPM,QUARTER+EIGHT,5);
	playNote(BPM,EIGHT,3);
	playNote(BPM,QUARTER+QUARTER,3);
	
	
}

void FurElise(float BPM) {
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,23);
	
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,23);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,19);
	playNote(BPM,EIGHT,22);
	playNote(BPM,EIGHT,20);

	playNote(BPM,EIGHT,17);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,17);
	
	playNote(BPM,EIGHT,19);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,16);
	playNote(BPM,EIGHT,19);
	
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,23);
	
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,23);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,19);
	playNote(BPM,EIGHT,22);
	playNote(BPM,EIGHT,20);
	
	playNote(BPM,EIGHT,17);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,17);
	
	playNote(BPM,EIGHT,19);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,20);
	playNote(BPM,EIGHT,19);
	
	playNote(BPM,EIGHT,17);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,19);
	playNote(BPM,EIGHT,20);
	playNote(BPM,EIGHT,22);
	
	playNote(BPM,EIGHT,24);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,15);
	playNote(BPM,EIGHT,25);
	playNote(BPM,EIGHT,24);
	
	playNote(BPM,EIGHT,22);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,22);
	
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,22);
	playNote(BPM,EIGHT,20);
	
	
	playNote(BPM,EIGHT,19);
	playNote(BPM,EIGHT,32);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,32);
	
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,23);
	playNote(BPM,EIGHT,24);
	playNote(BPM,EIGHT,23);
	playNote(BPM,EIGHT,24);
	
	playNote(BPM,SIXTEENTH,23);
	playNote(BPM,SIXTEENTH,24);
	playNote(BPM,SIXTEENTH,23);
	playNote(BPM,SIXTEENTH,24);
	playNote(BPM,SIXTEENTH,23);
	playNote(BPM,SIXTEENTH,24);
	playNote(BPM,SIXTEENTH,23);
	playNote(BPM,SIXTEENTH,24);
	playNote(BPM,SIXTEENTH,23);
	playNote(BPM,SIXTEENTH,24);
	
	playNote(BPM,QUARTER,19);
	playNote(BPM,QUARTER,22);
	playNote(BPM,QUARTER+QUARTER,20);
	playNote(BPM,QUARTER+QUARTER,17);
	playNote(BPM,QUARTER+QUARTER,5);
}
void SURPRISE(float BPM){
	playNote(BPM,QUARTER,8);
	
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,8);
	
	playNote(BPM,EIGHT,6);
	playNote(BPM,QUARTER,6);
	playNote(BPM,QUARTER,5);
	playNote(BPM,EIGHT,5);
	playNote(BPM,EIGHT,5);
	playNote(BPM,EIGHT,5);
	
	playNote(BPM,QUARTER,5);
	playNote(BPM,EIGHT,5);
	playNote(BPM,EIGHT,5);
	playNote(BPM,QUARTER,5);
	playNote(BPM,EIGHT,1);
	playNote(BPM,QUARTER+EIGHT,3);
	
	playNote(BPM,QUARTER,32);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,8);
	
	playNote(BPM,EIGHT,6);
	playNote(BPM,QUARTER,6);
	playNote(BPM,EIGHT,5);
	playNote(BPM,QUARTER,32);
	
	playNote(BPM,EIGHT,5);
	playNote(BPM,EIGHT,5);
	playNote(BPM,QUARTER,5);
	playNote(BPM,EIGHT,5);
	playNote(BPM,EIGHT,5);
	playNote(BPM,QUARTER,5);
	playNote(BPM,EIGHT,1);
	
	
	playNote(BPM,QUARTER,3);
	playNote(BPM,QUARTER+QUARTER,32);
	
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	
	playNote(BPM,QUARTER,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,QUARTER,12);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,QUARTER,12);
	playNote(BPM,QUARTER+QUARTER,13);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,QUARTER+EIGHT,15);
	playNote(BPM,QUARTER,17);
	
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,QUARTER,13);
	
	playNote(BPM,QUARTER+EIGHT,15);
	playNote(BPM,QUARTER,17);
	
	playNote(BPM,QUARTER,32);
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,EIGHT,12);
	playNote(BPM,QUARTER,13);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	
	playNote(BPM,EIGHT,22);
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER,17);
	
	playNote(BPM,EIGHT,17);
	playNote(BPM,EIGHT,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,EIGHT,15);
	playNote(BPM,QUARTER+QUARTER,17);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,EIGHT,15);
	playNote(BPM,QUARTER,15);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER+QUARTER,10);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,EIGHT,15);
	playNote(BPM,QUARTER+QUARTER,17);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER+QUARTER,20);
	playNote(BPM,QUARTER+QUARTER,17);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,20);
	playNote(BPM,EIGHT,20);
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER+QUARTER,17);
	
	playNote(BPM,EIGHT,17);
	playNote(BPM,EIGHT,17);
	playNote(BPM,EIGHT,17);
	playNote(BPM,EIGHT,17);
	playNote(BPM,QUARTER,17);
	playNote(BPM,QUARTER,13);
	playNote(BPM,QUARTER+QUARTER,15);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER+QUARTER,8);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER+QUARTER,8);
	
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,13);
	playNote(BPM,QUARTER,20);
	
	playNote(BPM,QUARTER,22);
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER,17);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,17);
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER+QUARTER,17);
	
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,8);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,15);
	playNote(BPM,QUARTER,13);
	
	playNote(BPM,QUARTER,22);
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER,17);
	playNote(BPM,EIGHT,13);
	playNote(BPM,EIGHT,17);
	playNote(BPM,EIGHT,20);
	playNote(BPM,QUARTER+QUARTER,17);
	
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,8);
	playNote(BPM,EIGHT,8);
	playNote(BPM,QUARTER,8);
	playNote(BPM,QUARTER,15);
	playNote(BPM,QUARTER,13);
	
}


int main(void)
{
     
    
		DDRD = 0xFF;
		DDRC &=~ (1<<0);
		DDRC &=~ (1<<1);
		DDRC &=~ (1<<2); 
		
	while(1){	
		if((PINC &(1<<0))!=0){
			PORTC |= (1<<0);
			FurElise(100);
		}
		if((PINC &(1<<1))!=0){
			PORTC |= (1<<1);
			OdeToJoy(150);
		}
		if((PINC &(1<<2))!=0){
			PORTC |= (1<<2);
			SURPRISE(150);
		}
		if((PINC &(1<<5))!=0){
			PORTC &=~ (1<<0);
			PORTC &=~ (1<<1);
			PORTC &=~ (1<<2);
		}
	}
	return 0;
	
		

}
