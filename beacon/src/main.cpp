#include <Arduino.h>
#include "beacon.hpp"

#define GPIO_BLINK GPIO_NUM_1

#define BEACON_UUID "00000000-0000-0000-0000-000000000005"
#define BEACON_NAME "Beacon 5"

TaskHandle_t taskBlinkHandler;

volatile bool error = false;

void blinkPattern(gpio_num_t gpio, int ms, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(gpio, LOW);
    vTaskDelay(ms);
    digitalWrite(gpio, HIGH);
    vTaskDelay(ms);
  }
}

void TaskBlink(void *pvParameters) {
  while (!error) {
    vTaskDelay(3800);
    blinkPattern(GPIO_BLINK, 200, 3);
  }

  digitalWrite(GPIO_BLINK, LOW);
  vTaskDelete(NULL);
}

void setup() {
  pinMode(GPIO_BLINK, OUTPUT);
  blinkPattern(GPIO_BLINK, 200, 3);

  xTaskCreatePinnedToCore(TaskBlink, "Blinking", 10000, NULL, 1, &taskBlinkHandler, 1);

  Beacon beacon(BEACON_UUID, BEACON_NAME);
  error = !beacon.start();
}

void loop() {
}
