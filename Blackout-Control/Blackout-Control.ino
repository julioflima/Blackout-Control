//Libraries
#include "Blackout-Control.h"
#include <TimerOne.h>
#include <Arduino.h>

void setup() {

	//Input object declaration. The Input object build the Hardware too.
	Input in;

	//Setting the boudrate.
	Serial.begin(9600);
}

void loop()
{
	//Send data only when you receive data:
	if (Serial.available() > 0) {
	}
}


