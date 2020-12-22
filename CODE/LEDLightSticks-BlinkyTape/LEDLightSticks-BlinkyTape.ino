// August 27th, 2018
// One strip with two buttons. Strip can be reversed with a "true" in the final member of the constructor
// Button one controlls current animation and brightness
// Button two controlls palette choice
// added some new animations that work with palettes
//
#include "FastLED.h"
#include "ring.h"
#include "dot.h"
#include <JC_Button_old.h>

FASTLED_USING_NAMESPACE


#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif


// ****************** CONSTANT DEFINED VARIABLES ********************
//
// ******************************************************************

//trinket pro pins
/*
#define DATA_PIN_BIKE_CENTER_STRIP    10
#define DATA_PIN_BIKE_SIDE_STRIP   11
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  A1
#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  A2

#define PULLUP              false // these should be true for kevin's button setup
#define INVERT              false // these should be true for kevin's button setup

*/

//Blinky Tape Pins

#define DATA_PIN_BIKE_CENTER_STRIP    13
//#define DATA_PIN_BIKE_SIDE_STRIP   11

// Use these for strip with 2 buttons
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  11
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE_backup  10

#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  7

// Use these for strip with 1 button
//#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  10
//#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  11

#define PULLUP              true // these should be true for kevin's button setup
#define INVERT              true // these should be true for kevin's button setup



//Teensy pins
/*
#define LED_ENABLE_PIN 7
#define DATA_PIN_BIKE_CENTER_STRIP    11
#define DATA_PIN_BIKE_SIDE_STRIP   13
#define BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE  22
#define BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE  21

#define PULLUP              true // these should be true for kevin's button setup
#define INVERT              true // these should be true for kevin's button setup

*/

#define LED_TYPE NEOPIXEL

#define NUM_LEDS_BIKE_CENTER_STRIP  34 // 92 for Kevin's Purposes and the staff
//#define NUM_LEDS_BIKE_SIDE_STRIP  0   // 92 for Kevin's Purposes and the staff

//#define NUM_LEDS_BIKE_TOTAL (NUM_LEDS_BIKE_CENTER_STRIP + NUM_LEDS_BIKE_SIDE_STRIP)
#define NUM_LEDS_BIKE_TOTAL NUM_LEDS_BIKE_CENTER_STRIP

//#define INITIAL_BRIGHTNESS          40 //start with low brightness for Kevin's wack wiring sake (kidding kevin)
#define INITIAL_BRIGHTNESS          60 
#define BRIGHTNESS_INCREMENT          20 
#define BRIGHTNESS_MAX_MODULO          180 // 


#define DEBOUNCE_MS         20
#define LONG_PRESS          1000

#define FRAMES_PER_SECOND  120

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

//BEGIN ******* FIRE ANIMATION GLOBAL VARIABLES ********
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120



//PartyColors is the Instagram palette
//CRGBPalette16 gPal(LavaColors_p);
CRGBPalette16 gPal(HeatColors_p);
//CRGBPalette16 gPal(CloudColors_p);
//CRGBPalette16 gPal(PartyColors_p);

//END ******* FIRE ANIMATION GLOBAL VARIABLES ********

Button button_BikeCenterStrip_and_BrightnessChange(BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE, PULLUP, INVERT, DEBOUNCE_MS);
Button button_BikeCenterStrip_and_BrightnessChange_backup(BUTTON_PIN_BIKE_CENTER_STRIP_AND_BRIGHTNESS_CHANGE_backup, PULLUP, INVERT, DEBOUNCE_MS);

Button button_BikeSideStrip_and_PaletteChange(BUTTON_PIN_BIKE_SIDE_STRIP_AND_PALETTE_CHANGE, PULLUP, INVERT, DEBOUNCE_MS);




//enum {SHOW_PATTERN, TO_CHANGE_BRIGHTNESS, CHANGE_BRIGHTNESS, TO_SHOW_PATTERN};

enum {SHOW_PATTERN, TO_CHANGE_BRIGHTNESS, CHANGE_BRIGHTNESS, TO_CHANGE_PALETTE, CHANGE_PALETTE, TO_SHOW_PATTERN};


