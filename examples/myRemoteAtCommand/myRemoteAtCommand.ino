/*
 Name:		RemoteAtCommand.ino
 Created:	11/3/2017 2:22:03 PM
 Author:	Julio Lima
*/

#include <XBee.h>
#include <SoftwareSerial.h>

// Define SoftSerial TX/RX pins
// Connect Arduino pin 8 to TX of usb-serial device
uint8_t ssRX = 8;
// Connect Arduino pin 9 to RX of usb-serial device
uint8_t ssTX = 9;
// Remember to connect all devices to a common Ground: XBee, Arduino and USB-Serial device
SoftwareSerial nss(ssRX, ssTX);

XBee xbee = XBee();

// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[2] = { 'D','0' };
uint8_t d0Value[] = { 0x4 };

// SH + SL of your remote radio
XBeeAddress64 remoteAddress = XBeeAddress64(0x00, BROADCAST_ADDRESS);

// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));

// Create a Remote AT response object
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();

void setup() {
	Serial.begin(9600);
	xbee.begin(Serial);

	nss.begin(9600);

	//Wait the Xbee configurations.
	delay(5000);

  nss.print("Hello World");
}

int count = 0;

void loop() {
	if (count % 2 == 0)
	{
		remoteRequest(0, 4);
	}
	else
	{
		remoteRequest(0, 5);
	}

	delay(1000);
	count++;
}

uint8_t value;

bool  remoteRequest(uint8_t dPort, uint8_t dState) {

	// Set a D"dPort" port.
	// Add 48 to dPort to pass to ASCII.
	d0Cmd[1] = { dPort + 48 };

	// Set a D"i" value.
	d0Value[0] = { dState };

	// Now reuse same object for DIO0 command.
	remoteAtRequest.setCommand(d0Cmd);
	remoteAtRequest.setCommandValue(d0Value);
	remoteAtRequest.setCommandValueLength(sizeof(d0Value));

	int tryTimes = 0;
	while (executeRemote() == dState && tryTimes < 5) {
		executeRemote();
		tryTimes++;
	}
}

uint8_t executeRemote() {
	// Set and query to compare
	setAndQueryRemote();

	// It's a good idea to clear the set value so that the object can be reused for a query.
	remoteAtRequest.clearCommandValue();

	return setAndQueryRemote();
}

uint8_t setAndQueryRemote() {

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
            value = remoteAtResponse.getValue()[i];
            return value;
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
