#ifndef BLACKOUT-CONTROL_H
#define BLACKOUT-CONTROL_H

#include <XBee.h>

class Status {
private:
	char status;
public:
	Status(void);
	void set_stop(void);
	void set_automatic(void);
	void set_manual(void);
	void set_hibrid(void);
	char get_status(void);
};


class Time {
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

class Database {
	//CHANGE int TO STRING
public:
	int read_address(int i);
	int get_hour_address(int address);
	int get_minute_address(int address);
	void add_address(int address);
	void delete_address(int address);
	void set_time_turn_off(int address, char hour, char minute);
	void set_time_turn_on(int address, char hour, char minute);
};

class Comunication {
private:
	// Define by default the AT commands for digital ports.
	uint8_t atCmd[2] = { 'D','0' };
	// Define by default the digital port to output and low.
	uint8_t atValue[1] = { 0x4 };
	// Create a Remote AT response object
	XBeeAddress64 remoteAddress = XBeeAddress64(0x00, BROADCAST_ADDRESS);
	// Create a Remote AT request object;
	RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, atCmd, atValue, sizeof(atValue));
	// Create a Remote AT response object
	RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();
public:
	// Create a Xbee object.
	XBee xbee = XBee();
	void remoteRequest(XBeeAddress64 remoteAddress, uint8_t dPort, uint8_t dState);
	uint8_t executeRemote();
	uint8_t setAndQueryRemote();
};

class Update {
	//CHANGE int TO STRING
public:
	void set_turn_off(int address);
	void turn_on(int address, char hour);
};

class Hardware {
private:
	char pin_relay_substation;
	char pin_relay_ff;
	char pin_chipSelect;
public:
	Hardware(void);
	char get_pin_relay_ff(void);
	char get_pin_relay_substation(void);
	char get_pin_chipSelect(void);
	void set_TRISn(void);
	void inputLvl(void);
};

class Input : public Hardware {
private:
	bool relay_substation;
	bool relay_ff;
public:
	Input(void);
	void set_relay_substation(bool relay_substastion);
	void set_relay_ff(bool relay_ff);
	bool get_relay_substation(void);
	bool get_relay_ff(void);
	static void extIntSubstation(void);
	static void extIntFF(void);
	static void timer_one(void);
};
#endif

