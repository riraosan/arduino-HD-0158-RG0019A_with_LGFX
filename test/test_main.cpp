
/*
MIT License

Copyright (c) 2021-2022 riraosan.github.io

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
