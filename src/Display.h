#ifndef DISPLAY_H
#define DISPLAY_H

#include "Defines.h"
#include "Display.h"
#include <Arduino.h>

/// @brief This Display class is designed to be extended by other screen classes that define the methods to
/// perform the requesite activities according to the library in use to drive the physical screen. This allows all
/// physical screen methods to be consistent regardless of the library or driver in use, allowing this code to support
/// multiple different screen types without needing to have the main functions call different libraries/methods. Every
/// virtual method must be declared and defined in the class that extends this.
class Display {
public:
  /// @brief Constructor for a new Display instance
  Display();

  /// @brief Virtual function to implement to setup the physical screen parameters
  /// @param rotation Rotate the screen if necessary
  /// @param textSize Pixel multiplier to increase text size if desired
  /// @param backgroundColour Fill the screen with this colour during setup
  void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour);

  /// @brief Virtual function to implement to clear the entire screen
  /// @param backgroundColour Valid colour to set the entire screen to
  void clearScreen(uint16_t backgroundColour);

  /// @brief Virtual function to implement to write a row of text to the physical screen
  /// @param row Row on screen, 0 - 255 (not pixels)
  /// @param column Column on screen, 0 - 255 (not pixels)
  /// @param fontColour Valid colour for the text
  /// @param backgroundColour Valid colour for the background
  /// @param maxLength Maximum number of columns (not pixels) that can fit on the screen
  /// @param message Char array containing the text to display
  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message, bool underlined) = 0;

  /// @brief Get the physical screen height
  /// @return Screen height in pixels
  virtual uint16_t getHeight() = 0;

  /// @brief Get they physical screen width
  /// @return Screen width in pixels
  virtual uint16_t getWidth() = 0;

protected:
  uint8_t _fontHeight;            // Calculated height of the font to determine row count
  uint8_t _fontWidth;             // Calculated width of the font to determine row length

};

#endif