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

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
//These settings are for the McuFriend 2.8" shield

const byte XP = 7, XM = A1, YP = A2, YM = 6;

//const int TS_LEFT = 99, TS_RT = 895, TS_TOP = 122, TS_BOT = 918;  // For Landscape Orientation
const int TS_LEFT = 123, TS_RT = 923, TS_TOP = 895, TS_BOT = 98; // for Portrait orientation 2

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Define the operating buttons
Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5, btn6;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars


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
//bool newMessageAvailable = true;


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
byte Ss;                           //  Integer Seconds 
String Time;                      //  Character Hours:Minutes
String TimeP;                     //  Character Hours:Minutes:Seconds
String Hour;                      //  Character Hours
String Minute;                    //  Character Minutes + ":"
String MinuteS;                   //  Character Minutes
String Second;                    //  Character Seconds
String Speed;                     //  Character Speed
String Pause;                     //  Character Pause
byte LastMinutes = 99;

byte ButtonPressed = 0;

struct MyTime {
  byte hour;
  byte minute;
  byte speed;
};

MyTime PauseTime;
