#include <Arduino.h>
#include "extended_beacon.hpp"

#define GPIO_LED GPIO_NUM_8

#define BEACON_UUID "00000000-0000-0000-0000-000000000008"
#define BEACON_NAME "Beacon 8"

volatile bool error = false;

void blinkPattern(uint8_t r, uint8_t g, uint8_t b, uint16_t delay_ms, uint8_t num_times) {
  for (uint8_t i = 0; i < num_times; i++) {
    neopixelWrite(GPIO_LED, r, g, b);
    delay(delay_ms);
    neopixelWrite(GPIO_LED, 0, 0, 0);
    delay(delay_ms);
  }
}

void setup() {
  blinkPattern(0, RGB_BRIGHTNESS, 0, 200, 5); // 2 sec
  neopixelWrite(GPIO_LED, 0, 0, RGB_BRIGHTNESS);

  ExtendedBeacon beacon(BEACON_UUID, BEACON_NAME);
  error = !beacon.start();
}

void loop() {
  if (error) {
    blinkPattern(RGB_BRIGHTNESS, 0, 0, 500, 60); // 1 min
    neopixelWrite(GPIO_LED, 0, 0, 0);
    esp_deep_sleep_start();
  }

  delay(1000); // 1 sec
}
