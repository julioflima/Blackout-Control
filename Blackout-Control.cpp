//Libraries
#include <Arduino.h>
#include <Blackout-Control.h>

void Status::Status(void){
    this.set_stop();    
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

void Status::get_status(void){
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

void Input::Input(void){
  this.relay_substastion = 0;
  this.relay_ff = 0;
}

void Input::set_relay_substastion(bool relay_substastion){
  this.relay_substastion;
}

void Input::set_relay_ff(bool relay_ff){
  this.relay_ff = relay_ff;
}

bool Input::get_relay_substastion(){
  return relay_substastion;
}

bool Input::get_relay_ff(){
  return relay_ff;
}

void Hardware::i_do_not_already_understand(void){
      //Read the incoming String:
    String received_i = Serial.readString();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(received_i);

    unsigned long int a = received_i.toInt();
    Serial.println(a,HEX);
    a = a << 8;
    Serial.println(a,HEX);
    a = (a) & 0xFFFF;
    Serial.println(a,HEX);
    a = (a << 8) & 0xFFFFFFFF;
    Serial.println(a,HEX);
    String test = "0013A20040915718";
    Serial.println(test.toInt(),HEX);
}

void Hardware::timer_one(void)
{
  //Update the input state.
  state.relay_substation = digitalRead(pin_relay_substation);
  state.relay_ff = digitalRead(pin_relay_ff);
}

void Hardware::reset(void)
{
  asm volatile ("jmp 0x0000");
}
