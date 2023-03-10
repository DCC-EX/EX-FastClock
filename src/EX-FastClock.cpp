
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


#include "EX-FastClock.h"
//#include "stdio.h"

// only load the wire library if we transmit to CS
#ifdef SEND_VIA_I2C
    #include <Wire.h>
#endif

MCUFRIEND_kbv tft;  // set up a tft instance with the MCUFRIEND drivers

// Load the special font for the clock display - 24 point wont load
// This is a converted Arial Truetype font with characters 0 - 9 & :
#include <Fonts/Arial48pt7b.h>
#include <Fonts/Arial9pt7b.h>

void showmsgXY(byte x, byte y, byte sz, char colour, const char *msg)
{
    tft.setFont();
    tft.setFont(&Arial9pt7b);
    tft.setCursor(x, y);
    tft.setTextColor(colour);
    tft.setTextSize(sz);
    tft.print(msg);
    delay(10);
}

void TFT_Begin()
{

    // ALL Touch panels and wiring is DIFFERENT
    // copy-paste results from TouchScreen_Calibr_native.ino

    const byte XP = 7, XM = A1, YP = A2, YM = 6;
  
    //const int TS_LEFT = 123, TS_RT = 923, TS_TOP = 895, TS_BOT = 98; // for Portrait orientation 
    

    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

    uint16_t ID = tft.readID();
    // Serial.print("TFT ID = 0x");
    // Serial.println(ID, HEX);
    // Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield

    tft.begin(ID);
  
    tft.setRotation(2);           //PORTRAIT

    tft.fillScreen(BLACK);
    showmsgXY(1, 15, 1, YELLOW, "Nantyderry Junction");
    tft.drawFastHLine(0, 18, tft.width(), WHITE);
  

}

void DrawButtons()
{

    tft.setFont();  // Set the default font

    //Serial.println("Defining Buttons");
    btn1.initButton(&tft,  40, 220, 70, 40, WHITE, GREEN, WHITE, "Start", 2);
    btn2.initButton(&tft,  120, 220, 70, 40, WHITE, RED, WHITE, "Save", 2);
    btn3.initButton(&tft,  200, 220, 70, 40, WHITE, CYAN, BLACK, "Reset", 2);
    btn4.initButton(&tft,  40, 270, 70, 40, WHITE, CYAN, BLACK, "T+", 2);
    btn5.initButton(&tft,  120, 270, 70, 40, WHITE, CYAN, BLACK, "T-", 2);
    btn6.initButton(&tft,  200, 270, 70, 40, WHITE, CYAN, BLACK, "Rate", 2); 

    btn1.drawButton(false);
    btn2.drawButton(false);
    btn3.drawButton(false);
    btn4.drawButton(false);
    btn5.drawButton(false);
    btn6.drawButton(false);
  
} 


void printClock(char *Msg)
{
    
    tft.setFont(&Arial48pt7b);
    
    tft.setTextColor(MAGENTA);
    tft.setTextSize(1);
    tft.fillRect(1, 30, 235, 90, BLACK);
    tft.setCursor(1,100);
    
    //Serial.print(" Time:");
    //Serial.println(Msg);

    tft.print(Msg);
    tft.drawFastHLine(0, 120, tft.width(), WHITE);

}

void printText(char *Msg)
{
    //Serial.println(Msg);

     tft.fillRect(1, 170, 318, 30, BLACK);
     tft.setCursor(15, 170);
    tft.setFont();
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.print(Msg);
    delay(10);
}

bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}


