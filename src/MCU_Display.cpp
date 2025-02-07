

#include "MCU_Display.h"



// Load the special font for the clock display - 24 point wont load
// This is a converted Arial Truetype font with characters 0 - 9 & :
#include <Fonts/Arial48pt7b.h>
#include <Fonts/Arial9pt7b.h>




MCU_Display::MCU_Display(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                 uint16_t backgroundColour) {

}

void MCU_Display::begin()
{

    uint16_t ID = tft.readID();
    // Serial.print("TFT ID = 0x");
    // Serial.println(ID, HEX);
    // Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield

    tft.begin(ID);
  
    tft.setRotation(0);           //PORTRAIT

    tft.fillScreen(BLACK);
    showmsgXY(1, 15, 1, YELLOW, header);
    tft.drawFastHLine(0, 18, tft.width(), WHITE);
  

}

void MCU_Display::clearScreen()
{
    tft.fillScreen(BLACK);
}



void MCU_Display::drawButtons()
{

    tft.setFont();  // Set the default font

    //Serial.println("Defining Buttons");
    key[0].initButton(&tft,  40, 220, 70, 40, WHITE, GREEN, WHITE, "Start", 2);
    
    key[1].initButton(&tft,  120, 220, 70, 40, WHITE, RED, WHITE, "Save", 2);
    
    key[2].initButton(&tft,  200, 220, 70, 40, WHITE, CYAN, BLACK, "Reset", 2);
    
    key[3].initButton(&tft,  40, 270, 70, 40, WHITE, CYAN, BLACK, "T+", 2);
    
    key[4].initButton(&tft,  120, 270, 70, 40, WHITE, CYAN, BLACK, "T-", 2);
    
    key[5].initButton(&tft,  200, 270, 70, 40, WHITE, CYAN, BLACK, "Rate", 2); 
    

    for (byte x = 0; x < 6; x++) {
      key[x].drawButton(false);
      delay(10);    // Seem to need a slight pause
    }
  
} 


void MCU_Display::printClock(char *Msg)
{
    
    tft.setFont(&Arial48pt7b);
    
    tft.setTextColor(MAGENTA);
    tft.setTextSize(1);
    tft.fillRect(1, 30, 235, 90, BLACK);
    tft.setCursor(1,100);
    
    tft.print(Msg);
    
    tft.drawFastHLine(0, 120, tft.width(), WHITE);

}

void MCU_Display::printText(char *Msg)
{
    //Serial.println(Msg);

     tft.fillRect(1, 170, 318, 30, BLACK);
     tft.setCursor(15, 170);
    tft.setFont();
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.print(Msg);
    delay(10);
}


void MCU_Display::displaySpeed(byte clockSpeed) {

   //clockSpeed = clockSpeeds[x];

    strcpy(message, "Speed = ");
    if (clockSpeed < 10) {
      message[8] = '0' + clockSpeed;
      message[9] = 0;
    } else{
      message[8] = '0' + clockSpeed/10;
      message[9] = '0' + clockSpeed%10;
      message[10] = 0;
    }

    tft.fillRect(10, 170, 240, 22, BLACK);
    showmsgXY(10, 190, 1, YELLOW, message);
   
}

//void showmsgXY(byte x, byte y, byte sz, char colour, const char *msg)
void MCU_Display::showmsgXY(byte x, byte y, byte sz, char colour, char *msg)
{
    tft.setFont();
    tft.setFont(&Arial9pt7b);
    tft.setCursor(x, y);
    tft.setTextColor(colour);
    tft.setTextSize(sz);
    tft.print(msg);
    delay(10);
}


void MCU_Display::checkButtons()
{

    tft.setFont();

    bool down = touchGetXY();

    for (uint8_t b = 0; b < 6; b++){
      key[b].press(down && key[b].contains(pixel_x, pixel_y));
      if (key[b].justReleased())
          key[b].drawButton();
      if (key[b].justPressed()) {
          key[b].drawButton(true);
          ButtonPressed = b + 1;
          delay(debounceDelay);
      }
    }
  
}


}

bool MCU_Display::touchGetXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}