// ******************************************************************
// ******************************************************************
// **************** BEGINNING OF LED STRIP CLASS ********************
// ******************************************************************
// ******************************************************************
class LEDStripSegment
{
  public:
  
    CRGB *ledStrip;

//    uint16_t* ledOrder;

    uint8_t STATE = 0;
    
    CRGB brightnessDemoColor = CRGB::Blue;
    
    uint16_t numPixelsInStrip;
    uint16_t ledStripStartIndex;

    bool gReverseDirection = false;

    unsigned long lastPatternUpdateTime = 0; // time of last update of the pattern
    unsigned long lastHueUpdateTime = 0;  
    unsigned long lastCycleUpdateTime = 0;
  
    unsigned long patternUpdateInterval = 0;   // milliseconds between updates. Likely needs to be 5
    unsigned long hueUpdateInterval = 10;
    unsigned long fireUpdateInterval = 15;
    unsigned long cycleUpdateInterval = 10000;
    
    typedef void (LEDStripSegment::*AnimationsList[13])(); // make sure to update the number (currently 11) when adding animations to the structure below
  
    AnimationsList gPatterns = { &LEDStripSegment::rainbow, 
                                 &LEDStripSegment::rainbowWithGlitter,
                                 &LEDStripSegment::confetti,
                                 //&LEDStripSegment::patrioticConfetti,
                                 &LEDStripSegment::paletteConfetti,
                                 &LEDStripSegment::sinelon,
                                 &LEDStripSegment::sinelon2,
                                 &LEDStripSegment::juggle,
                                 &LEDStripSegment::gearDots,
                                 &LEDStripSegment::bpm, 
                                 &LEDStripSegment::FillLEDsFromPaletteColors,
                                 &LEDStripSegment::fire2012WithPalette, // always must be third to last
                                 &LEDStripSegment::cycle, //this animation always must be second to last
                                 &LEDStripSegment::fadeToBlack};
    
    //Need to add a list of palettes to cycle though here            
    CRGBPalette16 gPalettes;

    uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
    uint8_t gCurrentPaletteNumber = 0; // Index number of which palette is current
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns

    uint8_t cycleFunctionPatternIndex = 0;
    

// GEAR DOTS
    Ring *r1;
    Ring *r2;

    Dot *d1;
    Dot *d2;
    Dot *d3;
    Dot *d4;
    Dot *d5;
    Dot *d6;
    Dot *d7;
    Dot *d8;
    
    Dot *dots;
// GEAR DOTS

//START **** FIRE ANIMATION CLASS VARIABLE
    // Array of temperature readings at each simulation cell
    // Since this is in a class now, the heat array has been declared as a class member
    byte *heat;
//END **** FIRE ANIMATION CLASS VARIABLE


  // ******************************************************************    
  //                         CONSTRUCTOR                     
  // ******************************************************************
  LEDStripSegment(CRGB *leds, CRGBPalette16 pPalettes, uint16_t pLedStripStartIndex, uint16_t pLedStripEndIndex, bool reverseTheLEDConfiguration = false)
  {

//  LEDStripSegment ledStrip_bike_center(&(leds_bike_center[0]), gPal, 0, NUM_LEDS_BIKE_CENTER_STRIP-1);

    ledStrip = leds;

    STATE = 0;

    gPalettes = pPalettes;

    numPixelsInStrip = pLedStripEndIndex - pLedStripStartIndex + 1;

    ledStripStartIndex = pLedStripStartIndex;

//***** IMPORTANT *****
    // This code will tell the strip to reverse or not for FIRE animation
    gReverseDirection = reverseTheLEDConfiguration;


// GEAR DOTS
    r1 = new Ring(ledStrip + ledStripStartIndex, numPixelsInStrip/2);
    r2 = new Ring(ledStrip + ledStripStartIndex + numPixelsInStrip/2, numPixelsInStrip/2);

    d1 = new Dot(r1, CRGB::Magenta, 0, 4, 0);
    d2 = new Dot(r1, CRGB::Orange, 6*16, 4, 0);
    d3 = new Dot(r1, CRGB::Green, 12*16, 4, 0);
    d4 = new Dot(r1, CRGB::Blue, 18*16, 4, 0);
    d5 = new Dot(r2, CRGB::Magenta, 0, -4, 0);
    d6 = new Dot(r2, CRGB::Orange, 6*16, -4, 0);
    d7 = new Dot(r2, CRGB::Green, 12*16, -4, 0);
    d8 = new Dot(r2, CRGB::Blue, 18*16, -4, 0);

    dots = new Dot[8]{*d1, *d2, *d3, *d4, *d5, *d6, *d7, *d8};
// GEAR DOTS

//START **** FIRE ANIMATION CLASS VARIABLE INITIALIZER
    // Array of temperature readings at each simulation cell
    // Since this is in a class now, the heat array has been declared as a class member
    heat = new byte[numPixelsInStrip];
    
//END **** FIRE ANIMATION CLASS VARIABLE INITIALIZER
    
  }
  
