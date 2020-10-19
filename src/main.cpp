#include <Arduino.h>
#include <Bounce2.h>
#include <Adafruit_DRV2605.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pitches.h"

#define SPKR 3

#define LED_R 9
#define LED_G 11
#define LED_B 10

#define BTN_0 5
#define BTN_1 6
#define BTN_2 7
#define BTN_3 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Bounce btn0, btn1, btn2, btn3;
Adafruit_DRV2605 drv;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setLed(uint8_t r, uint8_t g, uint8_t b) {
  analogWrite(LED_R, 255 - r);
  analogWrite(LED_G, 255 - g);
  analogWrite(LED_B, 255 - b);
}

void playTone(unsigned int freq, unsigned int duration) {
  tone(SPKR, freq, duration);
}

void mute() {
  noTone(SPKR);
}

void vibrate(uint8_t effect) {
  drv.setWaveform(0, effect);
  drv.setWaveform(1, 0);
  drv.go();
}

void showMessage(const __FlashStringHelper * text) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(text);
  display.display();
}

void setup() {
  delay(1000);

  playTone(NOTE_C6, 300);

  btn0.attach(BTN_0, INPUT_PULLUP);
  btn0.interval(25);
  btn1.attach(BTN_1, INPUT_PULLUP);
  btn1.interval(25);
  btn2.attach(BTN_2, INPUT_PULLUP);
  btn2.interval(25);
  btn3.attach(BTN_3, INPUT_PULLUP);
  btn3.interval(25);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  setLed(0, 0, 0);

  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.dim(true);
  display.clearDisplay();
}

void loop() {
  btn0.update();
  btn1.update();
  btn2.update();
  btn3.update();

  if (btn0.fell()) {
    playTone(NOTE_C4, 200);
    setLed(255, 0, 0);
    vibrate(17);
    showMessage(F("Button 0"));
  }
  if (btn1.fell()) {
    playTone(NOTE_C5, 200);
    setLed(0, 255, 0);
    vibrate(17);
    showMessage(F("Button 1"));
  }
  if (btn2.fell()) {
    playTone(NOTE_C6, 200);
    setLed(0, 0, 255);
    vibrate(17);
    showMessage(F("Button 2"));
  }
  if (btn3.fell()) {
    playTone(NOTE_C7, 200);
    setLed(0, 0, 0);
    vibrate(17);
    showMessage(F("Button 3"));
  }
}