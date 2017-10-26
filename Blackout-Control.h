class Status{
  private:
    byte status;
  public:
    Status(void);
    void set_stop(void);
    void set_stop(void);
    void set_automatic(void);
    void set_manual(void);
    void set_hibrid(void);
    byte get_status(void);
};

class Time{
  private:
    byte day;
    byte month;
    byte year;
    byte hour;
    byte minute;
    byte second;
  public:
    void set_date(byte day, byte month, byte year);
    void set_time(byte hour, byte minute, byte second);
    int get_date(void);
    int get_time(void);
};

class Database{
  //CHANGE int TO STRING
  public:
    int read_address(int i);   
    int get_hour_address(int address);
    int get_minute_address(int address);
    void add_address(int address);  
    void delete_address(int address);
    void set_time_turn_off(int address,byte hour, byte minute);
    void set_time_turn_on(int address,byte hour, byte minute);
};

class Input{
  private:
    bool relay_substastion;
    bool relay_ff;
  public:
    Input(void);
    void set_relay_substastion(bool relay_substastion);
    void set_relay_ff(bool relay_ff);
    bool get_relay_substastion();
    bool get_relay_ff();   
};

class Update{
  //CHANGE int TO STRING
  public:
    void set_turn_off(int address);
    void turn_on(int address,byte hour);  
};

class Hardware{
  public:
    void reset(void);
    void timer_one(void);
    void i_do_not_already_understand(void);
}


