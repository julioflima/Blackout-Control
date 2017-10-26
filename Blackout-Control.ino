//Libraries
#include "TimerOne.h"
#include <SdFat.h>

//Input declaration.
#define relay_substastion 9
#define relay_ff 8

//SPI declaratio.
// **MOSI - pin 11
// **MISO - pin 12
// **CLK - pin 13
// **CS - pin 10
// Just de CS, the other pins are declarated inside of library.
#define chipSelect 10

//Time global declaration.
unsigned long int  rtime_1 = 0;

//Globals declarations.

//SD object declaration.
SdFat sd;

//File object declaration.
SdFile myFile;

