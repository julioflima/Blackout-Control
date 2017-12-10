#ifndef BLACKOUT-CONTROL_H
#define BLACKOUT-CONTROL_H

#include <XBee.h>
#include <SdFat.h>
#include <SoftwareSerial.h>
#include <avr/wdt.h>

class RTC {
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
	static const uint8_t pin_substation_relay = 2;
	static const uint8_t pin_phase_relay = 3;
	static const uint8_t pin_chipSelect = 10;
	static const uint8_t pin_xbeeSelect = 7;
	static uint32_t delayHysteresis;
	static uint32_t tick;
public:
	Hardware(void);
	void print(String data);
	void println(String data);
	static void reset();
	static void inputLvl(void);
	static void outputLvl(void);
	static void set_TRISn(void);
	static void set_xbeeSelect(void);
	static void set_delayHysteresis(uint32_t _delayHysteresis);
	static void set_tick(uint32_t _tick);
	static uint32_t get_delayHysteresis(void);
	static uint32_t get_tick(void);
	static uint8_t get_pin_phase_relay(void);
	static uint8_t get_pin_substation_relay(void);
	static uint8_t get_pin_chipSelect(void);
	static uint8_t get_pin_xbeeSelect(void);
	static uint8_t get_state_substation_relay(void);
	static uint8_t get_state_phase_relay(void);
};

class Database : public Hardware {
private:
	static SdFat sd;			// SdFat object declaration.
	static SdFile myFile;		// SdFile object declaration.
	String fileName = "address.csv";
	uint32_t sh, sl;
	static uint8_t act_h_d0, act_min_d0, dea_h_d0, dea_min_d0, act_h_d1, act_min_d1, dea_h_d1, dea_min_d1,
		act_h_d2, act_min_d2, dea_h_d2, dea_min_d2, act_h_d3, act_min_d3, dea_h_d3, dea_min_d3, checksum;
public:
	Database();
	static Comunication xb;		// Comunication object declaration. The Comunication object build the Xbee too.
	void add(uint32_t sh = 0x00, uint32_t sl = BROADCAST_ADDRESS,
		uint8_t act_h_d0 = 20, uint8_t act_min_d0 = 30, uint8_t dea_h_d0 = 6, uint8_t dea_min_d0 = 30, uint8_t act_h_d1 = 20, uint8_t act_min_d1 = 30, uint8_t dea_h_d1 = 6, uint8_t dea_min_d1 = 30,
		uint8_t act_h_d2 = 20, uint8_t act_min_d2 = 30, uint8_t dea_h_d2 = 6, uint8_t dea_min_d2 = 30, uint8_t act_h_d3 = 20, uint8_t act_min_d3 = 30, uint8_t dea_h_d3 = 6, uint8_t dea_min_d3 = 30);
	String getLine(uint8_t line);
	uint8_t countLine();
	void split(String buffer);
};

class BlackoutControl {
public:
	static Database db; //Database object declaration. The Comunication object build the SdFile, Sd and Xbee too.
	static RTC rtc;
	static Hardware hard; // Hardware object declaration.
	BlackoutControl();
	void verify_substation_relay(void);
	void verify_phase_relay(void);
	void turnAllOff(void);
	void turnAllIn(void);
	void turnOneByOne(void);
	void turnIn(void);
	void turnOut(void);
};
#endif

