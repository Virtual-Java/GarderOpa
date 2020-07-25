#define COUNT_ROW  4  // number of rows
#define ROW_0   7
#define ROW_1   6
#define ROW_2   5
#define ROW_3   4

#define COUNT_COL  4  // number of columns
#define COL_0   0
#define COL_1   1
#define COL_2   2
#define COL_3   3

const byte row[] = {
  ROW_0, ROW_1, ROW_2, ROW_3
};
const byte col[] = {
  COL_0,COL_1, COL_2, COL_3
};


void setup() {
  Serial.begin(4800);
  while (!Serial) {
    //; // wait for serial port to connect. Needed for native USB port only
  }
}
unsigned int i = 0x01;
void loop() {
  digitalWriteScreen(i);
  i = (i << 1);
}


void digitalWriteScreen(int leds) { 
  // Turn on each row in series
  for (byte r = 7; r >= COUNT_ROW; r--) {                        // count next row
    // pinMode(r, OUTPUT);
    DDRA |= (1 << r);
    // digitalWrite(r, HIGH);                                 // initiate whole row
    PORTA |= (1 << r);
    for (byte c = 0; c < COUNT_COL; c++) {                      // count next column
      // pinMode(c, OUTPUT);
      DDRA |= (1 << c);
//      digitalWrite(c, LOW);                      // initiate whole column
      digitalWrite(col[c], ~((leds >> (r * 4 + c)) & 1));        // initiate whole column
      Serial.println(leds);
      // PORTA &= ~(1 << c);
      delay(200);
      // pinMode(c, INPUT);     // reset whole column
      DDRA &= ~(1 << c);
    }
    // pinMode(r, INPUT);     // reset whole row
    // digitalWrite(r, LOW);
    DDRA &= ~(1 << r);
    // PORTA &= ~(1 << r);
    // otherwise last row will intersect with next row
  }
}

void writeLed(byte led) {
  DDRA = 0x00;
  PORTA = 0x00;
  byte r = led / 4;
  byte c = led % 4;
  pinMode(row[r], OUTPUT);
  pinMode(col[c], OUTPUT);
  digitalWrite(row[r], HIGH);                              
  digitalWrite(col[c], LOW);
}

// 818 Bytes 39% ==> 554 Bytes 27%
// 17 Bytes 13% ==> 9 Bytes 7%
