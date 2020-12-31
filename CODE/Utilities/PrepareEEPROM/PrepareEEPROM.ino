/*
 * PrepareEEPROM
 *
 * This is how we prepare the LEDLightSticks EEPROM for production
 * Set the boolean flags below and modify settings variables 
 * Be careful when overwriting the numWrites variable
 * Always set display_saved_settings to true when overwriting 
 * this will display what the settings were before they were overwritten
 */

#include <EEPROM.h>


const uint8_t display_saved_settings = true;

const uint8_t overwrite_saved_settings = false;

struct Settings {
    uint8_t animationIndex;
    uint8_t brightnessLevel;
    uint8_t paletteIndex;
    uint8_t solidColorIndex;
    uint8_t speedLevel;
};



uint8_t animationIndexVal = 0;
uint8_t brightnessIndexVal = 0;
uint8_t paletteIndexVal = 0;
uint8_t solidColorIndexVal = 0;
uint8_t speedIndexVal = 0;

const uint8_t overwrite_numWrites = false;
uint16_t numWrites = 0;


#define EEPROM_NUMWRITES_ADDR 31
#define EEPROM_ADDR_ANIMATION_INDEX 0
#define EEPROM_ADDR_BRIGHTNESS_INDEX 1
#define EEPROM_ADDR_PALETTE_INDEX 2
#define EEPROM_ADDR_SOLID_COLOR_INDEX 3
#define EEPROM_ADDR_SPEED_INDEX 4

const int lastSettingsAddress = EEPROM_NUMWRITES_ADDR + sizeof(numWrites) + EEPROM_ADDR_SPEED_INDEX;


// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

bool writeSettings = true;

Settings testSettings = {
  8,
  4,
  0,
  1,
  3
};



#define LEDS_01_PIN 13
#define LEDS_01_NUM_LEDS 34

// BUTTON DEFINITIONS
#define PRIMARY_BUTTON_PIN  11
#define SECONDARY_BUTTON_PIN  7




void setup() {

  pinMode(PRIMARY_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SECONDARY_BUTTON_PIN, INPUT_PULLUP);

  delay(100);
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {

  // this will display and/or overwrite saved settings
  if( address == EEPROM_NUMWRITES_ADDR + sizeof(numWrites) ){
    if(display_saved_settings){
//      displaySavedSettings(address);  
      displaySavedSettingsStruct(address);  
    }
    if(overwrite_saved_settings){
      overwriteSavedSettings();
    }    
  }
  // this will display and/or overwrite numWrites
  else if(address == EEPROM_NUMWRITES_ADDR){
    if(display_saved_settings){
      displayNumWrites(address);
    }
    if(overwrite_numWrites){
      overwriteNumWrites();
    }    
  }


  if(display_saved_settings && address >= EEPROM_NUMWRITES_ADDR && address <= lastSettingsAddress){
    // don't display anything because we're displaying the other stuff
  }
  else{
    displayCurrentAddress();
  }



  if(writeSettings){

    writeSettingsTest(38);
    writeSettings = false;
  }


  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }


  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  delay(250);
}


void displayCurrentAddress(){

  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);
  
  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();  
}




// WRITE SETTINGS STRUCT TEST
void writeSettingsTest(int addr){

  EEPROM.put(addr, testSettings);
  
}




// *********************************************************************************
//    DISPLAY SAVED SETTINGS STRUCT
// *********************************************************************************
//struct Settings {
//    uint8_t animationIndex;
//    uint8_t brightnessLevel;
//    uint8_t paletteIndex;
//    uint8_t solidColorIndex;
//    uint8_t speedLevel;
//};


