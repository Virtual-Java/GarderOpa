float base = 1.0594631;

void setup() {
Serial.begin(9600);
}

void loop() {
delay(2000);
  for(int n = 0; n < 64; n++) {
    Serial.println(pow(base, n) * 110);
    //float note = (pow(base, n) * 110);
  }
}
