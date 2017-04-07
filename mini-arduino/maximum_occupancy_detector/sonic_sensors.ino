// defines pins numbers
const int trigPins[2] = {10, 6};
const int echoPins[2] = {9, 5};

int getDistance(int i) {
  // Clears the trigPin
  digitalWrite(trigPins[i], LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPins[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[i], LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(echoPins[i], HIGH);
  // Calculating the distance
  return duration*0.034/2;
}

void setup() {
  pinMode(trigPins[0], OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPins[0], INPUT); // Sets the echoPin as an Input 
  pinMode(trigPins[1], OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPins[1], INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {

  int distance1 = getDistance(0);
  int distance2 = getDistance(1);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 2: ");
  Serial.println(distance2);
}
