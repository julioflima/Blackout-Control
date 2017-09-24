
void setup(){ 

  //Throut the ports to input.
  pinMode(relay_substastion, INPUT);   
  pinMode(relay_ff, INPUT);  
  
  //Setting the boudrate;
  Serial.begin(9600);

  //Setting the Timer 0.
  Timer1.initialize(100000);  //Set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt(happen);  //Attach the service routine here
  
  //Reading address from EEPROM.
  digitalWrite(rele_1, EEPROM.read(address_rele_1));
  digitalWrite(rele_2, EEPROM.read(address_rele_2));
  
  //Reading times from EEPROM.
  digitalWrite(rele_1, EEPROM.read(address_rele_1));
  digitalWrite(rele_2, EEPROM.read(address_rele_2));
}