void CheckButtons()
{

    tft.setFont();

    bool down = Touch_getXY();

    btn1.press(down && btn1.contains(pixel_x, pixel_y));
    btn2.press(down && btn2.contains(pixel_x, pixel_y));
    btn3.press(down && btn3.contains(pixel_x, pixel_y));
    btn4.press(down && btn4.contains(pixel_x, pixel_y));
    btn5.press(down && btn5.contains(pixel_x, pixel_y));
    btn6.press(down && btn6.contains(pixel_x, pixel_y));
    
    if (btn1.justReleased()) 
        btn1.drawButton();
    if (btn2.justReleased()) 
        btn2.drawButton();
    if (btn3.justReleased()) 
        btn3.drawButton();  
    if (btn4.justReleased()) 
        btn4.drawButton();  
    if (btn5.justReleased()) 
        btn5.drawButton();  
    if (btn6.justReleased()) 
        btn6.drawButton();  
 
    if (btn1.justPressed()) {
      btn1.drawButton(true);
       ButtonPressed = 1;  // Start/Pause
      delay(debounceDelay);
    }
    if (btn2.justPressed()) {
      btn2.drawButton(true);
      ButtonPressed = 2; // Save
      delay(debounceDelay);
    }
    if (btn3.justPressed()) {
      btn3.drawButton(true);
      ButtonPressed = 3;   // Reset
      delay(debounceDelay);
    }
   if (btn4.justPressed()) {
      btn4.drawButton(true);
      ButtonPressed = 4;      //T+ 
      delay(debounceDelay);
    }
   if (btn5.justPressed()) {
      btn5.drawButton(true);
      ButtonPressed = 5;      //T-
      delay(debounceDelay);
    }
    if (btn6.justPressed()) {
      btn6.drawButton(true);
      ButtonPressed = 6;      // Rate
      delay(debounceDelay);
    }
  
  
}

#ifdef SEND_VIA_SERIAL
void SendTime(byte hour, byte mins, byte speed) {

  int itime = (hour * 60) + mins;
  //String buffer[20] = "<JC ", itime, " ", speed, ">\0";
  char buffer[20];
  sprintf(buffer, "<JC %d %d>", itime, speed);
  Serial.println(buffer);
}

#endif

void TimeCheck() {

  HH = ((startTime + runTime) / milPerHr) ;

    if (HH >= 24) 
        {
          HD = (HH / 24);
          HH = (HH - (24 * HD)); 
        }     
    if (HH <= 9)
        {
          Time = " ";
          Hour = "0";
          Hour.concat(HH);
          Hour += ":";
        }  
      else 
        {
          Hour = (HH);
          Hour += ":";
        }
     if ((HH >= 10) && (HH < 20)) 
        {
          Time = "  ";
        }
    if (HH >= 20) 
        {
          Time = " ";
        }
        
      MM = ((startTime + runTime) % milPerHr) / milPerMin;

    if (MM > 59) 
        {
          MH = (MM / 60);
          MM = (MM - ( 60 * MH)); 
        }

    if (MM <= 9)
        {
          Minute = "0";
          Minute.concat(MM);
          MinuteS = (Minute);
          Minute += ":";
        }  
    else 
        {
          Minute = (MM);
          MinuteS = (Minute);
          Minute += ":";
        }

    // Ss = ((startTime + runTime) % milPerHr) / milPerSec;

    // if (Ss > 59) 
    //     {
    //       SM = (Ss / 60);
    //       Ss = (Ss - ( 60 * SM)); 
    //     }
      
    // if (Ss <= 9)
    //     {
    //       Second = "0";
    //       Second.concat(Ss);
    //     }  
    //   else 
    //     {
    //       Second = (Ss);
    //     }   

    Time = Time += Hour += MinuteS += '\0';  //  Add null for dispaly
    //TimeP = Hour += Minute += Second;  
    Time.toCharArray(message, 8);

}

void CheckClockTime() {

//Serial.println("Clock Tick");

  if (currentMillis - lastMillis >= milPerSec) {  // cycle every second  
  
    runTime = runTime + (clockSpeed * milPerSec);
      
    TimeCheck();
    
  lastMillis = currentMillis;
  //Serial.print("Routine Cycle ");
  //Serial.println(message);

  if (MM != LastMinutes){
    LastMinutes = MM;

    printClock(message);  

    #ifdef SEND_VIA_SERIAL
      SendTime(HH, MM, clockSpeed);
    #endif  
  }
  
  }

}

void PauseClock() {

tft.setFont();

pausePlay = !pausePlay;

//Serial.print("PausePlay = ");
//Serial.println(pausePlay);

if (pausePlay == true)                   //  Clock paused
      {
        Pause = "Pause";
        Pause = Pause += '\0';
        Pause.toCharArray(message, 6);
        showmsgXY(55, 160, 2, YELLOW, "PAUSED");
        tft.setFont();
        btn1.initButton(&tft,  40, 220, 70, 40, WHITE, GREEN, WHITE, "Start", 2);
        btn1.drawButton(false);
      }   

else  
    {
        tft.setFont();
        tft.fillRect(1, 135, 235, 30, BLACK);
        btn1.initButton(&tft,  40, 220, 70, 40, WHITE, CYAN, BLACK, "Pause", 2);
        btn1.drawButton(false);
    
        #ifdef SEND_VIA_SERIAL
          //SendTime(HH, MM, clockSpeed);
        #endif  
    }

}

