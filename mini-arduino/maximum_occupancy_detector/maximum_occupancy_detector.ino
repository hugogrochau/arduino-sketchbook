#include "event_driven.h"

#define SENSOR1 1
#define SENSOR2 2

void sensorChanged(int pin, int v) {
  timerSet(500);
}

void init_() {
  /* 7-seg */
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);

  sensorListen(A1);
  sensorListen(A2);
}

void timerExpired() {

}