  // ******************************************************************    
  //                         UPDATE METHOD
  // ******************************************************************  
  void Update() {

    switch (STATE) {
 
      case SHOW_PATTERN:
        //(this->*(gPatterns[gCurrentPatternNumber]))();
        
          if( (millis() - lastPatternUpdateTime) > patternUpdateInterval ){
            (this->*(gPatterns[gCurrentPatternNumber]))();
            lastPatternUpdateTime = millis();
          }
        
        break;
  
      //This is a transition state where we run the fast blink function as feedback to the user,
      //but we also need to wait for the user to release the button, i.e. end the
      //long press, before moving to the CHANGE_BRIGHTNESS or SHOW_PATTERN state.
      case TO_CHANGE_BRIGHTNESS:
      case TO_CHANGE_PALETTE:
      case TO_SHOW_PATTERN:      
        fastBlink();
        break;

      case CHANGE_BRIGHTNESS:
        showCurrentBrightness();
        break;   

      case CHANGE_PALETTE:
        showCurrentPalette();
        break; 


    }

    // slowly cycle the "base color" through the rainbow
    if( (millis() - lastHueUpdateTime) > hueUpdateInterval){
      gHue++;
      lastHueUpdateTime = millis();
    }
    
    // DON'T USE THE "EVERY_N_MILLISECONDS" BUILT-IN FAST LED TIMER HERE. IT WILL BREAK THINGS FOR SOME REASON.
    //EVERY_N_MILLISECONDS( hueUpdateInterval ) { gHue++; }
    
  }

  

  // ******************************************************************    
  //                         HELPER METHODS
  // ******************************************************************    

  void nextPattern()
  {
    // add one to the current pattern number, and wrap around at the end
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % (ARRAY_SIZE( gPatterns ));

    //if cycleFunctionPatternIndex is second from the end of the array, skip to the next one, otherwise leave as is
    if( gCurrentPatternNumber == (ARRAY_SIZE( gPatterns ) - 3) ){
      patternUpdateInterval = 15;
      //patternUpdateInterval = fireUpdateInterval;
      
      for( uint16_t i = 0; i < numPixelsInStrip; i++) {
        heat[i] = 0;
      }
      
    }
    else{
      patternUpdateInterval = 0;
    }
    
  }

