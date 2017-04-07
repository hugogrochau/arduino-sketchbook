#include "counting_state.h"

void countingStateLoop() {
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 2: ");
  Serial.println(distance2);
}

void countingStateButtonChanged(int pin, int value) {
  
}