void TimePlus(){

   if (!pausePlay){
     PauseClock();
    }
          // if runTime is > 2 minutes (120000 millis) adjust runTime if under 2 minutes startTime
          //  Increment by 15 Min "a press"
        if (runTime > 120000)
        {
          runTime = runTime + 900000;
        } else  {
          startTime = startTime + 900000;
        }
    
        TimeCheck();


          printClock(message);

          #ifdef SEND_VIA_SERIAL
            //SendTime(HH, MM, clockSpeed);
          #endif  

}

void TimeMinus(){

  if (!pausePlay){
     PauseClock();
    }
  // if runTime is > 2 minutes (120000 millis) adjust runTime if under 2 minutes startTime
  //  Increment by -15 Min "a press"
  if (runTime > 120000)
  {
    runTime = runTime - 900000;
  } else  {
    startTime = startTime - 900000;
  }
          
    TimeCheck();

    printClock(message);

    #ifdef SEND_VIA_SERIAL
      //SendTime(HH, MM, clockSpeed);
    #endif        

}

void AlterRate(){

    if (!pausePlay){
     PauseClock();
    }

    //Serial.println(counter);
    if (counter < 6)
    {
      counter++;
    } else {
      counter = 0;
    }

    //Serial.println(counter);
    clockSpeed = clockSpeeds[counter];
    Speed = "Speed = ";
    Speed = Speed +=clockSpeed += '\0';    //  Add null for dispaly
    Speed.toCharArray(message, 12);
    tft.fillRect(10, 170, 240, 22, BLACK);
    showmsgXY(10, 190, 1, YELLOW, message);
         
    currentMillis = millis();

}


void ResetAll(){

    if (!pausePlay){
     PauseClock();
    }

    startTime = 21600000;              //  default start time 06:00  
    counter = 2;                       //  initial clock speed 4:1
    runTime = 0;                       //  Reset run time
    LastMinutes = 99;

    clockSpeed = clockSpeeds[counter];
    Speed = "Speed = ";
    Speed = Speed +=clockSpeed += '\0';    //  Add null for dispaly
    Speed.toCharArray(message, 12);
    
    tft.fillRect(10, 170, 240, 22, BLACK);
    showmsgXY(10, 190, 1, YELLOW, message);

    CheckClockTime();           // display the time
  

}

void SaveTime(){

    if (!pausePlay){
     PauseClock();
    }

    PauseTime.hour = HH;
    PauseTime.minute = MM;
    PauseTime.speed = counter;

    int eeAddress = 0;

    EEPROM.put(eeAddress, PauseTime);
    tft.fillRect(1, 135, 235, 30, BLACK);
    showmsgXY(55, 160, 2, YELLOW, "SAVED");

}

void GetSavedTime(){

    int eeAddress = 0;
    EEPROM.get(eeAddress, PauseTime);

    // Check we have something valid from EEPROM
    if (PauseTime.hour > 0 && PauseTime.hour < 25){
      // we have a valid time so calculate start point
        startTime = (PauseTime.hour * milPerHr) + (PauseTime.minute * milPerMin);
        counter = PauseTime.speed;
      }
    else {
      // not valid so set defaults.  Either first use or EEPROM corrupt
        startTime = 21600000;           //  default start time 06:00
        clockSpeed = 4;                 //  initial clock speed 4:1
    
    }

    lastMillis = millis();          //  first reference reading of arduino O/S

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

  clockSpeed = clockSpeeds[counter];
          Speed = "Speed = ";
          Speed = Speed +=clockSpeed += '\0';    //  Add null for dispaly
          Speed.toCharArray(message, 12);
          //printText(message);
          tft.fillRect(10, 170, 240, 22, BLACK);
          showmsgXY(10, 190, 1, YELLOW, message);

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
        TimePlus();
        PrintButton();
      break;

    case 5:
        TimeMinus();
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



