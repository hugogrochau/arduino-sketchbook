#include "state.h"
#include "initial_state.h"
#include "notes.h"

void initialStateButtonChanged(int pin, int value) {
  if (value == HIGH) {
    switch (pin) {
      case addButton:
        tone(beeperPin, NOTE_A);
        maxOccupants++;
        break;
      case subButton:
        if (maxOccupants > 0) {
          tone(beeperPin, NOTE_G_SHARP);
          maxOccupants--;
        }
        break;
      case confirmButton:
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
  if (maxOccupants == 0) {
    Serial.println("Enter max occupants");
  } else {
    Serial.print("Max occupants: ");
    Serial.println(maxOccupants);
  }
}