  void nextPalette()
  {
    // add one to the current palette number, and wrap around at the end
    //gCurrentPaletteNumber = (gCurrentPaletteNumber + 1) % ARRAY_SIZE( gPalettes );
    if( gCurrentPaletteNumber ==  0)  { gPalettes = RainbowColors_p;         }
    //else if( secondHand ==  5)  { SetupPurpleAndGreenPalette();      }
    //else if( secondHand == 10)  { SetupBlackAndWhiteStripedPalette();}
    else if( gCurrentPaletteNumber == 1)  { gPalettes = ForestColors_p;          }
    else if( gCurrentPaletteNumber == 2)  { gPalettes = CloudColors_p;           }
    else if( gCurrentPaletteNumber == 3)  { gPalettes = LavaColors_p;            }
    else if( gCurrentPaletteNumber == 4)  { gPalettes = OceanColors_p;           }
    else if( gCurrentPaletteNumber == 5)  { gPalettes = PartyColors_p;           }
    //else if( secondHand == 40)  { SetupRandomPalette();              }
    //else if( secondHand == 45)  { SetupRandomPalette();              }
    //else if( secondHand == 50)  { SetupRandomPalette();              }
    else if( gCurrentPaletteNumber == 6)  { gPalettes = RainbowStripeColors_p;   }
    else if( gCurrentPaletteNumber == 7)  { gPalettes = HeatColors_p;   }

    
    
    if(gCurrentPaletteNumber == 7){ gCurrentPaletteNumber = 0; }
    else { gCurrentPaletteNumber++; }
    
  } 

  //Used for button long press feedback
  void fastBlink() {
    uint8_t bpm = 45;  
    uint8_t on = beatsin8(bpm);
    if (on > 127) {
      fill_solid(&(ledStrip[ledStripStartIndex]), numPixelsInStrip, CRGB::White);
    } else {
      fill_solid(&(ledStrip[ledStripStartIndex]), numPixelsInStrip, CRGB::Black);    
    }
  }

  void showCurrentBrightness() {
      fill_solid(&(ledStrip[ledStripStartIndex]), numPixelsInStrip, brightnessDemoColor);  
  }


  void showCurrentPalette(){
     fill_palette( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 0, 8 /* higher = narrower stripes */,  gPalettes, 255, LINEARBLEND);
/*
     uint8_t colorIndex = 0;
      
      for( int i = 0; i < numPixelsInStrip; i++) {
        ledStrip[ledStripStartIndex + i] = ColorFromPalette(gPalettes, colorIndex, 255, LINEARBLEND);
        colorIndex += 3;
      }
*/      
  }
 
  void setStripState(uint8_t NEW_STATE){
    STATE = NEW_STATE;
  }

  uint8_t getStripState(){
    return STATE;
  }

  // ******************************************************************    
  //                         ANIMATION METHODS
  // ******************************************************************    

  void rainbow() 
  {
    // FastLED's built-in rainbow generator
    fill_rainbow( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, gHue, 7);
    
  }
  
  void rainbowWithGlitter() 
  {
    // built-in FastLED rainbow, plus some random sparkly glitter
    rainbow();
    addGlitter(80);
  }
  
  void addGlitter( fract8 chanceOfGlitter) 
  {
    if( random8() < chanceOfGlitter) {
      ledStrip[ ledStripStartIndex + random16(numPixelsInStrip) ] += CRGB::White;
    }
  }
  
  void confetti() 
  {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
    
    uint16_t pos = random16(numPixelsInStrip);
    
    ledStrip[ledStripStartIndex + pos] += CHSV( gHue + random8(64), 200, 255);
  }


  void patrioticConfetti() 
  {
    // red, white, and blue colored speckles that blink in and fade smoothly
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
    
    uint16_t pos = random16(numPixelsInStrip);
    
    CRGB nextColor;
    
    switch (random(3)) {
      case 0:
        nextColor = CRGB::Red;
        break;
      case 1:
        nextColor = CRGB::White;
        break;
      case 2:
        nextColor = CRGB::Blue;
        break;
      default:
        nextColor = CRGB::Blue;
        break;
    }
    ledStrip[ledStripStartIndex + pos] = nextColor;
  }

  void paletteConfetti() 
  {
    // red, white, and blue colored speckles that blink in and fade smoothly
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
    
    uint16_t pos = random16(numPixelsInStrip);
    
    ledStrip[ledStripStartIndex + pos] = ColorFromPalette( gPalettes, random8() );
  }

  
  void sinelon()
  {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
    
    uint16_t pos = beatsin16( 13, 0, numPixelsInStrip-1 );
    
    ledStrip[ledStripStartIndex + pos] += CHSV( gHue, 255, 192);
//    ledStrip[ledOrder[ledStripStartIndex + pos]] += CHSV( gHue, 255, 192);
  }

