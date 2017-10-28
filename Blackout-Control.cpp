#include <Blackout-Control.h>

Status::Status(void){
    status = 0;
}

void Status::set_stop(void){
    status = 0;
}

void Status::set_automatic(void){
    status = 1;
}

void Status::set_manual(void){
    status = 2;
}
  
void Status::set_hibrid(void){
    status = 3;
}

char Status::get_status(void){
    return status;
}

int Database::read_address(int i){
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

void Database::add_address(int address){
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

Hardware::Hardware(void) {
	relay_ff = 8;
	relay_substation = 9;
	chipSelect = 10;
}

char Hardware::get_relay_ff(void) {
	return relay_ff;
}

char Hardware::get_relay_substation(void) {
	return relay_substation;
}

char Hardware::get_chipSelect() {
	return chipSelect;
}

void Hardware::set_TRISn(void) {
	//Throut the ports to input.
	pinMode(get_relay_ff(), INPUT);
	pinMode(get_relay_substation(), INPUT);
	//Throut the ports to output.
}

Input::Input(void) {
	relay_substation = 0;
	relay_ff = 0;
	hard = Hardware();
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

void Input::timer_one(void)
{
	//Update the input state.
	set_relay_substation(digitalRead(hard.get_relay_substation()));
	set_relay_ff(digitalRead(hard.get_relay_ff()));
}

