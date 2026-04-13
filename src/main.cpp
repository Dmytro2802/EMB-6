#include <Arduino.h>

#define RED_LED      4
#define BLUE_LED     5
#define EXT_BUTTON   2
#define BOOT_BUTTON  0

#define FAST_DELAY   100
#define SLOW_DELAY   500
#define DEBOUNCE_MS  50

volatile int blinkDelay = SLOW_DELAY;
volatile unsigned long lastPressTime = 0;

void IRAM_ATTR onExtButton() {
  unsigned long now = millis();
  if (now - lastPressTime > DEBOUNCE_MS) {
    blinkDelay = FAST_DELAY;
    lastPressTime = now;
  }
}

void IRAM_ATTR onBootButton() {
  unsigned long now = millis();
  if (now - lastPressTime > DEBOUNCE_MS) {
    blinkDelay = SLOW_DELAY;
    lastPressTime = now;
  }
}

void setup() {
  pinMode(RED_LED,     OUTPUT);
  pinMode(BLUE_LED,    OUTPUT);
  pinMode(EXT_BUTTON,  INPUT_PULLUP);
  pinMode(BOOT_BUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(EXT_BUTTON),  onExtButton,  FALLING);
  attachInterrupt(digitalPinToInterrupt(BOOT_BUTTON), onBootButton, FALLING);
}

void loop() {
  digitalWrite(RED_LED,  HIGH);
  digitalWrite(BLUE_LED, LOW);
  delay(blinkDelay);

  digitalWrite(RED_LED,  LOW);
  digitalWrite(BLUE_LED, HIGH);
  delay(blinkDelay);
}