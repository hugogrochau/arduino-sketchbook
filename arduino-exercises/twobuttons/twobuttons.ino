
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

unsigned long lastLEDSwitchTime = 0;
unsigned long lastButton1PressTime = 0;
unsigned long lastButton2PressTime = 0;

int button1Active = 0;
int button2Active = 0;

int currentStatus = HIGH;

int speed = 1;

int stopped = 0;

void setup() {
  /* LED pins */
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  /* 7-seg */
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);

  /* Button pins */
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}

void loop() {
  unsigned long time = millis();

  checkButtons(time);

  if (!stopped) {
    if (time > lastLEDSwitchTime + 1000/speed) {
      switchLED();
      lastLEDSwitchTime = millis();
    }
    printNumber(speed);
  } else {
    printNumber(0);
  }

  if (button1Active && button2Active) {
    stopped = !stopped;
  } else if (button1Active) {
    speed++;
  } else if (button2Active) {
    speed--;
  }
}

void checkButtons(int time) {

  int button1Pressed = !digitalRead(button1Pin);
  int button2Pressed = !digitalRead(button2Pin);

  if (time > lastButton1PressTime + 500) {
    if (button1Pressed) {
      button1Active = 1;
      lastButton1PressTime = millis();
    } else {
      button1Active = 0;
    }
  }

  if (time > lastButton2PressTime + 500) {
    if (button2Pressed) {
      button2Active = 1;
      lastButton2PressTime = millis();
    } else {
      button2Active = 0;
    }
  }
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

