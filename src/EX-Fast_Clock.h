#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

#include <TouchScreen.h>
#include <EEPROM.h>

// include the specific clock configuration
#include "config.h"


#define MINPRESSURE 200
#define MAXPRESSURE 1000

#include <SPI.h>


// Define the operating buttons
//Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5, btn6;
Adafruit_GFX_Button key[6];

int pixel_x, pixel_y;     //Touch_getXY() updates global vars

// The following line governs the clock speeds available for selection
// Clockspeed of 1 = real time
// Clockspeed of 2 = half real time i.e. 1 min equiv. to 30 seconds
// Clockspeed of 4 = 1/4 real time i.e. 1 min equiv. to 15 seconds
// etc.
// These do not need to be changed but could be
byte clockSpeeds[] = {1, 2, 4, 6, 8, 12, 30};  //  Fast Clock Speeds

// The following line sets the default (startup) speed.

byte clockSpeed = 4;               //  Initial Fast Clock Speed Setting

// Define some colours for the display

#define BLACK   0x0000
//#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  15
char message[BUF_SIZE] = {"Hello!"};


unsigned long currentMillis = 0;  //  Current Millis value for comparison
unsigned long lastMillis = 0;     //  Last Millis for comparison
unsigned long startTime = 0;      //  Milliseconds since 00:00.000 to Session Start Time
unsigned long runTime = 0;        //  Milliseconds since Session Start Time

// Constants
const int milPerSec = 1000;       //  Milliseconds per Second
unsigned long milPerMin = 60000;  //  Milliseconds per minute
unsigned long milPerHr = 3600000; //  Milliseconds per Hour


byte debounceDelay = 75;           //  the debounce time; increase if the output flickers
byte counter = 2;                  //  for program logic
bool pausePlay = false;            //  clock state - running or paused

byte HH;                           //  Integer Hours
byte MM;                           //  Integer Minutes
byte HD;                           //  number of full Days since conting
byte MH;                           //  number of full hours since conting
byte SM;                           //  number of full minutes since conting 

byte LastMinutes = 99;

byte ButtonPressed = 0;

struct MyTime {
  byte hour;
  byte minute;
  byte speed;
};

MyTime PauseTime;
