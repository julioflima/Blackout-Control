void setup(){ 
  // Initialize SdFat.
  // Use half speed like the native library.
  // Change to SPI_FULL_SPEED for more performance.
  sd.begin(chipSelect, SPI_HALF_SPEED)

  // If the file exists, this flag has no effect. Otherwise, the file shall be created. And close.
  myFile.open("addresses and schedules.txt", O_CREAT);
  myFile.close();

  //Throut the ports to input.
  pinMode(relay_substastion, INPUT);   
  pinMode(relay_ff, INPUT);
  
  //Setting the boudrate.
  Serial.begin(9600);

  //Setting the Timer 0.
  Timer1.initialize(100000);  //Set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt(timer_one);  //Attach the service routine here
  
}
