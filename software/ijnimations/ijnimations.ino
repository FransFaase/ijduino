/*                            IJduino 1.0
Requires:
 * 8X8 LED grid MAX7219
 * Mini Breadboard
 * Atmega328
 * Button
 * 2 Wires
 * 4.5 Volt
 (c) IJhack 2014 GNU GPL 
http://ijhack.org/
 */
#include "LedControl.h"

/* using VCC, GND, DIN 21, CS 21, CLK 5 for the MAX7219 */
LedControl lc=LedControl(20,5,21,1);

int lowPin = 11;             /* ground pin for the buton ;-) */
int buttonPin = 9;           /* choose the input pin for the pushbutton */

int animations = 18;         /* the number of animations we have */

int lastButtonState = LOW;   /* the previous reading from the input pin */
long lastDebounceTime = 0;   /* the last time the output pin was toggled */
long debounceDelay = 50;     /* the debounce time; increase if the output flickers */
int anicount = 0;
int buttonState = LOW;

void setup() {
	/*
	   The MAX72XX is in power-saving mode on startup,
	   we have to do a wakeup call
	 */
	lc.shutdown(0,false);
	/* Set the brightness to a medium values */
	lc.setIntensity(0,15);
	/* and clear the display */
	lc.clearDisplay(0);
	/* setup pins */
	pinMode(buttonPin, INPUT_PULLUP);
	pinMode(lowPin, OUTPUT);
	digitalWrite(lowPin, LOW);
}

void loop() {
	switch (anicount) {
		case 0:
			ijhacklogo();
			break;
		case 1:
			ghost();
			break;
		case 2:
			invader();
			break;
		case 3:
			heart();
			break;
		case 4:
			invadesquid();
			break;
		case 5:
			jumper();
			break;
		case 6:
			ijlogowink();
			break;
		case 7:
			heartbeat();
			break;
		case 8:
			eq();
			break;
		case 9:
			invaderagain();
			break;
		case 10:
			pong();
			break;
		case 11:
			snake();
			break;
		case 12:
			arrows();
			break;
		case 13:
			directions();
			break;
		case 14:
			packman();
			break;  
		case 15:
			diagonals();
			break;  
		case 16:
			waterdrip();
			break;  
		case 17:
			aliens();
			break;  
		case 18:
			blockanim();
			break;  
	}
}

bool render(byte* animation, int delaytime) {
	lc.setColumn(0,0,animation[7]);
	lc.setColumn(0,1,animation[6]);
	lc.setColumn(0,2,animation[5]);
	lc.setColumn(0,3,animation[4]);
	lc.setColumn(0,4,animation[3]);
	lc.setColumn(0,5,animation[2]);
	lc.setColumn(0,6,animation[1]);
	lc.setColumn(0,7,animation[0]);

	long startTime = millis();
	while ((startTime + delaytime) > millis()){

		// read the state of the switch into a local variable:
		int reading = digitalRead(buttonPin);

		// check to see if you just pressed the button 
		// (i.e. the input went from HIGH to LOW),  and you've waited 
		// long enough since the last press to ignore any noise:  

		// If the switch changed, due to noise or pressing:
		if (reading != lastButtonState) {
			// reset the debouncing timer
			lastDebounceTime = millis();
		} 

		if ((millis() - lastDebounceTime) > debounceDelay) {
			// whatever the reading is at, it's been there for longer
			// than the debounce delay, so take it as the actual current state:

			// if the button state has changed:
			if (reading != buttonState) {
				buttonState = reading;

				// only toggle the animation if the new button state is HIGH
				if (buttonState == LOW) {
					anicount++;
					if (anicount > animations) {
						anicount = 0;
					}
					return true;
				}
			}
		}

		// save the reading.  Next time through the loop,
		// it'll be the lastButtonState:
		lastButtonState = reading;
	}
	return false;  /* don't skip the rest */
} 
