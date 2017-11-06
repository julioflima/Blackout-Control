#include "Blackout-Control.h"
#include <SoftwareSerial.h>

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

Database::Database(uint8_t chipSelect) {
	if (!sd.begin(chipSelect, SPI_HALF_SPEED)) nss.println("SD don't init.");

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
	while ((data = myFile.read()) >= 0) nss.write(data);

	// Close the file.
	myFile.close();
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
	myFile.println(dea_min_d3, DEC);

	// Close the file.
	myFile.close();

	// Report added.
	nss.print("The address,  ");
	nss.print(sh, HEX);
	nss.print(sl, HEX);
	nss.println(", was added.");
}

void Comunication::remoteRequest(XBeeAddress64 &remoteAddress, uint8_t &dPort, uint8_t &dState) {
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

char Hardware::get_pin_relay_substation(void) {
	return pin_relay_substation;
}

char Hardware::get_pin_relay_ff(void) {
	return pin_relay_ff;
}

char Hardware::get_pin_chipSelect() {
	return pin_chipSelect;
}

void Hardware::set_TRISn(void) {
	//Throut the ports to input.
	pinMode(get_pin_relay_ff(), INPUT);
	pinMode(get_pin_relay_substation(), INPUT);
	//Throut the ports to output.
}

void Hardware::inputLvl() {
	//Throut the ports to input.
	//Throut the resistor to pullup.
	pinMode(get_pin_relay_ff(), INPUT_PULLUP);
	pinMode(get_pin_relay_substation(), INPUT_PULLUP);
	//Throut the resistor to pulldown.
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
	//Input in;
	//in.set_relay_substation(digitalRead(in.get_pin_relay_substation()));
	//nss.print(in.get_relay_ff, DEC);
}

void Input::extIntFF() {
	//Update the port 3.
	//Input in;
	//in.set_relay_ff(digitalRead(in.get_pin_relay_ff()));
	//nss.print(in.get_relay_ff, DEC);
}

