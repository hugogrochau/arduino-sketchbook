#include "counting_state.h"
#include "notes.h"

const unsigned long triggerResetDelay = 1500;

unsigned long lastTrigger = 0;

int currentOccupants = 0;
int activeSensor = 0;

int lastDistance1 = 0;
int lastDistance2 = 0;

int numSamples = 5;
int currentSample = 0;
int distance1 = 0;
int distance2 = 0;
int distanceToChange = 10;

void countingStateLoop() {
  int sampleDistance1 = getDistance(trigPin1, echoPin1);
  delayMicroseconds(20);
  int sampleDistance2 = getDistance(trigPin2, echoPin2);
  if (currentSample < numSamples) {
    distance1 += sampleDistance1/numSamples;
    distance2 += sampleDistance2/numSamples;
    currentSample++;
    return;
  }
  Serial.print("Distance 1 ");
  Serial.println(distance1);
  Serial.print("Distance 2 ");
  Serial.println(distance2);
  Serial.print("Distance to change ");
  Serial.println(distanceToChange);

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
  distance1 = 0;
  distance2 = 0;
  currentSample = 0;
}

void countingStateButtonChanged(int pin, int value) {
    if (value == HIGH) {
    switch (pin) {
      case addButton:
        distanceToChange += 5;
        tone(beeperPin, NOTE_A);
        delay(200);
        noTone(beeperPin);
        break;
      case subButton:
        if (distanceToChange > 10) {
          distanceToChange -= 5;
          tone(beeperPin, NOTE_G_SHARP);
          delay(200);
          noTone(beeperPin);
        }
        break;
    }
  }
}

void personPassed(int count) {
  currentOccupants += count;
  if (currentOccupants < 0) {
    currentOccupants = 0;
  }
  printOccupants();
  tone(beeperPin, count > 0 ? NOTE_A : NOTE_G_SHARP);
  delay(500);
  noTone(beeperPin);
  lastTrigger = 0;
}

void sensorChanged(int sensor) {
  Serial.print("Sensor changed ");
  Serial.println(sensor);
  if (shouldReset()) {
    Serial.println("Trigger reset");
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

