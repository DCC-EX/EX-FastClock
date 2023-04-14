// Configuration file for EX-Fast_Clock
// Colin H Murdoch - February 2023
// This file comtains basic setting that comtrol how the FastClock operates.

// If we are sending data to the DCC-EX CS via I2C then we need to define an I2C Address
// and set a flag for inclusion. If not using I2C then comment out next two lines

//#define I2CAddress 0x55 // default I2C address
//#define SEND_VIA_I2C true

// If we are sending the data to the CS via Serial then uncomment the following line
#define SEND_VIA_SERIAL true


// Set this following string to the header you require.  This is displayed at the top of the screen
#define HDDR_SIZE  25
char header[HDDR_SIZE] = {"Nantyderry Junction"};


// ALL Touch panels and wiring is DIFFERENT.  The touch screen needs to be calibrated
// See the README files for how to run the calibration routine and
// copy-paste results from TouchScreen_Calibr_native.ino into the lines below.
// These settings are for the McuFriend 2.8" shield in Portrait tft.screenRotaion(0)

const byte XP = 7, XM = A1, YP = A2, YM = 6;
const int TS_LEFT=899,TS_RT=122,TS_TOP=100,TS_BOT=898;

