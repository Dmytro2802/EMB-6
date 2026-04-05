#include <Arduino.h>
#define RED_LED  4
#define BLUE_LED 5

#define FLASH_ON_MS  150
#define FLASH_OFF_MS 100

static bool     redTurn   = true;   
static bool     ledOn     = false;  
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
    digitalWrite(redTurn ? RED_LED : BLUE_LED, LOW);
    redTurn = !redTurn; 
    ledOn   = false;
  } else {
    digitalWrite(redTurn ? RED_LED : BLUE_LED, HIGH);
    ledOn = true;
  }
}
