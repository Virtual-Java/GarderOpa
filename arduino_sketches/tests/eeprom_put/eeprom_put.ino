#include <EEPROM.h>

void setup() {
  int iVal = 13823;  //Variable to store in EEPROM.
  int eeAddress = 0;   //Location we want the data to be put.
  
  Serial.begin(4800);
  while (!Serial) {
    //; // wait for serial port to connect. Needed for native USB port only
  }

  //One simple call, with the address first and the object second.
  EEPROM.put(eeAddress, iVal);

  Serial.println(iVal);
}

void loop() {  
  /* Empty loop */ 
}
 
