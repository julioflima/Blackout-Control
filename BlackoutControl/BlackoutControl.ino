//Libraries
#include "Blackout-Control.h"
#include <TimerOne.h>

//BlackoutControl object declaration.
static BlackoutControl blk;

void setup() {
	// Setting the Timer One.
	// Set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz).
	Timer1.initialize(100000);
	// Attach the service routine here.
	Timer1.attachInterrupt(timerOne);

	// Attach the Extern Interruptions.
	attachInterrupt(digitalPinToInterrupt(blk.hard.get_pin_substation_relay()), extIntSubstation, CHANGE);
	attachInterrupt(digitalPinToInterrupt(blk.hard.get_pin_phase_relay()), extIntPhase, CHANGE);

	// Setting the boudrate of Xbee.
	Serial.begin(9600);

	// Wait the Xbee configurations.
	delay(0);

	dbInit();
}

int count = 0;
void loop()
{

	//if (count % 2 == 0) {
	//	xbee.remoteRequest(XBeeAddress64(0x00, BROADCAST_ADDRESS), 0, 4);
	//}
	//else {
	//	xbee.remoteRequest(XBeeAddress64(0x0013A200, 0x4091572D), 0, 5);
	//}

	//count++;

	//uint8_t nLines = blk.db.countLine();

	//for (uint8_t i = 0; i < nLines; i++) {
	//	delay(1000);
	//	blk.db.split(blk.db.getLine(i));
	//}

}

void dbInit(void) {
	//blk.db.del();
	//blk.db = Database();
	blk.db.add(1286656, 1083266861);
}

void extIntSubstation(void) {
	if ((millis() - blk.hard.get_delayHysteresis() > 60000) || (blk.hard.get_delayHysteresis() == 0)) {
		//Verify sisnister.
		blk.verify_substation_relay();
		// Reset delay;
		blk.hard.set_delayHysteresis(millis());
	}
}

void extIntPhase(void) {
	if ((millis() - blk.hard.get_delayHysteresis() > 60000) || (blk.hard.get_delayHysteresis() == 0)) {
		//Verify sisnister.
		blk.verify_phase_relay();
		// Reset delay;
		blk.hard.set_delayHysteresis(millis());
	}
}

void timerOne() {
	if ((millis() - blk.hard.get_tick() > 60000)) {
		// Verify sisnisters.
		extIntPhase();
		extIntSubstation();
		// Reset tick;
		blk.hard.set_tick(millis());
	}
}