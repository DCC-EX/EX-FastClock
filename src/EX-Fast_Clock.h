#include <Arduino.h>
#include <Adafruit_GFX.h>
//#include <MCUFRIEND_kbv.h>

//#include <TouchScreen.h>
#include <EEPROM.h>
#include "Clock.h"
#include "Display.h"

// include the specific clock configuration
#include "config.h"


#define MINPRESSURE 200
#define MAXPRESSURE 1000

#include <SPI.h>



// The following line governs the clock speeds available for selection
// Clockspeed of 1 = real time
// Clockspeed of 2 = half real time i.e. 1 min equiv. to 30 seconds
// Clockspeed of 4 = 1/4 real time i.e. 1 min equiv. to 15 seconds
// etc.
// These do not need to be changed but could be
byte clockSpeeds[] = {1, 2, 4, 6, 8, 12, 30};  //  Fast Clock Speeds

// The following line sets the default (startup) speed.

//byte clockSpeed = 4;               //  Initial Fast Clock Speed Setting







byte debounceDelay = 75;           //  the debounce time; increase if the output flickers




byte ButtonPressed = 0;

struct MyTime {
  byte hour;
  byte minute;
  byte speed;
};

MyTime PauseTime;
