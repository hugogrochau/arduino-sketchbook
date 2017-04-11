#include "event_driven.h"
#include "TimerService.h"
#include "Scheduler.h"

TimerService myTimer; // Timer object
Scheduler taskCtl; // Scheduler object

// “pin” passado deve gerar notificações
char button_states[2];
int button_pins[2];
int num_buttons = 0;


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

void button_listen(int pin) {
  pinMode(pin, INPUT);
  pciSetup(pin);
  button_pins[num_buttons] = pin;
  num_buttons++;
}

void timer_callback() {
  taskCtl.post(0, timer_expired);
}

void timer_set(int ms) {
  myTimer.set(0, ms/1000.0, timer_callback);
}

/* Programa principal: */
// inicialização da API
void setup() {
  Serial.begin(9600);
  myTimer.init();
  
  for (int i = 0; i < 2; i++) {
    button_states[i] = LOW;
  }
  
  // inicialização do usuário
  init_();
}

void loop() { 
  taskCtl.loop();
}

