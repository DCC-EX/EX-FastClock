#include "Arduino.h"
#include "Display.h"



Display::Display(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                 uint16_t backgroundColour) {
  _rotation = rotation;
  _textSize = 1; // default text size to save amending display routine.
  _textColour = textColour;
  _backgroundColour = backgroundColour; 



  void begin();


  void clearScreen(uint16_t backgroundColour);

  void drawButtons();
  void printClock(char *Msg);
  void printText(char *Msg);
  void displaySpeed(byte clockSpeed);
  void showmsgXY(byte x, byte y, byte sz, char colour, char *msg);
  void checkButtons();
  void setCursor(int row, int col);


  //virtual uint16_t getHeight() = 0;
  //virtual uint16_t getWidth() = 0;

protected:
  uint8_t _fontHeight;            // Calculated height of the font to determine row count
  uint8_t _fontWidth;             // Calculated width of the font to determine row length

};