  //same as above but has two sinelones
  void sinelon2()
  {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
    
    uint16_t pos = beatsin16(13,0,numPixelsInStrip/2-1);
    ledStrip[ledStripStartIndex + pos] += CHSV( gHue, 255, 192);
//    ledStrip[ledOrder[ledStripStartIndex + pos]] += CHSV( gHue, 255, 192);
    
    uint16_t pos1 = beatsin16(13,0,numPixelsInStrip/2-1);
    ledStrip[ledStripStartIndex + pos1 + numPixelsInStrip/2] += CHSV( gHue, 255, 192);
//    ledStrip[ledOrder[ledStripStartIndex + pos1 + numPixelsInStrip/2]] += CHSV( gHue, 255, 192);
  }
  
  void juggle() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
    
    byte dothue = 0;
    
    for( uint16_t i = 0; i < 8; i++) {
      ledStrip[ledStripStartIndex + beatsin16( i+7, 0, numPixelsInStrip-1 )] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  }

  void bpm()
  {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    
    //CRGBPalette16 palette = PartyColors_p;
    
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    
    for( uint16_t i = 0; i < numPixelsInStrip; i++) { //9948
      //ledStrip[ledStripStartIndex + i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
      ledStrip[ledStripStartIndex + i] = ColorFromPalette(gPalettes, gHue+(i*2), beat-gHue+(i*10));
    }
  }

// GEAR DOTS
  void gearDots() {
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 20);
    
    for (uint16_t i=0; i< 8; i++) {
      dots[i].draw();
      dots[i].updatePos();
    }
  }
// GEAR DOTS

  // change patterns periodically
  void cycle() {
    (this->*(gPatterns[cycleFunctionPatternIndex]))();
    //EVERY_N_SECONDS( 10 ) { 
    if((millis() - lastCycleUpdateTime) > cycleUpdateInterval){
      cycleFunctionPatternIndex = (cycleFunctionPatternIndex + 1) % ARRAY_SIZE( gPatterns );

      //if cycleFunctionPatternIndex is second from the end of the array, skip to the next one, otherwise leave as is
      if( cycleFunctionPatternIndex == (ARRAY_SIZE( gPatterns ) -2) ){
        cycleFunctionPatternIndex = 0;
      }
      //if cycleFunctionPatternIndex is second from the end of the array, skip to the next one, otherwise leave as is
      else if( gCurrentPatternNumber == (ARRAY_SIZE( gPatterns ) - 3) ){
        patternUpdateInterval = 15;
        //patternUpdateInterval = fireUpdateInterval;
        
        for( uint16_t i = 0; i < numPixelsInStrip; i++) {
          heat[i] = 0;
        }
        
      }
      else{
        patternUpdateInterval = 0;
      }


      
      lastCycleUpdateTime = millis();
      //somewhat fancier but also more wordy way of doing the same thing in the if statement above
      //cycleFunctionPatternIndex = (cycleFunctionPatternIndex == (ARRAY_SIZE( gPatterns ) -2) ) ? cycleFunctionPatternIndex++ : cycleFunctionPatternIndex; 
      
    } 
  
  }

  void fire2012WithPalette() {
  // Fourth, the most sophisticated: this one sets up a new palette every
  // time through the loop, based on a hue that changes every time.
  // The palette is a gradient from black, to a dark color based on the hue,
  // to a light color based on the hue, to white.
  //
  //   static uint8_t hue = 0;
  //   hue++;
  //   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
  //   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
  //   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);
    
  // Array of temperature readings at each simulation cell
  // Since this is in a class now, the heat array has been declared as a class member
  //  static byte heat[numPixelsInStrip];
  
    // Step 1.  Cool down every cell a little
      for( uint16_t i = 0; i < numPixelsInStrip; i++) {
        heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / numPixelsInStrip) + 2));
      }
    
      // Step 2.  Heat from each cell drifts 'up' and diffuses a little
      for( uint16_t k= numPixelsInStrip - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
      }
      
      // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
      if( random8() < SPARKING ) {
        uint16_t y = random8(7);
        heat[y] = qadd8( heat[y], random8(160,255) );
      }
  
      // Step 4.  Map from heat cells to LED colors
      for( uint16_t j = 0; j < numPixelsInStrip; j++) {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        byte colorindex = scale8( heat[j], 240);
        CRGB color = ColorFromPalette( gPalettes, colorindex);
        uint16_t pixelnumber;
        if( gReverseDirection ) {
          pixelnumber = (numPixelsInStrip-1) - j;
        } else {
          pixelnumber = j;
        }
        ledStrip[pixelnumber] = color;
//        ledStrip[ledOrder[j]] = color;
        
        //ledStrip[ledStripStartIndex + j] = color;
        //ledStrip[numPixelsInStrip -1- j] = color;


        
      }
  }

  void FillLEDsFromPaletteColors()
  {
      uint8_t colorIndex = gHue;
      
      for( int i = 0; i < numPixelsInStrip; i++) {
          ledStrip[i] = ColorFromPalette( gPalettes, colorIndex);
//          ledStrip[ledOrder[i]] = ColorFromPalette( gPalettes, colorIndex);
          colorIndex += 3;
      }
  }  

  void FillLEDsFromPaletteOneColorAtAtime()
  {
      //uint8_t brightness = 255;
      
      for( int i = 0; i < numPixelsInStrip; i++) {
          ledStrip[i] = ColorFromPalette( gPalettes, gHue);
//          ledStrip[ledOrder[i]] = ColorFromPalette( gPalettes, gHue);
          //colorIndex += 3;
      }
  }  
  
  void fadeToBlack() {
    // turn off the strip in a "mysterious" way
    fadeToBlackBy( &(ledStrip[ledStripStartIndex]), numPixelsInStrip, 10);
  }



};


