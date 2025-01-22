

class Display {
public:
  /// @brief Constructor for a new Display instance
  Display();


  void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour);


  void clearScreen(uint16_t backgroundColour);


  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message, bool underlined) = 0;


  virtual uint16_t getHeight() = 0;


  virtual uint16_t getWidth() = 0;

protected:
  uint8_t _fontHeight;            // Calculated height of the font to determine row count
  uint8_t _fontWidth;             // Calculated width of the font to determine row length

};