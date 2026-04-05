#include <Arduino.h>
#define RED_LED  4
#define BLUE_LED 5

#define FLASH_ON_MS  150
#define FLASH_OFF_MS 100

static bool     redTurn   = true;   // чия черга: true=червоний, false=синій
static bool     ledOn     = false;  // LED зараз горить чи ні
static uint32_t startTime = 0;

void setup() {
  pinMode(RED_LED,  OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(RED_LED,  LOW);
  digitalWrite(BLUE_LED, LOW);
  startTime = millis();
}

void loop() {
  uint32_t timeout = ledOn ? FLASH_ON_MS : FLASH_OFF_MS;

  if (millis() - startTime < timeout) return;

  startTime += timeout;

  if (ledOn) {
    // гасимо поточний LED і передаємо чергу іншому
    digitalWrite(redTurn ? RED_LED : BLUE_LED, LOW);
    redTurn = !redTurn;  // міняємо чергу
    ledOn   = false;
  } else {
    // вмикаємо поточний LED
    digitalWrite(redTurn ? RED_LED : BLUE_LED, HIGH);
    ledOn = true;
  }
}
