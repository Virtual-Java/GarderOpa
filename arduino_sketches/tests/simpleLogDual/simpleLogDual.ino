void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {
  char data[30];
  int result = 1;
  for(int i = 0; i <= 8; i++){
    int logData = simpleLogDual(result);
    sprintf(data, "result: %d; logData: %d", result, logData);
    Serial.println(data);
    result = 2 * result;
  }
}


// calculate logarithm from powers of two: 2^n = x  ∩  n ∈ ℕ
int simpleLogDual(int x) {
  int i = 0;
  while(0 == ((x >> i) & 1) && i < 8) {
    i++;
  }
  return i;
}
