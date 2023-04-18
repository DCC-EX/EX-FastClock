
# EX-FastClock

An Adjustable Speed Model Railway Fast Clock which integrates with the DCC-EX Command Station



## Background

This project is based on a project originally written by Jim Gifford (Hallet Cove Southern) in June 2017.  His project used a 32 x 8 LED matrix to display the time and was controlled by a number of pushbuttons.
[See Jim's Original Project here.](https://www.hallettcovesouthern.com/track-plan-design-info/arduino-projects/fast-clock/)

I felt that this project was ripe for an update and decided to convert Jim's code to operate using a cheap TFT/LCD touch screen to run on my own layout. This project is the result.  Much of the code has been rewritten into smaller functions with additional features added, but the time clock calculations are the originals.

This project has now been extended to add the capability of integrating the clock to the DCC-EX 
Command Station and more specifically the EXRAIL automation feature which now allows time based 
control. This feature is optional and can be controlled by the config.h file.

In order to fit the code comfortablly into the available RAM on a arduino the code has now been significantly updated from that written by Jim Gifford.

## Hardware

The project uses only two components:
1.  A standard arduino or compatable clone.
2.  A 2.8" MCUFRIEND style TFT-LCD plug-in shield.

The completed project is shown in the accompanying photograph:


![TFT Fast Clock](/images/IMG_2502.jpg)

The FastClock communicates with the Command Station using either I2C or Serial.  

Given that the MCUFREIND style shield is a shield and uses the A4 pin as LCD_RST it is necessary to make a modification to enable the I2C communication.  This involces cutting the A4 pin and soldering a jumper from LCD_RST on the backof the TFT board to the pin that aligns with the UNO RST pin.  However if one is intending to configure the clock as a serial device then this modification is not required.

![Modified LCD Sheild](/images/IMG_3538.jpg)

This modification allow the A4 & A5 to operate correctly as I2C and was suggested by David Prentice who wrote the MCUFRIEND.kbv library that this project uses.  A discussion on this modification can be found [here](https://forum.arduino.cc/t/mcufriend-kbv-library-for-uno-2-4-2-8-3-5-3-6-3-95-inch-mcufriend-shields/353100/100).

If using Serial communication no modification is required. Pins 0 & 1 (TX/RX) are unused on the LCD PCB therefore wires may be soldered to the Arduino PCB to run to Serial connections on the CS.



## Installation Notes

The MCUFRIEND style shield used in this project is usually a cheap(ish) import from China.  These come with a variety of processor chips and various tolerances on the touch screen.  As such before use it is necessary to carry out a calibration routine.  Details of how to carry this out are provided [here](CALIBRATION.mdC:/Users/Colin/Documents/ADevCode/GitHub/EX-FastClock/EX-FastClock/README.md).

Once the calibration has been carried out plug the shield into the UNO and you are ready to install the software.  If you need assistance see the instructions [here](INSTALLATION.md).


## Configuration Notes

The FastClock can either operate in one of three modes:

* Standalone
* Serial Communication with the CS
* I2C Communication with the CS.

To indicate which mode is in use it is necessary to edit the config.h file.


1. Standalone use.
	The config.h file comes pre-configured to use the clock in standalone mode.  No changes are necessary.
<br>
2. Serial Mode.
	To communicatein Serial mode it is necessary to edit the config.h file and uncomment the following line:

		`//#define SEND_VIA_SERIAL true`

	This will load the appropriate code including the Wire library.
<br>
3. I2C mode
	To operate in I2C mode edit the config.h file and uncomment the following lines:

	`//#define I2CAddress 0x55 // default I2C address`
	`//#define SEND_VIA_I2C true`

	In this mode the CS will poll the FastClock to obtain the time.  It is necessary to set the same I2C address here as used in the myHal.cpp file within the CS.  This is set to a default of 0x55 (decimal 85) but can be set to some other value if this conflicts with othere I2C devices on your setup.
<br>
4. By default the top of the clock screen displays the name of my own layout.  To inset your layout name then change the following line.

	`char header[HDDR_SIZE] = {"Nantyderry Junction"};`

<br>
5. Finally insert the output of the touchscreen configuration program into the file in place of the following two lines.


	`const byte XP = 7, XM = A1, YP = A2, YM = 6;`
	`const int TS_LEFT=899,TS_RT=122,TS_TOP=100,TS_BOT=898;`


## Operation

At startup the clock will calculate a start time based on either a) a coded start time (currently 6:00 a.m.) or b) a run time stored in the EEPROM (see item 2) below.

The clock will start in a paused state and will display the speed rate factor (default = x 4).  Once any adjustemts have been made the clock can be started.  The usage of the six buttons are as below:

1. **Start** - Pressing this button will start the clock and the button text will change to **Pause**.  
2. **Save** - Pressing this button will pause the clock and save the current time and Speed Factor to the EEPROM.  These figures will be used to initialise the clock on nextstartup.
3. **Reset** - Pressing this button will pause the clock and set the time to 06:00 with a speed factor of 4.
4. **T+** - Pressing this key will pause the clock and add 15 minutes to the time.
5. **T-** - Pressing this key will pause the clock and deduct 15 minutes from the time.
6. **Rate** - Pressing this key will increase the speed factor to the next level.  The speed factor will cycle around the seven speed settings of 1, 2, 4, 6,, 8, 12 & 30.

In Serial Mode, at startup the initial clock time will be sent to the Command Station but when in a paused state no further time commands are sent until the START buttoon is pressed.

In I2C mode the Command Station polls the FastClock at intervals.

