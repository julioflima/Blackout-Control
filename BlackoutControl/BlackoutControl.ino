//Libraries
#include "Blackout-Control.h"
#include <SdFat.h>

//Input object declaration.
Input in;

//SD object declaration.
SdFat sdMain;

//BlackoutControl object declaration.
BlackoutControl blk;

void setup() {

	//Init SD.
	if (!sdMain.begin(10, SPI_HALF_SPEED)) sdMain.initErrorHalt();

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

	delay(1000);

	const int line_buffer_size = 69 + 1;
	char buffer[line_buffer_size];
	ifstream sdin("address.txt");

	int line = 0;

	while (sdin.getline(buffer, line_buffer_size, '\n') || sdin.gcount()) {
		int count = sdin.gcount();
		Serial.print(String(++line));
		Serial.println(buffer);
	}

}

void dbInit() {
	blk.db.del();
	blk.db = Database();
	blk.db.add(0x0013A200, 0x4091572D);
}