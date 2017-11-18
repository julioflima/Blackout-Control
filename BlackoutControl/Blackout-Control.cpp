#include "Blackout-Control.h"

// Define SoftSerial TX/RX pins
// Connect Arduino pin 8 to TX of usb-serial device
#define ssRX 8
// Connect Arduino pin 9 to RX of usb-serial device
#define ssTX 9
// Remember to connect all devices to a common Ground: XBee, Arduino and USB-Serial device
static SoftwareSerial nss(ssRX, ssTX);

void SoftSerial::print(String data) {
	nss.print(data);
}

void SoftSerial::println(String data) {
	nss.println(data);
}

//Comunication Database::xb;
SdFat Database::sd;
SdFile Database::myFile;
//uint32_t Database::sh;
//uint32_t Database::sl;
uint8_t Database::act_h_d0;
uint8_t Database::act_min_d0;
uint8_t Database::dea_h_d0;
uint8_t Database::dea_min_d0;
uint8_t Database::act_h_d1;
uint8_t Database::act_min_d1;
uint8_t Database::dea_h_d1;
uint8_t Database::dea_min_d1;
uint8_t Database::act_h_d2;
uint8_t Database::act_min_d2;
uint8_t Database::dea_h_d2;
uint8_t Database::dea_min_d2;
uint8_t Database::act_h_d3;
uint8_t Database::act_min_d3;
uint8_t Database::dea_h_d3;
uint8_t Database::dea_min_d3;
uint8_t Database::checksum;

Database::Database() {
	// Setting the Xbee.
	//xb.xbee.begin(Serial);

	if (!sd.begin(get_pin_chipSelect(), SPI_FULL_SPEED)) nss.println("SD don't init.");

	// Open or create the file.
	if (!myFile.open("ADDRESS.TXT", O_RDWR | O_CREAT | O_AT_END)) nss.println("Opening address.txt for create failed.");
	else nss.println("File was created!");

	// Close the file.
	myFile.close();
}

uint8_t Database::countLine() {
	static const int line_buffer_size = 69 + 1;
	static char buffer[line_buffer_size];
	ifstream sdin("address.txt");
	uint8_t count = 0;

	while (sdin.getline(buffer, line_buffer_size, '\n') || sdin.gcount()) {
		// Print line;
		//nss.println("Counter " + String(count) + ": " + buffer);

		// Increase counter.
		count++;
	}

	// Close sdin object.
	sdin.close();

	// Return line count.
	return count;
}

String Database::getLine(uint8_t line) {
	static const int line_buffer_size = 69 + 1;
	static char buffer[line_buffer_size];
	ifstream sdin("address.txt");
	int count = 0;

	while (sdin.getline(buffer, line_buffer_size, '\n') || sdin.gcount()) {
		if (count == line) {
			// Print line, close sdin object and break the while.
			nss.println("Got Line " + String(count) + ": " + buffer);
			sdin.close();
			break;
		}

		// Increase counter.
		count++;
	}

	// Return line.
	return buffer;
}

void Database::split(String buffer) {
	static uint8_t fields[17];
	String aux = "";
	uint8_t nComma = 0;

	nss.print("Splitted Line: ");

	for (uint8_t i = 0; i < buffer.length(); i++) {
		// Concatenate char until comma.
		aux.concat(buffer.charAt(i));

		// If comma or end array, comma plus plus, save the value and clean the String aux.
		if (buffer.charAt(i) == ',' || nComma == 17) {
			nComma++;
			if (nComma == 1) {
				sh = aux.toInt();
				nss.print(sh);
				aux = "";
			}
			else if (nComma == 2) {
				sl = aux.toInt();
				nss.print(sl);
				aux = "";
			}
			else if (nComma > 2) {
				fields[i + 3] = aux.toInt();
				nss.print(fields[i + 3]);
				aux = "";
			}
			if (buffer.charAt(i) == ',') {
				nss.print(",");
			}
		}
	}

	nss.println("");
}

void Database::add(uint32_t sh = 0x00, uint32_t sl = BROADCAST_ADDRESS,
	uint8_t act_h_d0 = 20, uint8_t act_min_d0 = 30, uint8_t dea_h_d0 = 6, uint8_t dea_min_d0 = 30, uint8_t act_h_d1 = 20, uint8_t act_min_d1 = 30, uint8_t dea_h_d1 = 6, uint8_t dea_min_d1 = 30,
	uint8_t act_h_d2 = 20, uint8_t act_min_d2 = 30, uint8_t dea_h_d2 = 6, uint8_t dea_min_d2 = 30, uint8_t act_h_d3 = 20, uint8_t act_min_d3 = 30, uint8_t dea_h_d3 = 6, uint8_t dea_min_d3 = 30) {
	// Open the file for write the address and schedules.
	if (!myFile.open("address.txt", O_WRITE | O_AT_END)) {
		nss.println("Opening address.txt for add address failed.");
	}
	else {
		// If the file is opened, add address to it.
		// Address, SH and SL.
		myFile.print(sh, DEC);
		myFile.print(",");
		myFile.print(sl, DEC);
		myFile.print(",");

		// Feeding the time of activation and deactivation of D"port". 
		myFile.print(act_h_d0, DEC);
		myFile.print(",");
		myFile.print(act_min_d0, DEC);
		myFile.print(",");
		myFile.print(dea_h_d0, DEC);
		myFile.print(",");
		myFile.print(dea_min_d0, DEC);
		myFile.print(",");
		myFile.print(act_h_d1, DEC);
		myFile.print(",");
		myFile.print(act_min_d1, DEC);
		myFile.print(",");
		myFile.print(dea_h_d1, DEC);
		myFile.print(",");
		myFile.print(dea_min_d1, DEC);
		myFile.print(",");
		myFile.print(act_h_d2, DEC);
		myFile.print(",");
		myFile.print(act_min_d2, DEC);
		myFile.print(",");
		myFile.print(dea_h_d2, DEC);
		myFile.print(",");
		myFile.print(dea_min_d2, DEC);
		myFile.print(",");
		myFile.print(act_h_d3, DEC);
		myFile.print(",");
		myFile.print(act_min_d3, DEC);
		myFile.print(",");
		myFile.print(dea_h_d3, DEC);
		myFile.print(",");
		myFile.print(dea_min_d3, DEC);

		// Report added.
		nss.print("The address,  ");
		nss.print(sh, HEX);
		nss.print(sl, HEX);
		nss.println(", was added.");
	}

	// By the way, close the file.
	myFile.close();
}

