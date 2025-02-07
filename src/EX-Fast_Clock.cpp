
/*
 * Fast Clock Version 3.0
 * Colin H Murdoch - December 2022
 * 
 * Modified December 2022
 * Amended to operate in conjuction with DCC-EX and pass clock time values over I2C
 * to allow time based operation of EXRAIL commands.
 * 
 * Based on the original Written by Jim Gifford June 2017
 * COPYRIGHT © 2017 Jim Gifford
 * http://www.hallettcovesouthern.com/ - The website for my Layout
 * http://halletcovesouthern.blogspot.com.au - The Construction & Activities Blog
 * 
 * Provided under a Creative Commons Attribution, Non-Commercial Share Alike,3.0 Unported License
 *
 * This version modified by Colin H Murdoch - March 2022
 * Modified to operate on an Arduino Uno with an McuFriend type TFT LCD Shield.
 *
 * Design Notes:
 *
 * This code is designed to use the Arduino Uno R3 with a 2.8" plug in shield TFT display.
 * On initialisation the clock is paused ready to set the start time. The start time can be adjusted
 * up and/or from the 06:00 preset with a preset fast clock ratio of 4:1.  The fast clock ratio can
 * be adjusted to 1, 2, 4, 6, 8, 12 or 30.  A reset function has been included. When ready to commence
 * operation the start/pause button is pressed.  the oroginal buttons have been replaced with on-screen buttons
 * set up using the Adafruit_GFX graphics library.
 * 
 * The system can now use the EEPROM to hold the time value.  If Button 2 (Save) is prwssed, the clock is halted 
 * and the values are saved to EEPROM.  on restart the clock loads up this time.  This can be overwritten
 * * with the Reset button.
 * 
 * On screen buttons.
 * 
 * Button 1   - Start/Pause
 * Button 2   - Save
 * Button 3   - Reset
 * Button 4   - +Time
 * Button 5   - -Time
 * Button 6   - Reset
 *
 * 
 */


#include "EX-Fast_Clock.h"
//#include "stdio.h"

// only load the wire library if we transmit to CS
#ifdef SEND_VIA_I2C
    #include <Wire.h>
#endif


#ifdef SEND_VIA_SERIAL
void SendTime(byte hour, byte mins, byte speed) {

  int itime = (hour * 60) + mins;
  Serial.print(F("<JC "));
  Serial.print( itime);
  Serial.print(F(" "));
  Serial.print((int)speed);
  Serial.print(F(">\n"));

}

#endif


void CheckClockTime() {

//Serial.println("Clock Tick");

  if (currentMillis - lastMillis >= milPerSec) {  // cycle every second  
  
    runTime = runTime + (clockSpeed * milPerSec);
      
    Clock.TimeCheck();
    
  lastMillis = currentMillis;

  if (MM != LastMinutes){
    LastMinutes = MM;

    printClock(message);  

    #ifdef SEND_VIA_SERIAL
      SendTime(HH, MM, clockSpeed);
    #endif  
  }
  
  }

}




void PrintButton(){

  //Serial.print("Button :");
  //Serial.println(ButtonPressed);

}

#ifdef SEND_VIA_I2C
void TransmitTime() {
        // send the data over I2C
        // send the time as <mmmm> as two bytes followed by clockspeed
        int timetosend = (HH * 60) + MM;
        byte TimeArray[2];
      
        TimeArray[0] = (timetosend >> 8);
        TimeArray[1] = timetosend & 0xFF;
        Wire.write(TimeArray, 2);
        
        Wire.write(clockSpeed);
        
}
#endif



void setup() 
{

  #ifdef SEND_VIA_SERIAL
    Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
  #endif

  #ifdef SEND_VIA_I2C       // only start the wire library if we transmit to CS
    //Serial.print("Starting Wire Library at address : ");
    //Serial.println(I2CAddress);
    Wire.begin(I2CAddress);
    Wire.onRequest(TransmitTime);
  #endif

  currentMillis = millis();

  TFT_Begin();
    
  DrawButtons();
 
  GetSavedTime();               // Read the EEPROM

  displaySpeed(counter);

  CheckClockTime();

  pausePlay = true;
  showmsgXY(50, 160, 2, YELLOW, "PAUSED");

  //Serial.println("Setup Finished");

}




void loop() 
{
  
  if (pausePlay == false){
    CheckClockTime();
  }

  CheckButtons();

  

  switch (ButtonPressed){
      
    

    case 1:
        PauseClock();
        PrintButton();

      break;
        
    case 2:
        SaveTime();
        PrintButton();
      break;

    case 3:
        
        ResetAll();
        PrintButton();
      break;

    case 4:
        AdjustTime(1); // add time
        PrintButton();
      break;

    case 5:
        AdjustTime(2); // deduct time
        PrintButton();
      break;

    case 6:
        AlterRate();
        PrintButton();
      break;

  }
    
    ButtonPressed = 0;
    currentMillis = millis();


}



