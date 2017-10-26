class  Status{
  private:
    char status;
  public:
   
  Status(void){
    status = 0;    
  }

  set_stop(void){
    status = 0;
  }

  set_automatic(void){
    status = 1;
  }

  set_manual(void){
    status = 2;
  }
  
  set_hibrid(void){
    status = 3;
  }

  get_status(void){
    return status;
  }
};

class Time{
  private:
    char day;
    char month;
    char year;
    char hour;
    char minute;
    char second;
  public:
    void set_date(char day, char month, char year);
    void set_time(char hour, char minute, char second);
    int get_date(void);
    int get_time(void);

};

class Database{
  //CHANGE int TO STRING
  public:
  
    int read_address(){
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
    
    int get_hour_address(int address);
    
    int get_minute_address(int address);
    
    void add_address(int address){
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
    
    void delete_address(int address);
    
    void set_time_turn_off(int address,char hour, char minute);
    
    void set_time_turn_on(int address,char hour, char minute);
      
};

class Update{
  //CHANGE int TO STRING
  public:
  
    void set_turn_off(int address);
    
    void turn_on(int address,char hour);
    
};

