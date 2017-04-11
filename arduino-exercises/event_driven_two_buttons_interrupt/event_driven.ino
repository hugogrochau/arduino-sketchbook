#include "event_driven.h"

// “pin” passado deve gerar notificações
char button_states[2];
int button_pins[2];
int num_buttons = 0;

void button_listen(int pin) {
  pinMode(pin, INPUT);
  pciSetup(pin);
  button_pins[num_buttons] = pin;
  num_buttons++;
}

// timer deve expirar após “ms” milisegundos
unsigned long timer_end = 0;

void pciSetup(byte pin) {
  // enable pin
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));
  // clear any outstanding interrupt (Interrupt Flag) 
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); 
  // enable interrupt for the group (Interrupt Control)
  PCICR  |= bit (digitalPinToPCICRbit(pin)); 
}

ISR(PCINT1_vect) {
  
  for (int i = 0; i < num_buttons; i++) {
    int pin = button_pins[i];
    int state = digitalRead(pin);
    if (state != button_states[i]) {
       button_changed(pin, state);
       button_states[i] = state;  
    }
  }
}

void timer_set(int ms) {
  timer_end = millis() + ms;
}

/* Programa principal: */
// inicialização da API
void setup() {
  Serial.begin(9600);
  sei();
    
  for (int i = 0; i < 2; i++) {
    button_states[i] = LOW;
  }
  
  // inicialização do usuário
  init_();
}

void loop() {

  unsigned long current_time = millis();
  if (timer_end && current_time > timer_end) {
    timer_end = 0;
    timer_expired();
  }
}

