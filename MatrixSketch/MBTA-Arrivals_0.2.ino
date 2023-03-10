
// Defines the buffer height / the maximum height of the matrix
//#define PxMATRIX_MAX_HEIGHT 64

// Defines the buffer width / the maximum width of the matrix
//#define PxMATRIX_MAX_WIDTH 64

// Defines how long we display things by default
//#define PxMATRIX_DEFAULT_SHOWTIME 30

// Defines the speed of the SPI bus (reducing this may help if you experience noisy images)
//#define PxMATRIX_SPI_FREQUENCY 20000000

#include <PxMatrix.h>
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2
#define PxMATRIX_COLOR_DEPTH 3
#define matrix_width 64
#define matrix_height 32

// This defines the 'on' time of the display is us. The larger this number,
// the brighter the display. If too large the ESP will crash
uint8_t display_draw_time=60; //30-70 is usually fine
PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
uint16_t myORANGE = display.color565(255, 40, 0);
void setup() {

 Serial.begin(9600);
  display.begin(16);
  //display.setColorOffset(5, 5,5); //Minimum color values
  display.setColorOrder(BBRRGG);
  //display.setPanelsWidth(2); //User later for adding second panel
  display.setBrightness(200);
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(myORANGE);
  display.setCursor(22,2);
  display.print("T");
  delay(3000);

}
union single_double{
  uint8_t two[2];
  uint16_t one;
} this_single_double;

unsigned long last_draw=0;
void scroll_text(uint8_t ypos, unsigned long scroll_delay, String text, uint8_t colorR, uint8_t colorG, uint8_t colorB)
{
    uint16_t text_length = text.length();
    display.setTextWrap(false);  // we don't wrap text so it scrolls nicely
    display.setTextSize(2);
    display.setRotation(0);
    display.setTextColor(display.color565(colorR,colorG,colorB));

    for (int xpos=matrix_width; xpos>-(matrix_width+text_length*5); xpos--)
    {
      display.setTextColor(display.color565(colorR,colorG,colorB));
      display.clearDisplay();
      display.setCursor(xpos,ypos);
      display.println(text);
      delay(scroll_delay);
      yield();

      delay(scroll_delay/5);
      yield();

    }
}

uint8_t icon_index=0;
void loop() {
  scroll_text(9,50,"Display Train Var Here",255,40,0);
  display.clearDisplay();

  delay(500);
  for (uint8_t dimm=255; dimm>0; dimm--)
  {
    display.setBrightness(dimm);
    delay(5);
  }
  for (uint8_t dimm=0; dimm<255; dimm++)
  {
    display.setBrightness(dimm);
    delay(5);
  }

}
