//Libraries
#include "Blackout-Control.h"

//Input object declaration.
Hardware hard;

//BlackoutControl object declaration.
static BlackoutControl blk;

void setup() {

	// Attach the Extern Interruptions.
	attachInterrupt(digitalPinToInterrupt(hard.get_pin_substation_relay()), extIntSubstation, CHANGE);
	attachInterrupt(digitalPinToInterrupt(hard.get_pin_phase_relay()), extIntPhase, CHANGE);

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

void dbInit() {
	//blk.db.del();
	//blk.db = Database();
	blk.db.add(1286656, 1083266861);
}

void extIntSubstation() {
	//Verify sisnister.
	if ((millis() - hard.get_delayHysteresis() > 60000) || (hard.get_delayHysteresis() == 0)) {
		if (hard.get_state_substation_relay()) {
			blk.ss.print("System OK, generator is off.");
			blk.turnAllIn();
		}
		else {
			blk.ss.print("Blackout, generator in.");
			blk.turnAllOff();
		}

		// Reset delay;
		hard.set_delayHysteresis(millis());
	}
}

void extIntPhase() {
	//Verify sisnister.
	if ((millis() - hard.get_delayHysteresis() > 60000) || (hard.get_delayHysteresis() == 0)) {
		if (hard.get_state_phase_relay()) {
			blk.ss.print("System OK, phases came back.");
			blk.turnAllIn();
		}
		else {
			blk.ss.print("Blackout, missing some phase.");
			blk.turnAllOff();
		}

		// Reset delay;
		hard.set_delayHysteresis(millis());
	}
}