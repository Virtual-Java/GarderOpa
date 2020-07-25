#include <EEPROM.h>           // library to read from and write to the microcontrollers builtin persistent eeprom memory: https://www.arduino.cc/en/Reference/EEPROM
// only needed in IDE versions below 1.0 (2011)
// #include <avr/pgmspace.h>  // library to store data in flash (program) memory instead of SRAM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
// The core used in this project is ATTinyCore of SpenceKonde:  https://github.com/SpenceKonde/ATTinyCore

// 68 bytes of sram must be reserved for debug via software serial otherwise there will be no/incorrect output (67 bytes are not enough)
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


// Enter here the songs to save in eeprom
static const PROGMEM int data[] = {
  NOTE_C5,4, NOTE_C5,8, 
  NOTE_D5,-4, NOTE_C5,-4, NOTE_F5,-4,
  NOTE_E5,-2, NOTE_C5,4, NOTE_C5,8, 
  NOTE_D5,-4, NOTE_C5,-4, NOTE_G5,-4,
  NOTE_F5,-2, NOTE_C5,4, NOTE_C5,8,

  NOTE_C6,-4, NOTE_A5,-4, NOTE_F5,-4, 
  NOTE_E5,-4, NOTE_D5,-4, NOTE_AS5,4, NOTE_AS5,8,
  NOTE_A5,-4, NOTE_F5,-4, NOTE_G5,-4,
  NOTE_F5,-2,
};

int Val = 0;
int Adr = 0;

void setup() {
  byte address = 0;
  unsigned int wholenote = (6000 * 4);
  int divider = 0;
  int noteDuration = 0;
  int frequency = 0;
  
  for(byte thisNote = address; thisNote < (sizeof(data) + address); thisNote += (sizeof(int) * 2)) {
    // calculates the duration of each note
    divider = pgm_read_word_near(data + ((thisNote / sizeof(int)) + 1));
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote / divider);
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote / abs(divider) / 2 * 3); // increases the duration in half for dotted notes
    }
    EEPROM.put(thisNote + sizeof(int), noteDuration);
    unsigned int frequency = pgm_read_word_near(data + (thisNote / sizeof(int)));
    EEPROM.put(thisNote, frequency);
    delay(50);       // Wait until the eeprom is ready for new data
  }
  // uncomment the following lines to debug via software serial (TX is AIN0/PA1, RX is AIN1/PA2)
  // initialize serial and wait for port to open:
  delay(2000);
    
  Serial.begin(4800);
  while (!Serial) {
    //; // wait for serial port to connect. Needed for native USB port only
  }
    
}

void loop() {
 // read a byte from the current address of the EEPROM
  
  EEPROM.get(Adr, Val);
  delay(20);
//  Serial.print("A: ");
  Serial.println(Val);
//  Serial.print(Adr,DEC); // more than one Serial.print(integer) does not function on ATtinys with SoftwareSerial -- Why?
//  Serial.print('\t');
//  Serial.println(Val, DEC);
//  Serial.println();

  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  Adr += sizeof(Val);   //Increment cursor by two
  if (Adr >= EEPROM.length()) {
    Adr = 0;
  }
 
  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  delay(200);
}
// The output of serial monitor should look like:
/*
0
262
6000
262
3000
294
9000
262
9000
349
9000
330
18000
262
6000
262
3000
294
9000
262
9000
392
9000
349
18000
262
6000
262
3000
523
9000
440
9000
349
9000
330
9000
294
9000
466
6000
466
3000
440
9000
349
9000
392
9000
349
18000
0
0
0

*/
