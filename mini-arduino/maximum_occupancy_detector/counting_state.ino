#include "counting_state.h"
#include "notes.h"

const unsigned long triggerResetDelay = 2000;
const unsigned long personPassDelay = 1000;
const int distanceChangeToTrigger = 15;

unsigned long lastSample = 0;
unsigned long lastPersonPass = 0;
unsigned long lastTrigger = 0;

int lastDistance1 = 0;
int lastDistance2 = 0;
int currentOccupants = 0;
int activeSensor = 0;

void countingStateLoop() {
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  // first run
  if (!lastDistance1 || !lastDistance2) {
    lastDistance1 = distance1;
    lastDistance2 = distance2;
  }

  // Beep when over capacity
  if (currentOccupants > maxOccupants) {
    tone(errorBeeperPin, NOTE_F);
  } else {
    noTone(errorBeeperPin);
  }

  if (millis() - lastTrigger > triggerResetDelay) {
    activeSensor = 0;
    lastTrigger = millis();
  }

  if (millis() - lastPersonPass > personPassDelay) {
    bool sensor1Triggered = lastDistance1 - distance1 > distanceChangeToTrigger;
    bool sensor2Triggered = lastDistance2 - distance2 > distanceChangeToTrigger;
    
    if (sensor1Triggered) {
      sensor1Changed();
      lastTrigger = millis();
    } else if (sensor2Triggered) {
      sensor2Changed();
      lastTrigger = millis();
    } else {
      noTone(beeperPin);
    }
    
    lastDistance1 = distance1;
    lastDistance2 = distance2;
  }
}

void countingStateButtonChanged(int pin, int value) {
  
}

void personPassed(int sign) {
  currentOccupants += sign;
  if (currentOccupants < 0) {
    currentOccupants = 0;
  }
  activeSensor = 0;
  lastPersonPass = millis();
  tone(beeperPin, sign == 1 ? NOTE_A : NOTE_G_SHARP);
  printOccupants();
}

void sensor1Changed() {
  if (activeSensor == 2) {
    personPassed(1);
  } else {
    activeSensor = 1;
  }
}

void sensor2Changed() {
  if (activeSensor == 1) {
    personPassed(-1);
  } else {
    activeSensor = 2;
  }
}

void printOccupants() {
  Serial.print("Occupants (");
  Serial.print(currentOccupants);
  Serial.print("/");
  Serial.print(maxOccupants);
  Serial.println(")");
}

