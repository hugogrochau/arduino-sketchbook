#include "state.h"
#include "distance.h"
#include "event_driven.h"
#include "initial_state.h"
#include "counting_state.h"
#include "past_limit_state.h"

const int trigPin1 = 12;
const int echoPin1 = 11;

const int trigPin2 = 9;
const int echoPin2 = 8;

const int beeperPin = 2;

const int addButton = 3;
const int subButton = 5;
const int confirmButton = 6;

state currentState = initial;
int maxOccupants = 0;

void setup_() {
  pinMode(trigPin1, OUTPUT); 
  pinMode(trigPin2, OUTPUT);
  
  pinMode(echoPin1, INPUT);  
  pinMode(echoPin2, INPUT);

  pinMode(beeperPin, OUTPUT);

  buttonListen(addButton);
  buttonListen(subButton);
  buttonListen(confirmButton);
  
  Serial.begin(9600); // Starts the serial communication
}

void loop_() {
  switch (currentState) {
    case initial:
      initialStateLoop();
    break;
    case counting:
      countingStateLoop();
    break;
    case pastLimit:
      pastLimitStateLoop();
    break;
  }
}

void buttonChanged(int pin, int value) {
  switch (currentState) {
    case initial:
      initialStateButtonChanged(pin, value);
    break;
    case counting:
      countingStateButtonChanged(pin, value);
    break;
    case pastLimit:
      pastLimitStateButtonChanged(pin, value);
    break;
  }
}

void timerExpired() {

}