// ******************************************************************
// ******************************************************************
// ****************** END OF CLASS ********************
// ******************************************************************
// ******************************************************************




// ********* STRIP SETUP VARIABLES FOR A SINGLE STRIP WITH MULTIPLE SEGMENTS ***************
//
// *****************************************************************************************
/*
CRGB leds[NUM_LEDS_TOTAL];

LEDStripSegment ledStrip_bike_center(&(leds[0]), 0, NUM_LEDS_BIKE_CENTER_STRIP-1);
LEDStripSegment ledStrip_bike_side(&(leds[0]), NUM_LEDS_BIKE_CENTER_STRIP, NUM_LEDS_TOTAL - 1);
*/


// *********** STRIP SETUP VARIABLES FOR MULTIPLE INDIVIDUAL STRIPS **********************
//
// ***************************************************************************************
/*
CRGB leds_bike_center[NUM_LEDS_BIKE_CENTER_STRIP];
CRGB leds_bike_side[NUM_LEDS_BIKE_SIDE_STRIP];

LEDStripSegment ledStrip_bike_center(&(leds_bike_center[0]), gPal, 0, NUM_LEDS_BIKE_CENTER_STRIP-1);
LEDStripSegment ledStrip_bike_side(&(leds_bike_side[0]), gPal, 0, NUM_LEDS_BIKE_SIDE_STRIP - 1);
*/

// *********** STRIP SETUP VARIABLES FOR ONE STRIP WITH MULTIPLE SEGMENTS ****************
//
// ***************************************************************************************

CRGB leds_bike_center[NUM_LEDS_BIKE_TOTAL];
//CRGB leds_bike_side[NUM_LEDS_BIKE_SIDE_STRIP];

LEDStripSegment ledStrip_bike_center(&(leds_bike_center[0]), gPal, 0, NUM_LEDS_BIKE_CENTER_STRIP-1, true);

//USE THIS IF YOU WANT THE STRIP FLIPPED FOR FIRE ANIMATION
//LEDStripSegment ledStrip_bike_center(&(leds_bike_center[0]), gPal, 0, NUM_LEDS_BIKE_CENTER_STRIP-1, true);

