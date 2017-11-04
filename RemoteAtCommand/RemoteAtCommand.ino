#include <xbee-arduino-master\XBee.h>




// Set DIO0 (pin 20) to Analog Input



// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, irCmd, irValue, sizeof(irValue));


