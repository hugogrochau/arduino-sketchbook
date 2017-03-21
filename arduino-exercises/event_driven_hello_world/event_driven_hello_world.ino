#include "event_driven.h"

#define LED_PIN 13
#define BUT_PIN A2

void button_changed(int pin, int v) {
  digitalWrite(LED_PIN, v);
}

void init_() {
  pinMode(LED_PIN, OUTPUT);
  button_listen(BUT_PIN);
}

void timer_expired() { }
