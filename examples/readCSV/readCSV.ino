#include <SdFat.h>

// SD chip select pin
const uint8_t chipSelect = 10;

// file system object
SdFat sd;

//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))
//------------------------------------------------------------------------------

void writeFile() {

  // create or open and truncate output file
  ofstream sdout("address.txt");
  
  // write file from string stored in flash
  sdout << pstr(
    "4294967296,4294967296,20,30,6,30,20,30,6,30,20,30,6,30,20,30,6,30,158\n") << flush;

  Serial.println("Write: 4294967296,4294967296,20,30,6,30,20,30,6,30,20,30,6,30,20,30,6,30,158\n");

  // check for any errors
  if (!sdout) error("writeFile");
  
  sdout.close();
}
//------------------------------------------------------------------------------
void testGetline() {
  const int line_buffer_size = 69 +1;
  char buffer[line_buffer_size];
  ifstream sdin("address.txt");

  while (sdin.getline(buffer, line_buffer_size, '\n') || sdin.gcount()) {
    int count = sdin.gcount();
    Serial.println( buffer );
  }
}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  while (!Serial) {} // wait for Leonardo
  delay(400);  // catch Due reset problem
  
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();
  
  // create test file
  writeFile();
  
  Serial.println("");

  // read and print test
  testGetline();  
  
  Serial.println("Done!");
}
void loop() {
    // read and print test
  testGetline();  
  }
