#include "event_driven.h"

// “pin” passado deve gerar notificações
char buttonStates[2];
int buttonPins[2];
int num_buttons = 0;

void button_listen(int pin) {
  pinMode(pin, INPUT);
  buttonPins[num_buttons] = pin;
  num_buttons++;
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
  init_();                
}

void loop () {

  unsigned long currentTime = millis();
  if (timerEnd && currentTime > timerEnd) {
    timerEnd = 0;
    timer_expired();
  }
  
  for (int i = 0; i < num_buttons; i++) {
    int pin = buttonPins[i];
    int state = digitalRead(pin);
    if (state != buttonStates[i]) {
       button_changed(pin, state);
       buttonStates[i] = state;  
    }
  }
}

