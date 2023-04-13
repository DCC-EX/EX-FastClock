

// If we are sending data to the DCC-EX CS via I2C then we need to define an I2C Address
// and set a flag for inclusion. If not using I2C then comment out next two lines

//#define I2CAddress 0x55 // default I2C address
//#define SEND_VIA_I2C true

// If we are sending the data to the CS via Serial then uncomment the following line
#define SEND_VIA_SERIAL true

// The following line governs the clock speeds availavle for selection
// Clockspeed of 1 = real time
// Clockspeed of 2 = half real time i.e. 1 min equiv. to 30 seconds
// Clockspeed of 4 = 1/4 real time i.e. 1 min equiv. to 15 seconds
// etc.

byte clockSpeeds[] = {1, 2, 4, 6, 8, 12, 30};  //  Fast Clock Speeds

// The following line sets the default (startup) speed.

byte clockSpeed = 4;               //  Initial Fast Clock Speed Setting



// Set this header to the title you wish to see
#define HDDR_SIZE  25
char header[HDDR_SIZE] = {"Nantyderry Junction!"};

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
// These settings are for the McuFriend 2.8" shield in Portrait tft.screenRotaion(2)

const byte XP = 7, XM = A1, YP = A2, YM = 6;

const int TS_LEFT = 123, TS_RT = 923, TS_TOP = 895, TS_BOT = 98; // for Portrait orientation 2

