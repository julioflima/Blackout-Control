//libraries
#include <EEPROM.h>
#include "TimerOne.h"

//Input declaration.
const int relay_substastion = 9; //
const int relay_ff = 8;

//Time global declaration.
unsigned long int  rtime_1 = 0;

//Creating type of data called address_xbee
typedef char address_xbee[8];

//Globals declarations.