// don't use these unless you want to create multiple segments in a single strip
//LEDStripSegment ledStrip_bike_center(&(leds_bike_center[0]), gPal, NUM_LEDS_BIKE_CENTER_STRIP, NUM_LEDS_BIKE_TOTAL - 1, NUM_LEDS_BIKE_TOTAL);
//LEDStripSegment ledStrip_bike_side(&(leds_bike_center[0]), gPal, NUM_LEDS_BIKE_CENTER_STRIP, NUM_LEDS_BIKE_TOTAL - 1);


// ****************** SETUP FUNCTION ********************************
// ****************** SETUP FUNCTION ********************************
// ****************** SETUP FUNCTION ********************************
void setup() {
  delay(3000); // 3 second delay for recovery ??? who knows why

//START ***** GLOBAL VARIABLE INITIALIZATION FOR FIRE ANIMATION ******
  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  //gPal = HeatColors_p;
  
  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  
  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
  
  // Third, here's a simpler, three-step gradient, from black to red to white
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
//END ***** GLOBAL VARIABLE INITIALIZATION FOR FIRE ANIMATION ******



  // tell FastLED about the LED strip configuration
  //***** VERSION WHERE THERE ARE MULTIPLE SEGMENTS IN A SINGLE STRIP *****
        //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP>(leds, NUM_LEDS_TOTAL).setCorrection(TypicalLEDStrip);
  //***** VERSION WHERE THERE ARE MULTIPLE SEGMENTS IN A SINGLE STRIP *****
  
  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP>(leds_bike_center, NUM_LEDS_BIKE_CENTER_STRIP).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_SIDE_STRIP>(leds_bike_side, NUM_LEDS_BIKE_SIDE_STRIP).setCorrection(TypicalLEDStrip);

  FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP>(leds_bike_center, NUM_LEDS_BIKE_TOTAL).setCorrection(TypicalLEDStrip);

  // Use this for the Staff
  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_SIDE_STRIP>(leds_bike_center, NUM_LEDS_BIKE_TOTAL).setCorrection(TypicalLEDStrip);

  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP,COLOR_ORDER>(leds_segment_1, NUM_LEDS_BIKE_CENTER_STRIP).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN_BIKE_CENTER_STRIP,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  
  //pinMode(LED_ENABLE_PIN, OUTPUT);
  //digitalWrite(LED_ENABLE_PIN, HIGH);  // enable access to LEDs

  // set master brightness control
  FastLED.setBrightness(INITIAL_BRIGHTNESS);

}

// ****************** MAIN LOOP *************************************
// ****************** MAIN LOOP *************************************
// ****************** MAIN LOOP *************************************
void loop() {

  // Add entropy to random number generator; we use a lot of it for the FIRE ANIMATION
  random16_add_entropy( random());

  readButtons();
  
  ledStrip_bike_center.Update();
  //ledStrip_bike_side.Update();

  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND); 

}


