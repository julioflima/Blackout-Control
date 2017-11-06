#ifndef BLACKOUT-CONTROL_H
#define BLACKOUT-CONTROL_H

#include <XBee.h>
#include <SdFat.h>
#include <SoftwareSerial.h>



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
private:
	SdFat sd;
	SdFile myFile;
public:
	Database(uint8_t chipSelect);
	void del();
	void add(uint32_t sh = 0x00, uint32_t sl = BROADCAST_ADDRESS,
		uint8_t act_h_d0 = 20, uint8_t act_min_d0 = 30, uint8_t dea_h_d0 = 6, uint8_t dea_min_d0 = 30, uint8_t act_h_d1 = 20, uint8_t act_min_d1 = 30, uint8_t dea_h_d1 = 6, uint8_t dea_min_d1 = 30,
		uint8_t act_h_d2 = 20, uint8_t act_min_d2 = 30, uint8_t dea_h_d2 = 6, uint8_t dea_min_d2 = 30, uint8_t act_h_d3 = 20, uint8_t act_min_d3 = 30, uint8_t dea_h_d3 = 6, uint8_t dea_min_d3 = 30);
	int get_hour_address(int address);
	void print();
	int get_minute_address(int address);
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
	void remoteRequest(XBeeAddress64 &remoteAddress, uint8_t &dPort, uint8_t &dState);
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
	const char pin_relay_substation = 2;
	const char pin_relay_ff = 3;
	const char pin_chipSelect = 10;
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
	static bool relay_substation;
	static bool relay_ff;
public:
	static void set_relay_substation(bool _relay_substastion);
	static void set_relay_ff(bool _relay_ff);
	static bool get_relay_substation(void);
	static bool get_relay_ff(void);
	static void extIntSubstation(void);
	static void extIntFF(void);
	static void timer_one(void);
};
#endif

