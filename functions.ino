void loop() 
{
  // send data only when you receive data:
  if (Serial.available() > 0) {
          // read the incoming byte:
          address_xbee = Serial.read();
  
          // say what you got:
          Serial.print("I received: ");
          Serial.println(address_xbee, HEX);
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

template <class T> int EEPROM_writeAnything(int address, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(address++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int address, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(address++);
    return i;
}

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void EEPROMWritelong(int address, long value){
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = ((value >> 0) & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  
  //Write the 4 bytes into the addressprom memory.
  EEPROM.write(address + 0, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

long addressPROMReadlong(long address){
  //Read the 4 bytes from the addressprom memory.
  long four = EEPROM.read(address + 0 );
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  
  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
