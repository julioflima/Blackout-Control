#include "Blackout-Control.h"

// Define SoftSerial TX/RX pins
// Connect Arduino pin 8 to TX of usb-serial device
#define ssRX 8
// Connect Arduino pin 9 to RX of usb-serial device
#define ssTX 9
// Remember to connect all devices to a common Ground: XBee, Arduino and USB-Serial device
static SoftwareSerial nss(ssRX, ssTX);

Status::Status(void) {
	status = 0;
}

void Status::set_stop(void) {
	status = 0;
}

void Status::set_automatic(void) {
	status = 1;
}

void Status::set_manual(void) {
	status = 2;
}

void Status::set_hibrid(void) {
	status = 3;
}

char Status::get_status(void) {
	return status;
}

Database::Database() {
	if (!sd.begin(get_pin_chipSelect(), SPI_HALF_SPEED)) nss.println("SD don't init.");

	// Open or create the file.
	if (!myFile.open("address.txt", O_RDWR | O_CREAT | O_AT_END)) nss.println("Opening address.txt for create failed.");

	// Close the file.
	myFile.close();
}

void Database::print() {
	// Re-open the file for reading to print.
	if (!myFile.open("address.txt", O_READ)) nss.println("Opening address.txt for print failed.");

	// Read from the file and print.
	int16_t data;
	while ((data = myFile.read()) >= 0) nss.println(data);

	// Close the file. 
	myFile.close();
}

String Database::getLine() {
	// Re-open the file for reading to print.
	if (!myFile.open("address.txt", O_READ)) nss.println("Opening address.txt for print failed.");

	// Read from the file store in String.
	int16_t data;
	String line;
	while ((data = myFile.read()) >= 0) {
		if (data == '\n') {
			nss.print("Isso é uma linha:    ");
		}
		else nss.write(data);
	}

	// Close the file. 
	myFile.close();
}

uint8_t Database::get_time(String line, uint8_t port, bool act_dea, char type) {

}

void Database::del() {
	// Open for delete the file.
	if (!myFile.open("address.txt", O_RDWR)) nss.println("Opening address.txt for exclude failed.");
	if (!myFile.remove()) nss.println("Removing file failed.");
}

void Database::add(uint32_t sh = 0x00, uint32_t sl = BROADCAST_ADDRESS,
	uint8_t act_h_d0 = 20, uint8_t act_min_d0 = 30, uint8_t dea_h_d0 = 6, uint8_t dea_min_d0 = 30, uint8_t act_h_d1 = 20, uint8_t act_min_d1 = 30, uint8_t dea_h_d1 = 6, uint8_t dea_min_d1 = 30,
	uint8_t act_h_d2 = 20, uint8_t act_min_d2 = 30, uint8_t dea_h_d2 = 6, uint8_t dea_min_d2 = 30, uint8_t act_h_d3 = 20, uint8_t act_min_d3 = 30, uint8_t dea_h_d3 = 6, uint8_t dea_min_d3 = 30) {
	// Open the file for write the address and schedules.
	if (!myFile.open("address.txt", O_WRITE | O_AT_END)) {
		nss.println("Opening address.txt for add address failed.");
	}

	// If the file is opened, add address to it.
	// Address, SH and SL.
	myFile.print(sh, HEX);
	myFile.print(",");
	myFile.print(sl, HEX);
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
	myFile.print(",");

	// Now calcutate the HEC checksum:
	uint8_t checksum = genCheckSum(sh, sl,
		act_h_d0, act_min_d0, dea_h_d0, dea_min_d0, act_h_d1, act_min_d1, dea_h_d1, dea_min_d1,
		act_h_d2, act_min_d2, dea_h_d2, dea_min_d2, act_h_d3, act_min_d3, dea_h_d3, dea_min_d3);
	myFile.println(checksum, HEX);

	// Close the file.

	myFile.close();

	// Report added.
	nss.print("The address,  ");
	nss.print(sh, HEX);
	nss.print(sl, HEX);
	nss.println(", was added.");
}

