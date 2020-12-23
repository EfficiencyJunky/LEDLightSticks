/*
  GlobalVariables.h  - Globally defined variables to be used throughout the sketch
                    -- Hardware definitions for various testing setups etc/
*/

#ifndef LEDLightSticks_h
#define LEDLightSticks_h

#include "JC_Button_old.h"

// *********************************************************************************
//    GLOBAL ENUM FOR MANAGING PROGRAM STATE
// *********************************************************************************
//The possible states for the button state machine
enum ProgramState {
        ANIMATION_IS_RUNNING, 
        TRANSITION_TO_CHANGE_BRIGHTNESS, 
        CHANGE_BRIGHTNESS,
        TRANSITION_TO_ANIMATION_IS_RUNNING
    };


// HELPER MACRO FOR CALCULATING THE LENGTH OF AN ARRAY
// creates a macro that computes the length of an array (number of elements)
// assuming all of the elements are the same size as the element in position 0
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))



// *********************************************************************************
//    ARDUINO HARDWARE SETTINGS -- Change these according to your hardware
// *********************************************************************************

// this will set whether or not the strip is inverted
// meaning the beginning is the end and the end is the beginning
#define INVERT_STRIP true

//#define __BLINKY_TAPE__
#define __TEENSY__

// ******* Blinky Tape Pins *******
#if defined(__BLINKY_TAPE__)
    
    // LED STRIP DEFINITIONS
    #define LEDS_01_PIN 13
    #define LEDS_01_NUM_LEDS 34

    // BUTTON DEFINITIONS
    #define ANIMATION_BUTTON_PIN  11

    // this is the button sodered directly to the blinkytape
    #define ANIMATION_BUTTON_PIN_BLINKYTAPE  10

    #define PALETTE_BUTTON_PIN  7


// ******* Teensy Pins *******
#elif defined(__TEENSY__)

    // LED STRIP DEFINITIONS
    #define LEDS_01_PIN 3
    #define LEDS_01_NUM_LEDS 30

    // BUTTON DEFINITIONS
    #define ANIMATION_BUTTON_PIN  1
    #define PALETTE_BUTTON_PIN    2

#endif



// *********************************************************************************
//    FastLED LIBRARY VARIABLES
// *********************************************************************************

#define LED_TYPE NEOPIXEL
#define FRAMES_PER_SECOND  60
#define INITIAL_BRIGHTNESS  60  //set between 0 (off) to 255

// variables for changing brightness
#define BRIGHTNESS_INCREMENT    20 
#define BRIGHTNESS_MAX_MODULO   180


// *********************************************************************************
//    JC_BUTTON LIBRARY VARIABLES
// *********************************************************************************
#define LONG_PRESS   1000
#define DEBOUNCE_MS  20
#define PULLUP  true
#define INVERT  true



#endif
