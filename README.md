# arduino-HD-0158-RG0019A with M5GFX

## Summary

//TODO 画像を貼ること


This library can control the HD-1580-RG0019A LED matrix. The drawing library uses M5GFX (LovyanGFX).
The original author used Adafruite_GFX with arduno-HD-0158-RG0019A library. 
I replaced this library with M5GFX for the purpose of using features that M5GFX has.

- You can take advantage of the M5GFX's fast drawing capabilities
- You have access to a large number of fonts provided by the M5GFX
- You can use the many APIs provided by the M5GFX
- However, you cannot use the sprite function.(Not tested.That feature might work, but I don't see the need for the Sprite functions.)

## Devices

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

- Use an ESP32 device board with many GPIOs drawn.
- Modify PANEL_NUM when you are using two or more LED matrix panels chained together.

例）
- lolin32, 
- ESPr developer 32,

## How to build

PlatformIOでこのソースをビルドしたことを説明する
ArduinoIDEでのビルドは確認していないが、多分このようになるだろうということを書いておく

## How to use

1. ライブラリを開発環境のディレクトリへコピーします。
2. あなたのコードにライブラリのインスタンスを作成するように記述します。
3. あなたのソースコードのsetup()メソッドでbegin()メソッドを実行します。
4. あなたのソースコードでM5GFXで使用すフォント、初期カーソル位置、色（黒、緑、赤、オレンジ）などを設定します。
5. M5GFXの各種描画APIを実行します。（横線、縦線、矩形、塗りつぶし矩形など）

I would recommend that you refer to the basic usage of the API here.
[Adafruit GFX Graphics Library Graphics Primitives](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives)

The author of the M5GFX library created it with reference to the Adafruit_GFX API. I suggest you refer to this reference.
Or I think you can parse the code directly to find out how to use it.

もし、あなたがAruduinoIDEを使っているのであれば、あなたがVSCodeとPlatformIO拡張機能の組み合わせでソースコードを記述する環境を構築するように私はおすすめします。

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

I have created an NTP clock.（It contains unnecessary code. Sorry.）


## License

MIT License

Feel free to modify or reprint. We would appreciate it if you could reprint the URL of this repository.

## Acknowledgements

If I could look out over the distance, it was on the shoulders of giants.
We would like to thank the authors of each library. Thank you very much.

[@m5stack](https://github.com/m5stack/M5GFX.git)
[@techno](https://github.com/techno/arduino-HD-0158-RG0019A)

## Conclusion

It would be a great pleasure and a blessing if I could contribute in some way to someone somewhere.

Enjoy!👍
