//Libraries
#include "Blackout-Control.h"
#include <TimerOne.h>

void setup() {

	//Input object declaration. The Input object build the Hardware too.
	Input in;

	//Setting the Timer 0.
	Timer1.initialize(100000);  //Set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
	Timer1.attachInterrupt(in.timer_one);  //Attach the service routine here

	//Setting the Extern Interruptions.
	attachInterrupt(digitalPinToInterrupt(in.get_pin_relay_substation()), in.extIntSubstation, FALLING);
	attachInterrupt(digitalPinToInterrupt(in.get_pin_relay_ff()), in.extIntFF, FALLING);

	//Setting the boudrate.
	Serial.begin(9600);
}

void loop()
{
	//Send data only when you receive data:
	if (Serial.available() > 0) {
	}
}


