#ifndef DISPLAY_H
#define DISPLAY_H

#include "Defines.h"

#include <Arduino.h>
#include <Adafruit_GFX.h>

/// @brief This Display class is designed to be extended by other screen classes that define the methods to
/// perform the requesite activities according to the library in use to drive the physical screen. This allows all
/// physical screen methods to be consistent regardless of the library or driver in use, allowing this code to support
/// multiple different screen types without needing to have the main functions call different libraries/methods. Every
/// virtual method must be declared and defined in the class that extends this.
class Display {
public:
  /// @brief Constructor for a new Display instance
  /// @param rotation Rotate the screen if necessary
  /// @param textFont The identiy of the font for this display.
  /// @param textColour Default 16bit text colour, refer to TFT_eSPI documentation for details
  /// @param backgroundColour Fill the screen with this colour during setup
  Display(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                 uint16_t backgroundColour);

  /// @brief Virtual function to implement to setup the physical screen parameters
  
  void begin();

  /// @brief Virtual function to implement to clear the entire screen
  /// @param backgroundColour Valid colour to set the entire screen to
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

  /// @brief Get the physical screen height
  /// @return Screen height in pixels
  virtual uint16_t getHeight() = 0;

  /// @brief Get they physical screen width
  /// @return Screen width in pixels
  virtual uint16_t getWidth() = 0;

protected:
  uint8_t _fontHeight;            // Calculated height of the font to determine row count
  uint8_t _fontWidth;             // Calculated width of the font to determine row length
  uint16_t _textColour;
  uint16_t _backgroundColour;
  uint8_t _rotation = 0;
  uint8_t _textSize = 1;

};

#endif