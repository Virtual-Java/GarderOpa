void setup() {
  Serial.begin(4800);
  while (!Serial) {
    //; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(A3, INPUT);
  digitalWrite(A3, HIGH);
  pinMode(A4, OUTPUT);
  digitalWrite(A4, LOW);
}

void loop() {
  Serial.println(analogRead(A3));
  delay(200);
}
