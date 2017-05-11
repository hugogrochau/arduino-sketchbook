#include "state.h"
#include "initial_state.h"
#include "notes.h"

void initialStateButtonChanged(int pin, int value) {
  if (value == HIGH) {
    switch (pin) {
      case addButton:
        tone(beeperPin, NOTE_A);
        maxOccupants++;
        printMaxOccupants();
        break;
      case subButton:
        if (maxOccupants > 0) {
          tone(beeperPin, NOTE_G_SHARP);
          maxOccupants--;
          printMaxOccupants();
        }
        break;
      case confirmButton:
        Serial.println("Controlling occupants...");
        tone(beeperPin, NOTE_C);
        delay(500);
        currentState = counting;
        noTone(beeperPin);
        break;
    }
  } else {
    noTone(beeperPin);
  }
}

void initialStateLoop() {
}

void printMaxOccupants() {
  Serial.print("Max occupants: ");
  Serial.println(maxOccupants);
}

