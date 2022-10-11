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
#include "HD_0158_RG0019A.h"
using namespace lgfx;

// HD_0158_RG0019A library doesn't use manual RAM control.
// Set SE and AB low.
#define PANEL_PIN_A3  23
#define PANEL_PIN_A2  21
#define PANEL_PIN_A1  25
#define PANEL_PIN_A0  26
#define PANEL_PIN_DG  19
#define PANEL_PIN_CLK 18
#define PANEL_PIN_WE  17
#define PANEL_PIN_DR  16
#define PANEL_PIN_ALE 22
#define PANEL_PIN_SE  13
#define PANEL_PIN_AB  27
#define PANEL_NUM     2  // two panels setting

class ESP32_HD0158_LGFX : public LGFX_Device {
public:
  ESP32_HD0158_LGFX(void) : _panel(PANEL_NUM,
                                   PANEL_PIN_A3,
                                   PANEL_PIN_A2,
                                   PANEL_PIN_A1,
                                   PANEL_PIN_A0,
                                   PANEL_PIN_DG,
                                   PANEL_PIN_CLK,
                                   PANEL_PIN_WE,
                                   PANEL_PIN_DR,
                                   PANEL_PIN_ALE) {
    // For auto RAM A/B changing
    pinMode(PANEL_PIN_SE, OUTPUT);
    pinMode(PANEL_PIN_AB, OUTPUT);
    digitalWrite(PANEL_PIN_SE, LOW);
    digitalWrite(PANEL_PIN_AB, LOW);

    auto cfg = _panel.config();

    cfg.memory_width = cfg.panel_width = 32 * PANEL_NUM;
    cfg.memory_height = cfg.panel_height = 16;

    cfg.rgb_order = true;

    _panel.config(cfg);
    _panel.setColorDepth(color_depth_t::rgb565_nonswapped);
    _panel.setRotation(0);

    setPanel(&_panel);
  }

private:
  HD_0158_RG0019A _panel;
};
