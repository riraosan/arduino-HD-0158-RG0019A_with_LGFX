
/*
ESP32_HD0158_LGFX Library

Original Source:
https://github.com/techno/arduino-HD-0158-RG0019A

Licence:
[MIT](https://github.com/riraosan/ESP32_HD0158_LGFX/blob/master/LICENSE)

Author:
[riraosan](https://twitter.com/riraosan_0901)

Contributors:
[lovyan03](https://github.com/lovyan03)
[M5Stack](https://github.com/m5stack)

ESP32_HD0158_LGFXライブラリは以下のライブラリに依存しています。
[M5GFX](https://github.com/m5stack/M5GFX)
*/

#include <Arduino.h>
#include <unity.h>

#include <M5GFX.h>
using namespace lgfx;
using namespace lgfx::v1::fonts;

#include <ESP32_HD0158_LGFX.h>

ESP32_HD0158_LGFX display;
M5Canvas          canvas(&display);

void setup() {
  ::delay(2000);
  display.begin();
  display.setFont(&efontJA_16);
}

void fill(void) {
  log_w("here");
  display.fillScreen(DOT_RED);
  ::delay(1000);
  display.fillScreen(DOT_GREEN);
  ::delay(1000);
  // display.fillScreen(DOT_ORANGE);
  // ::delay(1000);
  display.fillScreen(DOT_BLACK);
  ::delay(1000);
  log_w("here");
}

void draw(void) {
  display.drawFastHLine(0, 16 / 2, 64);
  ::delay(1000);

  display.drawLine(0, 0, 64 - 1, 16 - 1);
  ::delay(1000);

  display.drawFastVLine(64 / 2, 0, 16);
  ::delay(1000);

  display.drawLine(0, 15, 64 - 1, 0);
  ::delay(1000);

  display.drawRect(0, 0, 64, 16);
  ::delay(1000);

  display.setTextColor(DOT_GREEN, DOT_BLACK);
  display.setCursor(0, 0);
  display.print("testTEST");
  ::delay(1000);

  display.fillScreen(DOT_BLACK);
  ::delay(1000);
}

void loop() {
  fill();

  display.setColor(DOT_ORANGE);
  draw();
  display.setColor(DOT_GREEN);
  draw();
  display.setColor(DOT_RED);
  draw();
}
