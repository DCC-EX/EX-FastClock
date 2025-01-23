

#include "Clock.h"


Clock::Clock() {


}

void Clock::setup() {

}

void Clock::pauseClock() {
tft.setFont();

_pausePlay = !_pausePlay;

//Serial.print("PausePlay = ");
//Serial.println(pausePlay);

if (_pausePlay == true)                   //  Clock paused
      {
     // ******* move this to display
        showmsgXY(55, 160, 2, YELLOW, "PAUSED");
        tft.setFont();
        key[0].initButton(&tft,  40, 220, 70, 40, WHITE, GREEN, WHITE, "Start", 2);
        key[0].drawButton(false);
      }   

else  
    {
        tft.setFont();
        tft.fillRect(1, 135, 235, 30, BLACK);
        key[0].initButton(&tft,  40, 220, 70, 40, WHITE, CYAN, BLACK, "Pause", 2);
        key[0].drawButton(false);
    
        #ifdef SEND_VIA_SERIAL
          //SendTime(HH, MM, clockSpeed);
        #endif  
    }


}

void Clock::timeCheck() {
_HH = ((_startTime + _runTime) / _milPerHr) ;

    if (_HH >= 24) 
        {
          _HD = (_HH / 24);
          _HH = (_HH - (24 * HD)); 
        }     
 
        
      _MM = ((_startTime + _runTime) % _milPerHr) / _milPerMin;

    if (_MM > 59) 
        {
          _MH = (_MM / 60);
          _MM = (_MM - ( 60 * _MH)); 
        }

    message[0] = '0' + _HH/10;
    message[1] = '0' + _HH%10;
    message[2] = ':';
    message[3] = '0' + _MM/10;
    message[4] = '0' + _MM%10;
    message[5] = 0;


}

void Clock::resetAll() {
   if (!_pausePlay){
     pauseClock();
    }

    _startTime = 21600000;              //  default start time 06:00  
    _counter = 2;                       //  initial clock speed 4:1
    _runTime = 0;                       //  Reset run time
    _LastMinutes = 99;

    _clockSpeed = clockSpeeds[_counter];
    Display::displaySpeed(_clockSpeed);

    checkClockTime();           // display the time
  
}

void Clock::alterRate() {
  
    if (!_pausePlay){
     pauseClock();
    }

    if (c_ounter < 6)
    {
      _counter++;
    } else {
      _counter = 0;
    }
    Display::displaySpeed(_counter);

    _currentMillis = millis();

}

void Clock::adjustTime(byte OPT) {

if (!_pausePlay){
     pauseClock();
    }
          // if runTime is > 2 minutes (120000 millis) adjust runTime if under 2 minutes startTime
          //  Increment by 15 Min "a press"
        switch (OPT) {
          case 1:
            if (_runTime > 120000) {
              _runTime = _runTime + 900000;
            } else  {
              _startTime = _startTime + 900000;
            }
            break;
          case 2:
            if (_runTime > 120000)
              {
                _runTime = _runTime - 900000;
              } else  {
                _startTime = _startTime - 900000;
              }
            break;
          default:
            break;
        }
          
        timeCheck();
*****************************************
        printClock(message);

          #ifdef SEND_VIA_SERIAL
            //SendTime(HH, MM, clockSpeed);
          #endif  

}

void Clock::getSavedTime() {
    int eeAddress = 0;
    EEPROM.get(eeAddress, _PauseTime);

    // Check we have something valid from EEPROM
    if (_PauseTime.hour > 0 && _PauseTime.hour < 25){
      // we have a valid time so calculate start point
        _startTime = (_PauseTime.hour * _milPerHr) + (_PauseTime.minute * _milPerMin);
        _clockSpeed = _PauseTime.speed;
      }
    else {
      // not valid so set defaults.  Either first use or EEPROM corrupt
        _startTime = 21600000;           //  default start time 06:00
        _clockSpeed = 4;                 //  initial clock speed 4:1
    
    }

    _lastMillis = millis();          //  first reference reading of arduino O/S

}

void Clock::saveTime() {
  if (!_pausePlay){
     pauseClock();
    }
    _PauseTime.hour = _HH;
    _PauseTime.minute = _MM;
    _PauseTime.speed = _clockSpeed;

    int eeAddress = 0;
    EEPROM.put(eeAddress, _PauseTime);

    // Put this into Display code
    tft.fillRect(1, 135, 235, 30, BLACK);
    showmsgXY(55, 160, 2, YELLOW, "SAVED");


}
