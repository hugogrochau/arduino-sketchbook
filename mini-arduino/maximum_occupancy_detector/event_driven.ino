#include "event_driven.h"

// “pin” passado deve gerar notificações
char buttonStates[3];
int buttonPins[3];
int numButtons = 0;

void buttonListen(int pin) {
  pinMode(pin, INPUT);
  buttonPins[numButtons] = pin;
  numButtons++;
}

// timer deve expirar após “ms” milisegundos
unsigned long timerEnd = 0;

void timer_set(int ms) {
  timerEnd = millis() + ms;
}

/* Programa principal: */
// inicialização da API
void setup () {
  for (int i = 0; i < 2; i++) {
    buttonStates[i] = LOW;
  }
  
  // inicialização do usuário
  setup_();                
}

void loop () {
  unsigned long currentTime = millis();
  if (timerEnd && currentTime > timerEnd) {
    timerEnd = 0;
    timerExpired();
  }
  
  for (int i = 0; i < numButtons; i++) {
    int pin = buttonPins[i];
    int state = digitalRead(pin);
    if (state != buttonStates[i]) {
       buttonChanged(pin, state);
       buttonStates[i] = state;  
    }
  }
  
  // loop do usuário
  loop_();
}
