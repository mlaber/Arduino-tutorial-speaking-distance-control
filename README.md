# Arduino-Tutorial-Talking-distance-control

## Abstract:
This repo is part of an Arduino tutorial an should help the audience to get familiar with the Arduino IDE and the ESP32 microcontroller.
The speaking distance control measures the distance to an object displays it on the LCD and uses speech samples to give audio feedback like the [Ground proximity warning systemes](https://en.wikipedia.org/wiki/Ground_proximity_warning_system) in aircrafts.

## Part list
* ESP32 NideMCU Microcontroller
* 128x160 Pixel TFT Display (ST7735 controller IC)
* 4 Ohm, 3 Watt mini speaker
* HC-SR04 ultrasonic distance sensor
* PAM8403 3 Watt stereo amp module

## Wiring
![Board design](https://github.com/mlaber/Arduino-tutorial-speaking-distance-control/blob/main/speaking-distance_Steckplatine.png)


## Notes
Using the DAC_Audio library provided by [XTronical](https://www.xtronical.com/the-dacaudio-library-download-and-installation/)
