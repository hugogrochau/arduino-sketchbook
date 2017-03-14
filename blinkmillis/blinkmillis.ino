// constants won't change. Used here to set a pin number :

#define ledPin0 10
#define ledPin1 11
#define ledPin2 12
#define ledPin3 13

#define buttonPin A2
unsigned long lastTime = 0;
int currentStatus = HIGH;

void setup() {
  // set the digital pin as output:
  Serial.begin(9600);      // open the serial port at 9600 bps:    
  pinMode(ledPin0, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  unsigned long time = millis();

  if (time > lastTime + 1000) {
    currentStatus = currentStatus == HIGH ? LOW : HIGH;  
    digitalWrite(ledPin0, currentStatus);
    lastTime = millis();
  }
}