uint8_t Database::genCheckSum(uint32_t sh, uint32_t sl,
	uint8_t act_h_d0, uint8_t act_min_d0, uint8_t dea_h_d0, uint8_t dea_min_d0, uint8_t act_h_d1, uint8_t act_min_d1, uint8_t dea_h_d1, uint8_t dea_min_d1,
	uint8_t act_h_d2, uint8_t act_min_d2, uint8_t dea_h_d2, uint8_t dea_min_d2, uint8_t act_h_d3, uint8_t act_min_d3, uint8_t dea_h_d3, uint8_t dea_min_d3) {

	// Now calcutate the HEC checksum:
	uint8_t checksum = 0;
	checksum = (sh & 0xff) + ((sh >> 8) & 0xff) + ((sh >> 16) & 0xff) + ((sh >> 32) & 0xff);
	checksum += (sl & 0xff) + ((sl >> 8) & 0xff) + ((sl >> 16) & 0xff) + ((sl >> 24) & 0xff);
	checksum += act_h_d0 + act_min_d0 + dea_h_d0 + dea_min_d0 + act_h_d1 + act_min_d1 + dea_h_d1 + dea_min_d1;
	checksum += act_h_d2 + act_min_d2 + dea_h_d2 + dea_min_d2 + act_h_d3 + act_min_d3 + dea_h_d3 + dea_min_d3;
	checksum ^= 0xFF;
	checksum += 1;
	return checksum;
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

Hardware::Hardware(void) {
	// Setting the boudrate of Software Serial.
	nss.begin(9600);

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
	pinMode(get_pin_relay_ff(), INPUT);
	pinMode(get_pin_relay_substation(), INPUT);
	//Throut the ports to output.
}

void Hardware::inputLvl(void) {
	//Throut the ports to input.
	//Throut the resistor to pullup.
	pinMode(get_pin_relay_ff(), INPUT_PULLUP);
	pinMode(get_pin_relay_substation(), INPUT_PULLUP);
	//Throut the resistor to pulldown.
}

char Hardware::get_pin_relay_substation(void) {
	return pin_relay_substation;
}

char Hardware::get_pin_relay_ff(void) {
	return pin_relay_ff;
}

char Hardware::get_pin_chipSelect() {
	return pin_chipSelect;
}

bool Input::relay_substation;

bool Input::relay_ff;

bool Input::get_relay_substation(void) {
	return relay_substation;
}

bool Input::get_relay_ff(void) {
	return relay_ff;
}

void Input::set_relay_substation(bool _relay_substation) {
	relay_substation = _relay_substation;
}

void Input::set_relay_ff(bool _relay_ff) {
	relay_ff = _relay_ff;
}

void Input::timer_one(void) {
	//Update the input state.
	digitalWrite(13, HIGH);
	Serial.println(digitalRead(2));
}

void Input::extIntSubstation() {
	//Update the port 2.
	set_relay_substation(digitalRead(get_pin_relay_substation()));
	nss.println("Blackout, generator in.");
}

void Input::extIntFF() {
	//Update the port 3.
	set_relay_ff(digitalRead(get_pin_relay_ff()));
	nss.println("Blackout, missing some phase.");
}

Status BlackoutControl::st;

Comunication BlackoutControl::xb;

Database BlackoutControl::db;

BlackoutControl::BlackoutControl() {
	// Setting the Xbee.
	xb.xbee.begin(Serial);
}

void BlackoutControl::turnAllOut(void) {
	// Change the status to stop.
	st.set_stop();

	// Increment i and send in broadcast the value of digital ports to low.
	for (uint8_t i = 0; i < 4; i++) {
		xb.remoteRequest(XBeeAddress64(0x00, BROADCAST_ADDRESS), i, 4);
		delay(400);
	}
}

void BlackoutControl::turnAllIn(void) {
	// Change the status to automatic.
	st.set_automatic();
}

void BlackoutControl::turnIn(void) {
	// Change the status to automatic.
	st.set_automatic();
}

void BlackoutControl::turnOut(void) {
	// Change the status to automatic.
	st.set_automatic();
}
