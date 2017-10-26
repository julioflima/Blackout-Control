//Libraries
#include <TimerOne.h>
#include <SdFat.h>

//Input declaration.
#define pin_relay_substastion 9
#define pin_relay_ff 8

//SPI declaratio.
// **MOSI - pin 11
// **MISO - pin 12
// **CLK - pin 13
// **CS - pin 10
// Just de CS, the other pins are declarated inside of library.
#define chipSelect 10

//SD object declaration.
SdFat sd;

//File object declaration.
SdFile myFile;

//Input object declaration.
Input state;

//Hardware object declaration.
Hardware hard;

//Time global declaration.
unsigned long int  rtime_1 = 0;

//Globals declarations.


void setup() {
  // Initialize SdFat.
  // Use half speed like the native library.
  // Change to SPI_FULL_SPEED for more performance.
  sd.begin(chipSelect, SPI_HALF_SPEED);

  // If the file exists, this flag has no effect. Otherwise, the file shall be created. And close.
  myFile.open("adresses.txt", O_RDWR | O_CREAT | O_AT_END);
  // if the file opened okay, write to it:
  Serial.print("Writing to test.txt...");
  myFile.println("testing 1, 2, 3.");
  myFile.close();

  //Throut the ports to input.
  pinMode(pin_relay_substastion, INPUT);
  pinMode(pin_relay_ff, INPUT);

  //Setting the boudrate.
  Serial.begin(9600);

  //Setting the Timer 0.
  Timer1.initialize(100000);  //Set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt(hard.timer_one);  //Attach the service routine here

}

void loop()
{
  //Send data only when you receive data:
  if (Serial.available() > 0) {
  }
}


