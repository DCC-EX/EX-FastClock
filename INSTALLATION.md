# EX-FastClock

An Adjustable Speed Model Railway Fast Clock which integrates with the DCC-EX Command Station

## Github Repository

This repositry currently contains two branches:
1. Main.  This branch contains a ccopy of the code and ancilliary files on PlatformIO configuration.
2. Arduino IDE.  This branch contains the files in the necessary structure for use with the Ardiuino IDE


## Installation

### Libraries

The project requires three libraries - Adafruit_GFX, Adafruit_Touchscreen and MCUFRIEND_kbv.  All three can be installed from the Arduino IDE library manager or Platformio Library system as required however for compatability where possible use the copies supplied in the repositiory folder.

### Platformio

Select the Main branch from the repository and click on the CODE button.  Select Download ZIP file option.  Extract the files from the download and place the files in a folder within your Projects directory.

### Arduino IDE

Select the Arduino IDE branch from the repository and click on the CODE button.  Select Download ZIP file option.  Create a folder within your Arduino sketch folder called EX-Fast_Clock.  Copy the files EX-Fast_Clock.ino, EX-FastClock.h and config.h to this folder.  Copy the directories from the libraries folder into the Arduino libraries folder.


### Both Environments

I have  generated two special fonts for the project which can be found in the Fonts folder in the Adafruit GFX Library in this repository.  These should be copied into the fonts folder in the Adafruit_GFX library once installed. The file Arial9pt7b.h congtains a fullset of the Arial Font as used in Windows.  The file Arial48pt7b.h contains a large 48pt Arial font containing only charachters 0-9 and :.  This is used to display the time clock on the screen.  The full font was too large to fit into the Uno memory.


