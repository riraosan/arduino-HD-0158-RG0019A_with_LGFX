/*
ESP32_HD0158_LGFX Library

Original Source:
https://github.com/techno/arduino-HD-0158-RG0019A

Licence:
[MIT](https://github.com/riraosan/ESP32_HD0158_LGFX/blob/master/LICENSE)

Author:
[riraosan](https://twitter.com/riraosan_0901)

Contributors:
[techno](https://github.com/techno)
[lovyan03](https://github.com/lovyan03)
[M5Stack](https://github.com/m5stack)

The ESP32_HD0158_LGFX library depends on the following libraries.
[M5GFX](https://github.com/m5stack/M5GFX)
*/

#pragma once

#include <M5GFX.h>
#include "lgfx/v1/panel/Panel_Device.hpp"
#include "lgfx/v1/misc/range.hpp"
#include "lgfx/v1/LGFXBase.hpp"

using namespace lgfx;

#define DOT_PANEL_WIDTH  32
#define DOT_PANEL_HEIGHT 16

#define DOT_BLACK        0x0000
#define DOT_RED          0xF800
#define DOT_GREEN        0x07E0
#define DOT_ORANGE       (DOT_RED | DOT_GREEN)

class HD_0158_RG0019A : public Panel_Device {
public:
  HD_0158_RG0019A(void){};
  HD_0158_RG0019A(int8_t n_panel,
                  int8_t pin_a3,
                  int8_t pin_a2,
                  int8_t pin_a1,
                  int8_t pin_a0,
                  int8_t pin_dg,
                  int8_t pin_clk,
                  int8_t pin_we,
                  int8_t pin_dr,
                  int8_t pin_ale);

  ~HD_0158_RG0019A();

  void begin();
  void drawPixel(int16_t x, int16_t y, uint32_t color);
  void startWrite(void);
  void writePixel(int16_t x, int16_t y, uint32_t color);
  void endWrite(void);

  void initBus(void) override {}
  void releaseBus(void) override {}

  bool init(bool use_reset) {
    (void)use_reset;
    begin();
    return true;
  }

  void beginTransaction(void) override {
    startWrite();
  }

  void endTransaction(void) override {
    endWrite();
  }

  color_depth_t setColorDepth(color_depth_t depth) override {
    _write_depth = depth;
    _read_depth  = depth;
    return depth;
  }

  void setInvert(bool) override {
  }

  void setRotation(uint_fast8_t r) {
    r &= 7;
    _rotation = r;

    _internal_rotation = ((r + _cfg.offset_rotation) & 3) | ((r & 4) ^ (_cfg.offset_rotation & 4));

    auto ox = _cfg.offset_x;
    auto oy = _cfg.offset_y;
    auto pw = _cfg.panel_width;
    auto ph = _cfg.panel_height;
    auto mw = _cfg.memory_width;
    auto mh = _cfg.memory_height;

    if (_internal_rotation & 1) {
      std::swap(ox, oy);
      std::swap(pw, ph);
      std::swap(mw, mh);
    }

    _width  = pw;
    _height = ph;

    _xe = pw - 1;
    _ye = ph - 1;
    _xs = 0;
    _ys = 0;
  }

  void setSleep(bool) override {}
  void setPowerSave(bool) override {}

  void writeCommand(uint32_t, uint_fast8_t) override {}
  void writeData(uint32_t, uint_fast8_t) override {}

  void initDMA(void) override {}
  void waitDMA(void) override {}
  bool dmaBusy(void) override { return false; }
  void waitDisplay(void) override {}
  bool displayBusy(void) override { return false; }
  void display(uint_fast16_t x, uint_fast16_t y, uint_fast16_t w, uint_fast16_t h) override {
    endWrite();
  }
  bool isReadable(void) const override { return false; }
  bool isBusShared(void) const override { return false; }

