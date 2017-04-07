#include "distance.h"
#include "event_driven.h"

// defines pins numbers
const int trigPin1 = 12;
const int echoPin1 = 11;

const int trigPin2 = 9;
const int echoPin2 = 8;

const int beeperPin = 2;

const int addButton = 3;
const int subButton = 5;
const int confirmButton = 6;

const int cSharp = 277;
const int fSharp = 370;
const int gSharp = 415;

enum state {
  initial,
  counting,
  pastLimit
};

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
      initialState();
    break;
    case counting:
    break;
    case pastLimit:
    break;
  }
}

void buttonChanged(int pin, int value) {
  if (value == HIGH) {
    switch (pin) {
      case addButton:
        tone(beeperPin, cSharp);
        maxOccupants++;
        break;
      case subButton:
        tone(beeperPin, fSharp);
        maxOccupants--;
        break;
      case confirmButton:
        break;
    }
  } else {
    noTone(beeperPin);
  }
}

void timerExpired() {
}

void initialState() {
  if (maxOccupants == 0) {
    Serial.println("Enter max occupants");
  } else {
    Serial.print("Max occupants: ");
    Serial.println(maxOccupants);
  }
}

void countingState() {
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 2: ");
  Serial.println(distance2);
}

void pastLimitState() {

}

