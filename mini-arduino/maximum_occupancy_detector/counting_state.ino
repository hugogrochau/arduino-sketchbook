#include "counting_state.h"
#include "notes.h"

const unsigned long sampleInterval = 250;
const int distanceChangeToTrigger = 15;

unsigned long lastSample = 0;

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
  } else {
    if (millis() - sampleInterval > lastSample) {
      bool sensor1Triggered = lastDistance1 - distance1 > distanceChangeToTrigger;
      bool sensor2Triggered = lastDistance2 - distance2 > distanceChangeToTrigger;
      if (sensor1Triggered || sensor2Triggered) {
        if (sensor1Triggered) {
          sensor1Changed();
        } else {
          sensor2Changed();
        }

      } else {
        noTone(beeperPin);
      }
      
        lastDistance1 = distance1;
        lastDistance2 = distance2;
        lastSample = millis();
        

    } 
  }


}

void countingStateButtonChanged(int pin, int value) {
  
}

void sensor1Changed() {
  if (activeSensor == 2) {
    currentOccupants++;
    activeSensor = 0;
    tone(beeperPin, NOTE_A);
    printOccupants();
  } else {
    activeSensor = 1;
  }
}

void sensor2Changed() {
  if (activeSensor == 1 && currentOccupants > 0) {
    currentOccupants--;    
    activeSensor = 0;
    tone(beeperPin, NOTE_G_SHARP);
    printOccupants();
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