void Comunication::remoteRequest(XBeeAddress64 remoteAddress, uint8_t dPort, uint8_t dState) {
	// Set a D"dPort" port.
	// Add 48 to dPort to pass to ASCII.
	atCmd[1] = { dPort + 48 };

	// Set a D"i" value.
	atValue[0] = { dState };

	// Now reuse same object for D"dPort" command.
	remoteAtRequest.setRemoteAddress64(remoteAddress);
	remoteAtRequest.setCommand(atCmd);
	remoteAtRequest.setCommandValue(atValue);
	remoteAtRequest.setCommandValueLength(sizeof(atValue));

	int tryTimes = 0;
	while (executeRemote() == dState && tryTimes < 5) {
		executeRemote();
		tryTimes++;
	}
}

uint8_t Comunication::executeRemote() {
	// Set and query to compare
	setAndQueryRemote();

	// It's a good idea to clear the set value so that the object can be reused for a query.
	remoteAtRequest.clearCommandValue();

	return setAndQueryRemote();
}

uint8_t Comunication::setAndQueryRemote() {
	// Send the command.
	xbee.send(remoteAtRequest);

	// Wait up until to 5 seconds for the status response.
	// If got a response.
	if (xbee.readPacket(5000)) {

		// Should be an AT command response.
		if (xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE) {
			xbee.getResponse().getRemoteAtCommandResponse(remoteAtResponse);

			// If response is OK.
			if (remoteAtResponse.isOk()) {

				// Get value of input D"i".
				if (remoteAtResponse.getValueLength() > 0) {
					for (int i = 0; i < remoteAtResponse.getValueLength(); i++) {
						// Set transation with the value of response.
						return remoteAtResponse.getValue()[i];
					}
				}
			}
			else {
				// Set transation with not OK.
				return false;
			}
		}
		else {
			// Set transation with not OK.
			return false;
		}
	}
	else {
		// Set transation with not OK.
		return false;
	}
	// Set transation with OK.
	return true;
}

uint32_t Hardware::delayHysteresis = 0;

Hardware::Hardware(void) {
	// Setting the boudrate of Software Serial.
	nss.begin(9600);

	// Setting the Extern Interruptions.
	set_TRISn();
	inputLvl();
}

void Hardware::reset() {
	// Start watchdog with the provided prescaller.
	// Some times to wait before reset: WDTO_15MS, WDTO_30MS, WDTO_60MS, WDTO_120MS, WDTO_250MS, WDTO_500MS, WDTO_1S, WDTO_2S, WDTO_4S, WDTO_8S
	wdt_enable(WDTO_15MS);
	// Wait for the prescaller time to expire.
	// Without sending the reset signal by using.
	// The wdt_reset() method stop the wdt.
	while (true) {}
}

void Hardware::set_TRISn(void) {
	//Throut the ports to input.
	pinMode(get_pin_phase_relay(), INPUT);
	pinMode(get_pin_substation_relay(), INPUT);
	//Throut the ports to output.
}

void Hardware::inputLvl(void) {
	//Throut the ports to input.
	//Throut the resistor to pullup.
	pinMode(get_pin_phase_relay(), INPUT_PULLUP);
	pinMode(get_pin_substation_relay(), INPUT_PULLUP);
	//Throut the resistor to pulldown.
}

void Hardware::set_delayHysteresis(uint32_t _delayHysteresis) {
	delayHysteresis = _delayHysteresis;
}

uint32_t Hardware::get_delayHysteresis(void) {
	return delayHysteresis;
}


uint8_t Hardware::get_state_substation_relay(void) {
	return digitalRead(pin_substation_relay);
}

uint8_t Hardware::get_state_phase_relay(void) {
	return digitalRead(pin_phase_relay);
}

uint8_t Hardware::get_pin_substation_relay(void) {
	return pin_substation_relay;
}

uint8_t Hardware::get_pin_phase_relay(void) {
	return pin_phase_relay;
}

uint8_t Hardware::get_pin_chipSelect() {
	return pin_chipSelect;
}

Database BlackoutControl::db;

BlackoutControl::BlackoutControl() {

}

void BlackoutControl::turnAllOff(void) {
	// Increment i and send in broadcast the value of digital ports to low.
	for (uint8_t i = 0; i < 4; i++) {
		//db.xb.remoteRequest(XBeeAddress64(0x00, BROADCAST_ADDRESS), i, 4);
		delay(400);
	}
	nss.println(" - ALL OFF");
}

void BlackoutControl::turnAllIn(void) {
	// Increment i and send in broadcast the value of digital ports to high.
	for (uint8_t i = 0; i < 4; i++) {
		//db.xb.remoteRequest(XBeeAddress64(0x00, BROADCAST_ADDRESS), i, 5);
		delay(400);
	}
	nss.println(" - ALL IN");
}

void BlackoutControl::turnIn(void) {
	// Change the status to automatic.
}

void BlackoutControl::turnOut(void) {
	// Change the status to automatic.
}
