void loop() 
{
  // send data only when you receive data:
  if (Serial.available() > 0) {         
  }
}

void i_do_not_already_understand(){
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

void timer_one()
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
