# Omnitrix
*Built 2022 (Grade 12)*

A wearable replica of the Omnitrix from BEN10 Omniverse, built from a hand sketch through 3D-printed shell to working electronics with display, sound, and WiFi; all functional.

![omnitrix demo](_forREADME/preview.mp4)

## About
- Sketched the design in a notebook
- Modeled in SketchUp
    - [View 3D model](model/om_omitrix.stl)
    - [SketchUp online view](https://app.sketchup.com/share/tc/asia/PURIXS78B2o?source=web&stoken=ISEB06Jzt2daRUTS5baNcMTQGDCTEWSpj3dOnC49rCvpmC_fDfDo_K8EKKh11-AL)
- 3D printed the shell
- ESP32-S2 Mini wired to a TFT screen and a speaker
- Can be powered using two 12V 23A alkaline cells (wired in parallel)

## What It Does
- **Play Feature** —  physical buttons drive an on-screen menu and animations to cycle between 8 alien icons synced with sound effects
    - *There are 4 buttons, 3 on the side and 1 behind the screen to allow you to activate the omnitrix just like in the show*
- **WiFi Setup** — connects via a captive portal (using the WiFiManager library) so it can be configured from a phone, no hardcoded credentials
- **Time Lookup** — syncs time over NTP and display it on the screen

## Component
- ESP32-S2 Mini
- TFT 1.3 inch
- LM386 Audio Amplifier
- Speaker (collected from broken earbuds)
- Wires (collected from broken earbuds)
- 5V Buck converter

## Wiring

| Component | Signal | GPIO Pin |
|---|---|---|
| Display (TFT) | MOSI | 11 |
| Display (TFT) | SCLK | 7 |
| Display (TFT) | CS | 6 |
| Display (TFT) | DC | 35 |
| Display (TFT) | RST | 39 |
| Display (TFT) | Backlight | 16 |
| LM386 (audio amp) | BCLK/WSEL | 5 |
| LM386 (audio amp) | Data | 17 |
| Buttons | 4x inputs | 3, 4, 18, 21 |

**This pinout was reconstructed from the code.*

## Built With
- Arduino IDE 1.8.19
- ESP32 board package (Espressif) v2.0.17, board set to "LOLIN S2 Mini"
- Libraries: TFT_eSPI, WiFiManager, ESP8266Audio
    - working copies included in `_library/` (see below)

## Constraints
- The ESP32-S2 Mini's flash storage filled up fast because of audio, bitmap graphics and code combined — final build used **99%** of available program storage. I coded main screen to be draw manually instead of storing it as bitmap like the icons, to lower the storage used.

- The sound this build can produce is quite quiet because the speaker is collected from earbud. Making it hard to hear if in a loud environment.

- Battery choice (23A cells) was picked for its small size to keep the build wearable. Even so, the battery tray ended up being the second-largest component. This also makes its runtime pretty short, around 2-3 minutes per pair of cells.

## Library Credits
`_library/` contains known-working copies of each dependency, since exact original versions aren't otherwise documented and newer releases aren't confirmed to work:
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [WiFiManager](https://github.com/tzapu/WiFiManager)
- [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio)