void displaySavedSettingsStruct(int addr){

  byte val;
  Settings settings;
  
  Serial.println("**********************");
  Serial.println("READING SAVED SETTINGS");
  Serial.println();
  Serial.println("*************");

  EEPROM.get(addr, settings);



  //val = EEPROM.read(addr);

  Serial.println("ANIMATION Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(settings.animationIndex, DEC);
  Serial.println();
  Serial.println("*************");

  addr++;
  //val = EEPROM.read(addr);
  Serial.println("BRIGHTNESS Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(settings.brightnessLevel, DEC);
  Serial.println();
  Serial.println("*************");
  
  addr++;
//  val = EEPROM.read(addr);
  Serial.println("PALETTE Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(settings.paletteIndex, DEC);
  Serial.println();
  Serial.println("*************");

  addr++;
//  val = EEPROM.read(addr);
  Serial.println("SOLID COLOR Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(settings.solidColorIndex, DEC);
  Serial.println();
  Serial.println("*************");

  
  addr++;
//  val = EEPROM.read(addr);
  Serial.println("SPEED Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(settings.speedLevel, DEC);
  Serial.println();  
  Serial.println("*************");

  Serial.println("**********************");
  Serial.println();
}











// *********************************************************************************
//    DISPLAY SAVED SETTINGS
// *********************************************************************************
void displaySavedSettings(int addr){

  byte val;
  
  Serial.println("**********************");
  Serial.println("READING SAVED SETTINGS");
  Serial.println();
  Serial.println("*************");

  val = EEPROM.read(addr);

  Serial.println("ANIMATION Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(val, DEC);
  Serial.println();
  Serial.println("*************");

  addr++;
  val = EEPROM.read(addr);
  Serial.println("BRIGHTNESS Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(val, DEC);
  Serial.println();
  Serial.println("*************");
  
  addr++;
  val = EEPROM.read(addr);
  Serial.println("PALETTE Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(val, DEC);
  Serial.println();
  Serial.println("*************");

  addr++;
  val = EEPROM.read(addr);
  Serial.println("SOLID COLOR Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(val, DEC);
  Serial.println();
  Serial.println("*************");

  
  addr++;
  val = EEPROM.read(addr);
  Serial.println("SPEED Index: ");
  Serial.print("addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(val, DEC);
  Serial.println();  
  Serial.println("*************");

  Serial.println("**********************");
  Serial.println();
}


// *********************************************************************************
//    OVERWRITE SAVED SETTINGS
// *********************************************************************************

void overwriteSavedSettings(){

  Serial.println("*************************************");

  Serial.println("   OVERWRITING SETTINGS VARIABLES");
  Serial.println();
  Serial.print("Settings Var - ");  
  Serial.print("\t");
  Serial.print("addr");
  Serial.print("\t");
  Serial.print("val");
  Serial.println();

  int animationAddr   = EEPROM_NUMWRITES_ADDR + sizeof(numWrites) + EEPROM_ADDR_ANIMATION_INDEX;
  int brightnessAddr  = EEPROM_NUMWRITES_ADDR + sizeof(numWrites) + EEPROM_ADDR_BRIGHTNESS_INDEX;
  int paletteAddr     = EEPROM_NUMWRITES_ADDR + sizeof(numWrites) + EEPROM_ADDR_PALETTE_INDEX;
  int solidColorAddr  = EEPROM_NUMWRITES_ADDR + sizeof(numWrites) + EEPROM_ADDR_SOLID_COLOR_INDEX;
  int speedAddr       = EEPROM_NUMWRITES_ADDR + sizeof(numWrites) + EEPROM_ADDR_SPEED_INDEX;
  
  // overwrite animation index
  EEPROM.write(animationAddr, animationIndexVal);
  Serial.print("Animation - ");  
  Serial.print("\t");
  Serial.print(animationAddr);
  Serial.print("\t");
  Serial.print(animationIndexVal);
  Serial.println();

  // overwrite brightness index
  EEPROM.write(brightnessAddr, brightnessIndexVal);
  Serial.print("Brightness - ");  
  Serial.print("\t");
  Serial.print(brightnessAddr);
  Serial.print("\t");
  Serial.print(brightnessIndexVal);
  Serial.println();



  // overwrite palette index
  EEPROM.write(paletteAddr, paletteIndexVal);
  Serial.print("Palette - ");  
  Serial.print("\t");
  Serial.print(paletteAddr);
  Serial.print("\t");
  Serial.print(paletteIndexVal);
  Serial.println();

  // overwrite palette index
  EEPROM.write(solidColorAddr, solidColorIndexVal);
  Serial.print("Palette - ");  
  Serial.print("\t");
  Serial.print(solidColorAddr);
  Serial.print("\t");
  Serial.print(solidColorIndexVal);
  Serial.println();

  
  // overwrite speed index
  EEPROM.write(speedAddr, speedIndexVal);
  Serial.print("Speed - ");  
  Serial.print("\t");
  Serial.print(speedAddr);
  Serial.print("\t");
  Serial.print(speedIndexVal);
  Serial.println();



  Serial.println("*************************************");

  
}



// *********************************************************************************
//    DISPLAY NUM WRITES
// *********************************************************************************
void displayNumWrites(int addr){

  Serial.println();
  Serial.println("*************************************");
  Serial.println("READING NUMWRITES");

  // EEPROM.get(addr, variable) will read all necessary bytes for the "variable" passed in
  // it does this based on the number of bytes that variable's type requires
  // in our numWrites (which is a 2 byte uint16_t) will grab 2 bytes of data and convert to uint16_t
  
  uint16_t val;
  EEPROM.get(addr, val);

  Serial.print("Number of writes so far: ");
  Serial.print(val);
  Serial.println();
  Serial.println();

  // EEPROM.read(addr) will get a single byte at the given address
  // this is the LSB of numWrites (which is a 2 byte uint16_t)
  byte firstByte = EEPROM.read(addr);
  
  Serial.print("Byte 1 (lsb) - addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print("               ");
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(firstByte, DEC);
  Serial.println();

  addr++;
  // EEPROM.read(addr) will get a single byte at the given address
  // this is the MSB of numWrites (which is a 2 byte uint16_t)  
  byte secondByte = EEPROM.read(addr);
  
  Serial.print("Byte 2 (msb) - addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print("               ");
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(secondByte, DEC);
  Serial.println();

  Serial.println("*************************************");
  
}



// *********************************************************************************
//    OVERWRITE NUM WRITES
// *********************************************************************************
void overwriteNumWrites(){


  // EEPROM.put(addr, variable) will write all necessary bytes for the "variable" passed in
  // it does this based on the number of bytes that variable's type requires
  // in our numWrites (which is a 2 byte uint16_t) will convert uint16_t to 2 bytes of data and save it in 2 bytes of EEPROM
  EEPROM.put(EEPROM_NUMWRITES_ADDR, numWrites);

  Serial.println();
  Serial.println("*************************************");
  Serial.println("OVERWRITING NUMWRITES");
  Serial.print("numWrites is now set to: ");
  Serial.print(numWrites);
  Serial.println();

    // EEPROM.read(addr) will get a single byte at the given address
  // this is the LSB of numWrites (which is a 2 byte uint16_t)
  byte firstAddr = EEPROM_NUMWRITES_ADDR;
  byte firstByte = EEPROM.read(firstAddr);
  
  Serial.print("Byte 1 (lsb) - addr");
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print("               ");
  Serial.print(firstAddr);
  Serial.print("\t");
  Serial.print(firstByte, DEC);
  Serial.println();

  // EEPROM.read(addr) will get a single byte at the given address
  // this is the MSB of numWrites (which is a 2 byte uint16_t)  
  byte secondAddr = EEPROM_NUMWRITES_ADDR + 1;
  byte secondByte = EEPROM.read(secondAddr);
  
  Serial.print("Byte 2 (msb) - addr");  
  Serial.print("\t");
  Serial.print("val");
  Serial.println();
  Serial.print("               ");
  Serial.print(secondAddr);
  Serial.print("\t");
  Serial.print(secondByte, DEC);
  Serial.println();

  Serial.println("*************************************");
  
}
