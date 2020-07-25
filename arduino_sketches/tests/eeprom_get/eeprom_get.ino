/***
    eeprom_get example.

    This shows how to use the EEPROM.get() method.

    To pre-set the EEPROM data, run the example sketch eeprom_put.
    This sketch will run without it, however, the values shown
    will be shown from what ever is already on the EEPROM.

    This may cause the serial object to print out a large string
    of garbage if there is no null character inside one of the strings
    loaded.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

#include <EEPROM.h>

void setup() {
  int iVal = 0;       //Variable to store data read from EEPROM.
  int eeAddress = 0;  //EEPROM address to start reading from

  Serial.begin(4800);
  while (!Serial) {
    //; // wait for serial port to connect. Needed for native USB port only
  }

  //Get the float data from the EEPROM at position 'eeAddress'
  EEPROM.get(eeAddress, iVal);
  
  Serial.println(iVal);    //This may print 'ovf, nan' if the data inside the EEPROM is not a valid float.
}

void loop() {
  /* Empty loop */
}
