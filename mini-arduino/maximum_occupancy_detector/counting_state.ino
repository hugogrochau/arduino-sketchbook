#include "counting_state.h"
#include "notes.h"

const unsigned long triggerResetDelay = 3000;
const int distanceToChange = 20;

unsigned long lastTrigger = 0;

int lastDistance1 = 0;
int lastDistance2 = 0;
int currentOccupants = 0;
int activeSensor = 0;

void countingStateLoop() {
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
//  Serial.print("Distance 1 ");
//  Serial.println(distance1);
//  Serial.print("Distance 2 ");
//  Serial.println(distance2);

  // Beep when over capacity
  if (currentOccupants > maxOccupants) {
    tone(errorBeeperPin, NOTE_F);
  } else {
    noTone(errorBeeperPin);
  }

  if (shouldChange(lastDistance1, distance1)) {
    sensorChanged(1);
  } else if (shouldChange(lastDistance2, distance2)) {
    sensorChanged(2);
  }
  
  lastDistance1 = distance1;
  lastDistance2 = distance2;
}

void countingStateButtonChanged(int pin, int value) {
  
}

void personPassed(int count) {
  currentOccupants += count;
  if (currentOccupants < 0) {
    currentOccupants = 0;
  }
  activeSensor = 0;
  printOccupants();
  tone(beeperPin, count > 0 ? NOTE_A : NOTE_G_SHARP);
  delay(500);
  noTone(beeperPin);
}

void sensorChanged(int sensor) {
  Serial.print("Sensor changed ");
  Serial.println(sensor);
  if (shouldReset()) {
    activeSensor = 0;
  }
  if (activeSensor != sensor) {
    Serial.print("Sensor triggered ");
    Serial.println(sensor);
    lastTrigger = millis();
    if (activeSensor == 0) {
      activeSensor = sensor;
    } else {
      personPassed(sensor == 1 ? 1 : -1);
    }
  }
}

bool shouldReset() {
  return millis() - lastTrigger > triggerResetDelay;
}

bool shouldChange(int lastDistance, int distance) {
  return (lastDistance - distance > distanceToChange) && distance > 0;
}

void printOccupants() {
  Serial.print("Occupants (");
  Serial.print(currentOccupants);
  Serial.print("/");
  Serial.print(maxOccupants);
  Serial.println(")");
}

