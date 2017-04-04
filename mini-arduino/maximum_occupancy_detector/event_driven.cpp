#include "event_driven.h"

#define NUM_SENSORS 2

char sensorStates[NUM_SENSORS];
int sensorPins[NUM_SENSORS];
int lastSensorRegistered = -1;

void sensorListen(int pin) {
  pinMode(pin, INPUT);
  lastSensorRegistered++;
  buttonPins[lastSensorRegistered] = pin;
}

// timer deve expirar após “ms” milisegundos
unsigned long timerEnd = 0;

void timerSet(int ms) {
  timerEnd = millis() + ms;
}

/* Programa principal: */
// inicialização da API
void setup() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorStates[i] = LOW;
  }
  
  // inicialização do usuário
  init_();                
}

void loop () {

  unsigned long currentTime = millis();
  if (timerEnd && currentTime > timerEnd) {
    timerEnd = 0;
    timerExpired();
  }
  
  for (int i = 0; i <= lastSensorRegistered; i++) {
    int pin = sensorPins[i];
    int state = digitalRead(pin);
    if (state != sensorStates[i]) {
       sensorChanged(pin, state);
       sensorState[i] = state;  
    }
  }
}

