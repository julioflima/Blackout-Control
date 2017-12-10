//Libraries
#include "Blackout-Control.h"

#define TIMEBASE 60000

//BlackoutControl object declaration.
static BlackoutControl blk;

void setup() {
	// Attach the Extern Interruptions.
	attachInterrupt(digitalPinToInterrupt(blk.hard.get_pin_substation_relay()), extIntSubstation, FALLING);
	attachInterrupt(digitalPinToInterrupt(blk.hard.get_pin_phase_relay()), extIntPhase, FALLING);

	// Wait the Xbee configurations.
	delay(5000);

	// Setting the boudrate of Xbee.
	Serial.begin(9600);

	dbInit();
}

int count = 0;
void loop()
{
	// XBEE TESTs
	// -> BROADCAST TEST 
	//if (count % 2 == 0) {
	//	blk.db.xb.remoteRequest(XBeeAddress64(0x00, BROADCAST_ADDRESS), 0, 4);
	//}
	//else {
	//	blk.db.xb.remoteRequest(XBeeAddress64(0x00, BROADCAST_ADDRESS), 0, 5);
	//}
	// -> UNICAST TEST
	if (count % 2 == 0) {
		blk.db.xb.remoteRequest(XBeeAddress64(0x0013A200, 0x4091572D), 0, 4);
	}
	else {
		blk.db.xb.remoteRequest(XBeeAddress64(0x0013A200, 0x4091572D), 0, 5);
	}
	delay(1000);
	count++;

	//DATABASE TEST
	//uint8_t nLines = blk.db.countLine();
	//for (uint8_t i = 0; i < nLines; i++) {
	//	delay(1000);
	//	blk.db.split(blk.db.getLine(i));
	//}

	// MAIN TEST
	//if ((millis() - blk.hard.get_tick() > TIMEBASE)) {
	//	// Verify sisnisters.
	//	blk.verify_phase_relay();
	//	blk.verify_substation_relay();
	//	// Reset tick;
	//	blk.hard.set_tick(millis());
	//}
}

void dbInit(void) {
	blk.db = Database();
	blk.db.add(1286656, 1083266861);
}

void extIntSubstation(void) {
	if ((millis() - blk.hard.get_delayHysteresis() > TIMEBASE) || (blk.hard.get_delayHysteresis() == 0)) {
		//Verify sisnister.
		blk.verify_substation_relay();
		// Reset delay;
		blk.hard.set_delayHysteresis(millis());
	}
}

void extIntPhase(void) {
	if ((millis() - blk.hard.get_delayHysteresis() > TIMEBASE) || (blk.hard.get_delayHysteresis() == 0)) {
		//Verify sisnister.
		blk.verify_phase_relay();
		// Reset delay;
		blk.hard.set_delayHysteresis(millis());
	}
}
