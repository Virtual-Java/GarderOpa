#include <EEPROM.h>

// when using an ATtiny24 disable millis()/micros() to save flash

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

#ifdef PINMAPPING_CCW

  #define ROW_0   3
  #define ROW_1   4
  #define ROW_2   5
  #define ROW_3   6
  
  #define COL_0   10
  #define COL_1   9
  #define COL_2   8
  #define COL_3   7

  #define PHOTO  A3    // pin where the phototransistor is attached to
  #define MICRO  A7    // pin where the microphone is attached to
  #define PIEZO   2    // pin where the piezo speaker is attached to

#else // ifdef PINMAPPING_CW*/

  #define ROW_0   7
  #define ROW_1   6
  #define ROW_2   5
  #define ROW_3   4
  
  #define COL_0   0
  #define COL_1   1
  #define COL_2   2
  #define COL_3   3

  #define PHOTO  A3    // pin where the phototransistor is attached to
  #define MICRO  A7    // pin where the microphone is attached to
  #define PIEZO   8    // pin where the piezo speaker is attached to
  
#endif

  #define COUNT_ROW  4  // number of rows
  #define COUNT_COL  4  // number of columns
  
  #define REF_VAL 400  // reference value: value greater than this value will turn the LED on

/* 
  Happy Birthday
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#define HAPPY_BIRTHDAY   1  // index of the song


const byte row[] = {
  ROW_0, ROW_1, ROW_2, ROW_3
};
const byte col[] = {
  COL_0,COL_1, COL_2, COL_3
};

bool LedState = 0;

void setup() 
{
  playMusik(HAPPY_BIRTHDAY);
}

void loop() {
  darknessDetect();
}

void switchLight() {
  byte countCol = 4;
  // Turn on each row in series
  for (byte r = 7; r >= 4; r--) {                       // count next row
    // pinMode(r, OUTPUT);
    DDRA |= (1 << r);
    // digitalWrite(r, HIGH);                           // initiate whole row
    PORTA |= (1 << r);
    if(4 == r) {
      countCol = 1;
    }
    for (byte c = 0; c < countCol; c++) {               // count next column
      // pinMode(c, OUTPUT);
      DDRA |= (1 << c);
      // digitalWrite(c, LOW);                          // initiate whole column
      PORTA &= ~(1 << c);
      delay(100);
      // pinMode(c, INPUT);                             // reset whole column
      DDRA &= ~(1 << c);
    }
    // pinMode(r, INPUT);                               // reset whole row
    DDRA &= ~(1 << r);
    // digitalWrite(r, LOW);
    // PORTA &= ~(1 << r);
  }
  /*
   * direct writing to the registers saves a lot of memory:
   * flash:  818 Bytes 39% ==> 554 Bytes 27%
   * sram:   17 Bytes 13% ==> 9 Bytes 7%
   */
}

void writeLeds(int leds) { 
  // Turn on each row in series
  for (byte r = 0; r < COUNT_ROW; r++) {                        // count next row
    pinMode(row[r], OUTPUT);
    digitalWrite(row[r], HIGH);                              // initiate whole row
    for (byte c = 0; c < COUNT_COL; c++) {                    // count next column
      digitalWrite(col[c], ~(leds >> (r * 4 + c) & 0x01));        // initiate whole column      
      digitalWrite(col[c], 1);      // reset whole column
    }
    digitalWrite(row[r], LOW);     // reset whole row
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

void playMusik(byte song) {
  unsigned int led = 0x01;
  byte address = 0;    // use datatype int for controllers with eeprom sizes greater than 256 Bytes
  byte tempo = 140;
  byte notes = EEPROM.length();     // number of notes used in this Song
  switch(song) {
    case HAPPY_BIRTHDAY:
      tempo = 140;
      address = 0;    // start index for the song happy birthday
      notes = 25;     // number of notes used in this Song
      break;
  }
  int noteDuration = 0;
  int frequency = 0;
    // iterate over the notes of the melody.
  for (byte thisNote = address; thisNote < ((notes * 4) + address); thisNote += (sizeof(int) * 2)) {
    // calculates the duration of each note
    EEPROM.get((thisNote + sizeof(int)), noteDuration);   // read the notes of the song stored in eeprom
    EEPROM.get(thisNote, frequency);
    writeLed(led);
    if(led < 13) {
      led += 1;
    } else {
      led = 0;
    }
    tone(PIEZO, frequency, (noteDuration / tempo * 9));                      // we only play the note for 90% of the duration, leaving 10% as a pause
    delay((noteDuration / tempo * 10));                                      // wait for the specief duration before playing the next note.
    noTone(PIEZO);                                                           // stop the waveform generation before the next note.
  }
}

void switchLED(byte brightness) {
  if(0 == brightness) {
    pinMode(COL_1, INPUT);
  } else {
    pinMode(COL_1, OUTPUT);
    digitalWrite(COL_1, LOW);
    digitalWrite(ROW_3, brightness);
    // analogWrite(ROW_3, brightness);
  }
}

void darknessDetect()
{
  pinMode(PHOTO, INPUT_PULLUP);
  pinMode(ROW_3, OUTPUT);
  digitalWrite(ROW_3, LOW);
  if(REF_VAL < analogRead(A3)) {                                                          
    switchLED(HIGH);
  } else {
    switchLED(LOW);
  }
    
}
