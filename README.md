# GarderOpa
A Happy Birthday playing wardrobe for my grandpa (ger: Garderobe &amp; Opa) realized with ATtiny24

I made this GarderOpa because my Grandpa likes to cut power cords in two pices. Afterwards he gives me the plugs as a present and tells me: "Certainly you can use this". His words allways are sounding like the cutted plugs are very valuable. But the only thing you could do with them is to build a Wardrobe (in german: “Garderobe”).
So I built this wardrobe to give it to my grandfather on his 80th birthday with the words: "Certainly you can use this".
If you have some old cables with plugs too, feel free to make your own wardrobe based on my project.

The main challenge of this project was to get all the functions needed to drive 13 LEDs and to play the whole Happy Birthday melody into the small flash of ATtiny24.
You would say why don't you use a ATtiny44, ATtiny84 or even a ATmega controller?

  • Firstly I just had a ATtiny24 laying around.
  
  • Secondly a ATtiny24 you can get for around 1€ / 1$ or less (smd versions) while bigger controllers are a little bit more expensive.
  
  • Thirdly my prototyping pcb only had around 5 x 7,5 cm (2 x 3 inches) so space was rare, so ATmega controllers were to big.
  
  • At last I didn't know that debug of micro-controllers without any hardware serial uart interface is not reliable (Could only send one integer value without additionally strings). In the same way the flash program memory is very small on ATtiny24. Consequently I reached the limit with only a few code lines with subfunctions. Therefore it is better to use the ATtiny44/84 when price is less important. For cost sensitive applications this project shows how to use eeprom to allocate flash memory, which is normaly used for tasks like storing constant data.

In this project I used the ATtiny core of SpenceKonde and got inspired by the “happybirthday" sketch of Robson Couto.

For more information about the ATtiny core see SpenceKode's repository:  
https://github.com/SpenceKonde/ATTinyCore

Further songs can be downloaded from robsoncouto's repository:  
https://github.com/robsoncouto/arduino-songs


Usage:

  * Solder the compounents on a pcb or similar like described in the example circuit (breadboards are not recommanded cause of their capacities between contacts and lose connections).
  * Download Arduino IDE and install the ATTiny core of SpenceKonde via Boardmanager.
  * Test your Hardware via the programs in test folder or your own programs.
  * Use the sketch "write_songs_to_eeprom" to put the data in the eeprom.
  * Upload the sketch "GarderOpa" to see if the buzzer plays "Happy Birthday" while some LEDs light up. Compare your result with mine like shown in the short video.
  * Feel free to modify the soft- / hardware to fit your imaginations. If something doesn't function as expected, write a simple test routine or undo your changes until the point where it still functioned.

[front](pictures/GarderOpa_front.jpg?raw=true "My wardrobe "GarderOpa" from the front")

[side](pictures/GarderOpa_side.jpg?raw=true "My wardrobe "GarderOpa" from the side")

[Video to show how my wardrobe "GarderOpa" functions](pictures/GarderOpa_video.mp4)
