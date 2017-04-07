#include "counting_state.h"
#include "notes.h"

const unsigned long sampleInterval = 500;
const int distanceChangeToTrigger = 15;

unsigned long lastSample = 0;

int lastDistance1 = 0;
int lastDistance2 = 0;
int currentOccupants = 0;

void countingStateLoop() {
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);

  // first run
  if (!lastDistance1 || !lastDistance2) {
    lastDistance1 = distance1;
    lastDistance2 = distance2;
  } else {
    if (millis() - sampleInterval > lastSample) {
      if (lastDistance1 - distance1 > distanceChangeToTrigger) {
        sensor1Changed();
      } else if (lastDistance2 - distance2 > distanceChangeToTrigger) {
        sensor2Changed();
      } else {
        noTone(beeperPin);
      }
        lastDistance1 = distance1;
        lastDistance2 = distance2;
        lastSample = millis();
        
        // Prints the distance on the Serial Monitor
        Serial.print("Distance 1: ");
        Serial.println(distance1);
        // Prints the distance on the Serial Monitor
        Serial.print("Distance 2: ");
        Serial.println(distance2);
        printOccupants();
    } 
  }


}

void countingStateButtonChanged(int pin, int value) {
  
}

void sensor1Changed() {
  tone(beeperPin, NOTE_A);
  currentOccupants++;
}

void sensor2Changed() {
  tone(beeperPin, NOTE_G_SHARP);
  currentOccupants--;
}

void printOccupants() {
  Serial.print("Occupants (");
  Serial.print(currentOccupants);
  Serial.print("/");
  Serial.print(maxOccupants);
  Serial.println(")");
}

