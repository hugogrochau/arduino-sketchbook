#include "event_driven.h"

/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
/* Segment byte maps for numbers 0 to 9 */
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

#define ledPin0 10
#define ledPin1 11
#define ledPin2 12
#define ledPin3 13

#define button1Pin A1
#define button2Pin A2

int speed = 1;
int button1On = 0;
int button2On = 0;
int currentStatus = LOW;

void button1Changed() {
  Serial.print("button 1 changed");
  button1On = !button1On;
  speed++;
}

void button2Changed() {
  Serial.print("button 2 changed");
  button2On = !button2On;
  if (speed > 1) speed--;
}


void init_() {
    /* LED pins */
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  /* 7-seg */
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);

  button_listen(A1, button1Changed);
  button_listen(A2, button2Changed);

  timer_set(500);
}

void timer_expired() {
  switchLED();
  timer_set(1000/speed);
}

void printNumber(int number) {
  int place = 0;
  while (number > 0) {
    int digit = number % 10;
    WriteNumberToSegment(3 - place , digit);
    place++;
    number /= 10;
  }
}

void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO,LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO,HIGH);
}

void switchLED() {
  currentStatus = currentStatus == HIGH ? LOW : HIGH;  
  digitalWrite(ledPin0, currentStatus);
  digitalWrite(ledPin1, currentStatus);
  digitalWrite(ledPin2, currentStatus);
  digitalWrite(ledPin3, currentStatus);
}
