#include "Blackout-Control.h"
#include <SdFat.h>
#include <SoftwareSerial.h>

SdFat sd;
SdFile myFile;


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

int Database::read_address(int i) {
	// re-open the file for reading:
	if (!myFile.open("test.txt", O_READ)) {
		sd.errorHalt("opening test.txt for read failed");
	}
	Serial.println("test.txt:");

	// read from the file until there's nothing else in it:
	int data;
	while ((data = myFile.read()) >= 0) Serial.write(data);
	// close the file:
	myFile.close();
}

void Database::add_address(int address) {
	// open the file for write at end like the Native SD library
	if (!myFile.open("test.txt", O_RDWR | O_CREAT | O_AT_END)) {
		sd.errorHalt("opening test.txt for write failed");
	}
	// if the file opened okay, write to it:
	Serial.print("Writing to test.txt...");
	myFile.println("testing 1, 2, 3.");

	// close the file:
	myFile.close();
	Serial.println("done.");
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
	pin_relay_substation = 2;
	pin_relay_ff = 3;
	pin_chipSelect = 10;
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

Input::Input(void) {
	relay_substation = 0;
	relay_ff = 0;
}

bool Input::get_relay_substation(void) {
	return relay_substation;
}

bool Input::get_relay_ff(void) {
	return relay_ff;
}

void Input::set_relay_substation(bool relay_substation) {
	this->relay_substation = relay_substation;
}

void Input::set_relay_ff(bool relay_ff) {
	this->relay_ff = relay_ff;
}

void Input::timer_one(void) {
	//Update the input state.
}

void Input::extIntSubstation(void) {
	//Update the port 2.

	Input in;
	in.set_relay_substation(digitalRead(in.get_pin_relay_substation()));
	Serial.println("INTERRUPTION 2");
}

void Input::extIntFF(void) {
	//Update the port 3.
	Input in;
	in.set_relay_ff(digitalRead(in.get_pin_relay_ff()));
	Serial.println("INTERRUPTION 3");
}

