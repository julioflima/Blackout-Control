//Libraries
#include "Blackout-Control.h"

//Input object declaration.
Input in;

//BlackoutControl object declaration.
static BlackoutControl blk;

void setup() {

	// Attach the Extern Interruptions.
	attachInterrupt(digitalPinToInterrupt(in.get_pin_relay_substation()), in.extIntSubstation, FALLING);
	attachInterrupt(digitalPinToInterrupt(in.get_pin_relay_ff()), in.extIntFF, FALLING);

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

	uint8_t nLines = blk.db.countLine();

	for (uint8_t i = 0; i < nLines; i++) {
		delay(1000);
		blk.db.split(blk.db.getLine(i));
	}

}

void dbInit() {
	//blk.db.del();
	//blk.db = Database();
	blk.db.add(1286656, 1083266861);
}