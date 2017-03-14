

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 10; i < 14; i++) {
    digitalWrite(i, HIGH);   
    delay(1000);
    digitalWrite(i, LOW);
    delay(1000); 
  }
}
