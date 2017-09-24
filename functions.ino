void loop() 
{
  // send data only when you receive data:
  if (Serial.available() > 0) {
          // read the incoming byte:
          address_xbee address = Serial.read();
  
          // say what you got:
          Serial.print("I received: ");
          Serial.println(address);
  }
}

void checkUpNewEntries(unsigned long int armazenavalor){
  //Lê da EEPROM as teclas cadastradas para comparação.
  unsigned long int key_1 = EEPROMReadlong(5);
  unsigned long int key_2 = EEPROMReadlong(6);
}

void happen()
{
	
}

void reset()
{
  unsigned long int reset_t = 4000000000;
  if(millis() > reset_t)
  {
    asm volatile ("jmp 0x0000");
  }
}
