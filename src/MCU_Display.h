#ifndef MCU_DISPLAY_H
#define MCU_DISPLAY_H

#include "Defines.h"
#include "Display.h"
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <EX-Fast_Clock.h>


#define MINPRESSURE 200
#define MAXPRESSURE 1000

MCUFRIEND_kbv *_tft;  // set up a tft instance with the MCUFRIEND drivers
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Define the operating buttons
//Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5, btn6;
Adafruit_GFX_Button key[6];

int pixel_x, pixel_y;     //Touch_getXY() updates global vars

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  15
char message[BUF_SIZE] = {"Hello!"};



class MCU_Display : public Display {
public:
  /// @brief Constructor for a MCUFREIND Display instance
  /// @param rotation Rotation of the display, 0 - 3, refer to TFT_eSPI documentation for details
  /// @param textFont The identiy of the font for this display.
  /// @param textColour Default 16bit text colour, refer to TFT_eSPI documentation for details
  /// @param backgroundColour Default 16bit background colour, refer to TFT_eSPI documentation for details
  MCU_Display(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                 uint16_t backgroundColour);

  /// @brief Destructor for the display
  ~MCU_Display();

  /// @brief Perform any initial setup required
  void begin();

  /// @brief Clear the entire screen
  void clearScreen(uint16_t backgroundColour);
  
  void drawButtons();
  void printClock(char *Msg);
  void printText(char *Msg);
  void displaySpeed(byte clockSpeed);


  /// @brief Show a message at a specific x,y location
  /// @param x horizontal position
  /// @param y vertival position
  /// @param sz text size
  /// @param colour the colour code
  /// @param msg the message to be displayed
  void showmsgXY(byte x, byte y, byte sz, char colour, char *msg);
  void checkButtons();
  void setCursor(int row, int col);

private:

  bool touchGetXY(void);

  static MCUFRIEND_kbv *_tft;
  const GFXfont *_gfxFont;
  static bool _tftInitialised;

};

#endif // MCU_DISPLAY_H