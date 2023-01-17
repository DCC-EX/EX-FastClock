# DRAFT

# This document is in the process of being updated


# EX-FastClock

An Adjustable Speed Model Railway Fast Clock which integrates with the DCC-EX Command Station



## Background

This project is based on a project originally written by Jim Gifford (Hallet Cove Southern) in June 2017.  This project used a 32 x 8 LED matrix to display the time and was controlled by a number of pushbuttons.
[See Jim's Original Project here.](https://www.hallettcovesouthern.com/track-plan-design-info/arduino-projects/fast-clock/)

I felt that this project was ripe for an update and decided to convert Jim's code to operate using a cheap TFT/LCD touch screen to run on my own layout. This project is the result.  Much of the code has been rewritten into smaller functions with additional features added, but the time clock calculations are the originals.

This project has now been extended to add the capability of integrating the clock to the DCC-EX 
Command Station and more specifically the EXRAIL automation feature which now allows time based 
control. This feature is optional and can be controlled by the config.h file.

## Hardware

The project uses only two components:
1.  A standard arduino or compatable clone.
2.  A 2.8" MCUFRIEND style TFT-LCD plug-in shield.

The completed project is shown in the accompanying photograph:


![TFT Fast Clock](/images/IMG_2502.jpg)

The FastClock communicates with the Command Station using I2C.  Given that the MCUFREIND style shield is a shield and uses/images/IMG_2502.jpg the A4 pin as LCD_RST it is necessary to make a modification to enable the I2C communication.  This involces cutting the A4 pin and soldering a jumper from LCD_RST on the backof the TFT board to the pin that aligns with the UNO RST pin.

![Modified LCD Sheild](/images/IMG_3538.jpg)

This modification allow the A4 & A5 to operate correctly as I2C and was suggested by David Prentice who wrote the MCUFRIEND.kbv library thatthis project uses.  A discussion on this modification can be found [here](https://forum.arduino.cc/t/mcufriend-kbv-library-for-uno-2-4-2-8-3-5-3-6-3-95-inch-mcufriend-shields/353100/100).

## Operation

At startup the clock will calculate a start time based on either a) a coded start time (currently 6:00 a.m.) or b) a run time stored in the EEPROM (see item 2) below.

The clock will start in a paused state and will display the speed rate factor (default = x 4).  Once any adjustemts have been made the clock can be started.  The usage of the six buttons are as below:

1. **Start** - Pressing this button will start the clock and the button text will change to **Pause**.  
2. **Save** - Pressing this button will pause the clock and save the current time and Speed Factor to the EEPROM.  These figures will be used to initialise the clock on nextstartup.
3. **Reset** - Pressing this button will pause the clock and set the time to 06:00 with a speed factor of 4.
4. **T+** - Pressing this key will pause the clock and add 15 minutes to the time.
5. **T-** - Pressing this key will pause the clock and deduct 15 minutes from the time.
6. **Rate** - Pressing this key will increase the speed factor to the next level.  The speed factor will cycle around the seven speed settings of 1, 2, 4, 6,, 8, 12 & 30.


## Installation Notes

The project requires three libraries - Adafruit_GFX, Adafruit_Touchscreen and MCUFRIEND_kbv.  All three cn be installed from the Arduino IDE library manager.

I have also generated two special fonts for the project which can be found in the Fonts folder in this repository.  These should be copied into the fonts folder in the Adafruit_GFX library once installed. The file Arial9pt7b.h congtains a fullset of the Arial Font as used in Windows.  The file Arial48pt7b.h contains a large 48pt Arial font containing only charachters 0-9 and :.  This is used to display the time clock on the screen.  The full font was too large to fit into the Uno memory.

## Configuration Notes

The FastClock can either operate standalone of in communication mode being polled by the Command Station.  To operate in standalone mode edit the file config.h and comment out the following two lines:
#define I2CAddress 0x55 // default I2C address
#define SEND_TO_CS true
The compilation will then exclude the code relating to the use of the Wire library.

The operating speeds of the clock can be controlled by modifying the following line:
byte clockSpeeds[] = {1, 2, 4, 6, 8, 12, 30};  //  Fast Clock Speeds
See the notes in the config.h file.

Finally the default speed of the clock at startup is controlled by the line:
byte clockSpeed = 4;  
which may be modified as required but must correspond to one of the clockspeeds in the array defined above.