  void writeBlock(uint32_t rawcolor, uint32_t length) override {
    uint32_t xs   = _xs;
    uint32_t xe   = _xe;
    uint32_t ys   = _ys;
    uint32_t ye   = _ye;
    uint32_t xpos = _xpos;
    uint32_t ypos = _ypos;

    do {
      auto len = std::min<uint32_t>(length, xe + 1 - xpos);
      writeFillRectPreclipped(xpos, ypos, len, 1, rawcolor);
      xpos += len;
      if (xpos > xe) {
        xpos = xs;
        if (++ypos > ye) {
          ypos = ys;
        }
      }
      length -= len;
    } while (length);

    _xs   = xs;
    _xe   = xe;
    _ys   = ys;
    _ye   = ye;
    _xpos = xpos;
    _ypos = ypos;
  }

  void setWindow(uint_fast16_t xs, uint_fast16_t ys, uint_fast16_t xe, uint_fast16_t ye) override {
    xs  = std::max(0u, std::min<uint_fast16_t>(_width - 1, xs));
    xe  = std::max(0u, std::min<uint_fast16_t>(_width - 1, xe));
    ys  = std::max(0u, std::min<uint_fast16_t>(_height - 1, ys));
    ye  = std::max(0u, std::min<uint_fast16_t>(_height - 1, ye));
    _xs = xs;
    _xe = xe;
    _ys = ys;
    _ye = ye;
  }

  void drawPixelPreclipped(uint_fast16_t x, uint_fast16_t y, uint32_t rawcolor) {
    writePixel(x, y, rawcolor);
  }

  void writeFillRectPreclipped(uint_fast16_t x, uint_fast16_t y, uint_fast16_t w, uint_fast16_t h, uint32_t rawcolor) {
    //log_i("here %02d %02d %02d %02d 0x%06x ", x, y, w, h, rawcolor);
    for (uint_fast16_t _x = x; _x < x + w; _x++) {
      for (uint_fast16_t _y = y; _y < y + h; _y++) {
        writePixel(_x, _y, rawcolor);
      }
    }
  }

  void writeImage(uint_fast16_t x, uint_fast16_t y, uint_fast16_t w, uint_fast16_t h, pixelcopy_t *param, bool use_dma) override {}

  void writeImageARGB(uint_fast16_t x, uint_fast16_t y, uint_fast16_t w, uint_fast16_t h, pixelcopy_t *param) override {}

  void writePixels(pixelcopy_t *param, uint32_t length, bool use_dma) override {}

  void writePixel(uint_fast16_t x, uint_fast16_t y, uint32_t color) {
    if (!bufferR || !bufferG || x < 0 || x >= DOT_PANEL_WIDTH * nPanel || y < 0 || y >= DOT_PANEL_HEIGHT) {
      return;
    }

    uint_fast16_t i      = (x >> 5) + (y * nPanel);
    uint8_t       panelX = x & 31;

    uint16_t _color = lgfx::v1::getSwap16(color);
    // log_w("%04X", _color);

    switch (_color) {
      case DOT_RED:
        bufferR[i] |= 1 << panelX;
        bufferG[i] &= ~(1 << panelX);
        break;
      case DOT_GREEN:
        bufferR[i] &= ~(1 << panelX);
        bufferG[i] |= 1 << panelX;
        break;
      case DOT_ORANGE:
        bufferR[i] |= 1 << panelX;
        bufferG[i] |= 1 << panelX;
        break;
      default:
        bufferR[i] &= ~(1 << panelX);
        bufferG[i] &= ~(1 << panelX);
        break;
    }
  }

  uint32_t readCommand(uint_fast8_t, uint_fast8_t, uint_fast8_t) override { return 0; }
  uint32_t readData(uint_fast8_t, uint_fast8_t) override { return 0; }
  void     readRect(uint_fast16_t, uint_fast16_t, uint_fast16_t, uint_fast16_t, void *, pixelcopy_t *) override {}
  void     copyRect(uint_fast16_t, uint_fast16_t, uint_fast16_t, uint_fast16_t, uint_fast16_t, uint_fast16_t) override {}

private:
  int8_t    pinA3, pinA2, pinA1, pinA0, pinDG, pinCLK, pinWE, pinDR, pinALE;
  uint8_t   nPanel;
  uint32_t  transactionCounter;
  uint32_t *bufferR, *bufferG;

  uint_fast16_t _xpos;
  uint_fast16_t _ypos;
};
