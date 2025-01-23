#ifndef CLOCK_H
#define CLOCK_H


#include <Arduino.h>
#include <EEPROM.h>

class Clock {
public:
  Clock();
  void setup();
  void pauseClock();
  void timeCheck();
  void resetAll();
  void alterRate();
  void adjustTime(byte OPT);
  void getSavedTime();
  void saveTime();

private:

  unsigned long _currentMillis = 0;  //  Current Millis value for comparison
  unsigned long _lastMillis = 0;     //  Last Millis for comparison
  unsigned long _startTime = 0;      //  Milliseconds since 00:00.000 to Session Start Time
  unsigned long _runTime = 0;        //  Milliseconds since Session Start Time

  bool _pausePlay = false;            //  clock state - running or paused
  // Constants
  const int _milPerSec = 1000;       //  Milliseconds per Second
  unsigned long _milPerMin = 60000;  //  Milliseconds per minute
  unsigned long _milPerHr = 3600000; //  Milliseconds per Hour
  byte _clockSpeed;                  //  Fast Clock Speed Setting
  byte _counter                       //  array counter
  byte _HH;                           //  Integer Hours
  byte _MM;                           //  Integer Minutes
  byte _HD;                           //  number of full Days since conting
  byte _MH;                           //  number of full hours since conting
  byte _SM;                           //  number of full minutes since conting 

  byte _LastMinutes = 99;

  struct MyTime {
    byte hour;
    byte minute;
    byte speed;
  };
  MyTime _PauseTime;

};


#endif // CLOCK_H