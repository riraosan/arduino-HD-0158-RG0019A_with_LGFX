# arduino-HD-0158-RG0019A with M5GFX

## Summary

//TODO 画像


This library can control the HD-1580-RG0019A LED matrix. The drawing library uses M5GFX (LovyanGFX).
The original author used Adafruite_GFX with [arduno-HD-0158-RG0019A](https://github.com/techno/arduino-HD-0158-RG0019A) library. 
I replaced this library with M5GFX for the purpose of using features that M5GFX has.

- You can take advantage of the M5GFX's fast drawing capabilities
- You have access to a large number of fonts provided by the M5GFX
- You can use the many APIs provided by the M5GFX
- However, you cannot use the sprite function.(Not tested.That feature might work, but I don't see the need for the Sprite functions.)

## Devices

### ESP32

- ESP32 Board examples
  - lolin32
  - ESPr developer32

### HD-0158-RG0019A

I show next the devices to be controlled.

[32×16ドットマトリクスLEDパネル(赤/橙/緑)■限定特価品■32x16DOT-0158-DJK](https://eleshop.jp/shop/g/gEB8411/)

You need 11 GPIOs to make this device work.

```c++
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
```

- You use an ESP32 device board with many GPIOs.
- You modify PANEL_NUM when you are using two or more LED matrix panels chained together.

## How to build

PlatformIOでこのソースをビルドしたことを説明する
ArduinoIDEでのビルドは確認していないが、多分このようになるだろうということを書いておく

## How to use

1. You copy the library to a directory in your development environment.
2. You write in your code to create an instance of the library.
3. You execute the begin() method in the setup() method of your source code.
4. You set the initial font, initial cursor position, colors (black, green, red, orange), etc. in your source code for the M5GFX.
5. You execute the various M5GFX drawing APIs (horizontal lines, vertical lines, rectangles, fill rectangles, etc.) with the loop() method, etc.

I would recommend that you refer to the basic usage of the API here.
[Adafruit GFX Graphics Library Graphics Primitives](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives)

The author of the M5GFX library created it with reference to the Adafruit_GFX API. I suggest you refer to this reference.
Or I think you can parse the code directly to find out how to use it.

If you are using AruduinoIDE, I would recommend that you build your source code writing environment with a combination of VSCode and PlatformIO extensions. 
## Library's

I have confirmed this library works with arduino-esp32 ver 2.0.3.

```yaml
[arduino-esp32]
platform          = platformio/espressif32@^4.4.0
```

I have put the GitHub link to the library under the `lib_deps =` directive. You can download the library from GitHub yourself and register it with the Arduino IDE.

```yaml
lib_deps =
        https://github.com/m5stack/M5GFX.git#0.0.20
```

## About example

I have created an NTP clock.（It contains unnecessary code.）
This sample code has a simple timer function that can turn specific GPIOs on or off.

Here is where I am drawing on the LED matrix.

```c++
void loop(void) {
  Portal.handleClient();
  switch (message) {
    case MESSAGE::MSG_COMMAND_GET_SENSOR_DATA:
      message = MESSAGE::MSG_COMMAND_NOTHING;
      break;
    case MESSAGE::MSG_COMMAND_START_CLOCK:
      digitalWrite(PORT_LAMP, HIGH);
      startClock();
      message = MESSAGE::MSG_COMMAND_NOTHING;
      break;
    case MESSAGE::MSG_COMMAND_STOP_CLOCK:
      stopClock();
      message = MESSAGE::MSG_COMMAND_PRINT_TEMPERATURE_VALUE;
      break;
    case MESSAGE::MSG_COMMAND_NOTHING:
    default:;  // nothing
  }

  char tmp_str[10] = {0};
  time_t t         = pftime::time(NULL);
  struct tm *tm    = pftime::localtime(&t);
  if (tm->tm_sec != oldSeconds && isEnableClock) {
    sprintf(tmp_str, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    oldSeconds = tm->tm_sec;
    matrix.startWrite();
    matrix.setCursor(1, -1);
    matrix.setTextColor(DOT_GREEN, DOT_BLACK);
    matrix.print(tmp_str);
    matrix.drawLine(0, 0, 0, 15, DOT_GREEN);
    matrix.drawLine(1, 0, 1, 15, DOT_GREEN);
    matrix.drawLine(0, 15, 63, 15, DOT_GREEN);
    matrix.endWrite();
  }

  ::delay(1);
}

```

## License

[MIT](https://github.com/riraosan/arduino-HD-0158-RG0019A_with_LGFX/blob/master/LICENSE) License

Feel free to modify or reprint. We would appreciate it if you could reprint the URL of this repository.

## Acknowledgements

If I could look out over the distance, it was on the shoulders of giants.
We would like to thank the authors of each library. Thank you very much.

- [@m5stack](https://github.com/m5stack/M5GFX.git)
- [@techno](https://github.com/techno/arduino-HD-0158-RG0019A)

## Conclusion

It would be a great pleasure and a blessing if I could contribute in some way to someone somewhere.

Enjoy!👍
