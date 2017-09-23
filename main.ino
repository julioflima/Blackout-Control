//libraries
#include "LiquidCrystal.h"
#include "TimerOne.h"

//declaration lamps
const int LAMP_1 = 2;
const int LAMP_2 = 3;
const int LAMP_3 = 4;
const int LAMP_4 = 5;
const int LAMP_5 = 6;
const int LAMP_6 = 7;
const int LAMP_7 = 8;
const int LAMP_8 = 13;
const int LAMP_9 = 12;
const int LAMP_10 = 11;
const int LAMP_11 = 10;
const int LAMP_12 = 9;

//declaration lcd
const int RS = 18;
const int E = 19;
const int D4 = 17;
const int D5 = 15;
const int D6 = 16;
const int D7 = 0;

//declaration keyboard
const int key = 14;

//declaration parameters of time running and flag one
int  prtime_1 = 0;
int  prtime_2 = 0;
int  prtime_3 = 0;
int  prtime_4 = 0;
int  prtime_5 = 0;
int  prtime_6 = 0;
int  prtime_7 = 0;
int  prtime_8 = 0;
int  prtime_9 = 0;
int  prtime_10 = 0;
int  prtime_11 = 0;
int  prtime_12 = 0;

//declaration parameters of time stoped
int  pstime_1 = 0;
int  pstime_2 = 0;
int  pstime_3 = 0;
int  pstime_4 = 0;
int  pstime_5 = 0;
int  pstime_6 = 0;
int  pstime_7 = 0;
int  pstime_8 = 0;
int  pstime_9 = 0;
int  pstime_10 = 0;
int  pstime_11 = 0;
int  pstime_12 = 0;

//declaration flutuations of time running
unsigned long int  rtime_1 = 0;
unsigned long int  rtime_2 = 0;
unsigned long int  rtime_3 = 0;
unsigned long int  rtime_4 = 0;
unsigned long int  rtime_5 = 0;
unsigned long int  rtime_6 = 0;
unsigned long int  rtime_7 = 0;
unsigned long int  rtime_8 = 0;
unsigned long int  rtime_9 = 0;
unsigned long int  rtime_10 = 0;
unsigned long int  rtime_11 = 0;
unsigned long int  rtime_12 = 0;

//declaration flutuations of time stoped
unsigned long int  stime_1 = 0;
unsigned long int  stime_2 = 0;
unsigned long int  stime_3 = 0;
unsigned long int  stime_4 = 0;
unsigned long int  stime_5 = 0;
unsigned long int  stime_6 = 0;
unsigned long int  stime_7 = 0;
unsigned long int  stime_8 = 0;
unsigned long int  stime_9 = 0;
unsigned long int  stime_10 = 0;
unsigned long int  stime_11 = 0;
unsigned long int  stime_12 = 0;

//declarations globals
int tecla = 13;
bool on_off = 0;
int c = 0;
int lido = 0;
int maior = 0, menor = 0, media, amostras = 500;