// ****************** HELPER FUNCTIONS *************************************
// ****************** HELPER FUNCTIONS *************************************
// ****************** HELPER FUNCTIONS *************************************
void readButtons(){

  //Read the button associated with bike center strip and brightness change (with long press)
  button_BikeCenterStrip_and_BrightnessChange.read();

  switch (ledStrip_bike_center.getStripState()) {

    //This state watches for short and long presses, switches the pattern for
    //short presses, and moves to the TO_CHANGE_BRIGHTNESS state for long presses.
    case SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){
        ledStrip_bike_center.nextPattern();
        //ledStrip_bike_side.nextPattern();
      }
      else if (button_BikeCenterStrip_and_BrightnessChange.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_CHANGE_BRIGHTNESS);
      }
      break;
      
    //This is a transition state where we start the fast blink as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TO_CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){
        ledStrip_bike_center.setStripState(CHANGE_BRIGHTNESS);
      }
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TO_SHOW_PATTERN" which is the fast-blink state.
    case CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_SHOW_PATTERN);
      }
      else if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){
        nextBrightness();
      }
      break;

    //This is a transition state where we just wait for the user to release the button
    //before moving back to the SHOW_PATTERN state.
    case TO_SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange.wasReleased()){
        ledStrip_bike_center.setStripState(SHOW_PATTERN);
      }
      break;
  }  



  button_BikeCenterStrip_and_BrightnessChange_backup.read();

  switch (ledStrip_bike_center.getStripState()) {

    //This state watches for short and long presses, switches the pattern for
    //short presses, and moves to the TO_CHANGE_BRIGHTNESS state for long presses.
    case SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        ledStrip_bike_center.nextPattern();
        //ledStrip_bike_side.nextPattern();
      }
      else if (button_BikeCenterStrip_and_BrightnessChange_backup.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_CHANGE_BRIGHTNESS);
      }
      break;
      
    //This is a transition state where we start the fast blink as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TO_CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        ledStrip_bike_center.setStripState(CHANGE_BRIGHTNESS);
      }
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TO_SHOW_PATTERN" which is the fast-blink state.
    case CHANGE_BRIGHTNESS:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.pressedFor(LONG_PRESS)){
        ledStrip_bike_center.setStripState(TO_SHOW_PATTERN);
      }
      else if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        nextBrightness();
      }
      break;

    //This is a transition state where we just wait for the user to release the button
    //before moving back to the SHOW_PATTERN state.
    case TO_SHOW_PATTERN:
      if (button_BikeCenterStrip_and_BrightnessChange_backup.wasReleased()){
        ledStrip_bike_center.setStripState(SHOW_PATTERN);
      }
      break;
  }  
  


    
  //Read the button associated with bike side strip and palette change (with long press)
  button_BikeSideStrip_and_PaletteChange.read();
  
  if (button_BikeSideStrip_and_PaletteChange.wasReleased()){
    ledStrip_bike_center.nextPalette();
  }
    

/*
  switch (ledStrip_bike_side.getStripState()) {

    //This state watches for short and long presses, switches the pattern for
    //short presses, and moves to the TO_CHANGE_BRIGHTNESS state for long presses.
    case SHOW_PATTERN:
      if (button_BikeSideStrip_and_PaletteChange.wasReleased())
        ledStrip_bike_side.nextPattern();
      else if (button_BikeSideStrip_and_PaletteChange.pressedFor(LONG_PRESS))
        ledStrip_bike_side.setStripState(TO_CHANGE_PALETTE);
      break;
      
    //This is a transition state where we start the fast blink as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TO_CHANGE_PALETTE:
      if (button_BikeSideStrip_and_PaletteChange.wasReleased())
        ledStrip_bike_side.setStripState(CHANGE_PALETTE);
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TO_SHOW_PATTERN" which is the fast-blink state.
    case CHANGE_PALETTE:
      if (button_BikeSideStrip_and_PaletteChange.pressedFor(LONG_PRESS)){
        ledStrip_bike_side.setStripState(TO_SHOW_PATTERN);
      }
      else if (button_BikeSideStrip_and_PaletteChange.wasReleased()){
        ledStrip_bike_side.nextPalette();
        ledStrip_bike_center.nextPalette();
      }
      break;

    //This is a transition state where we just wait for the user to release the button
    //before moving back to the SHOW_PATTERN state.
    case TO_SHOW_PATTERN:
      if (button_BikeSideStrip_and_PaletteChange.wasReleased())
        ledStrip_bike_side.setStripState(SHOW_PATTERN);
      break;
  }  

 */
}

void nextBrightness() {
  uint8_t currentBrightness = FastLED.getBrightness();
  currentBrightness += BRIGHTNESS_INCREMENT;

  if(currentBrightness < BRIGHTNESS_MAX_MODULO){
    currentBrightness = currentBrightness % BRIGHTNESS_MAX_MODULO;
  }
  else if(currentBrightness >= BRIGHTNESS_MAX_MODULO){
    currentBrightness = BRIGHTNESS_INCREMENT;
  }

  FastLED.setBrightness(currentBrightness);
}

void nextBrightness_old() {
  uint8_t currentBrightness = FastLED.getBrightness();
  currentBrightness += 16;
  currentBrightness = currentBrightness % 132;
  FastLED.setBrightness(currentBrightness);
}