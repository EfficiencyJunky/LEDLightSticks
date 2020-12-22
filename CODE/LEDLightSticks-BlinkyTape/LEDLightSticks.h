/*
  GlobalVariables.h  - Globally defined variables to be used throughout the sketch
                    -- Hardware definitions for various testing setups etc/
*/

#ifndef LEDLightSticks_h
#define LEDLightSticks_h

    // ************************************************************************************
    //    EXTERNAL LIBRARY INITIALIZATION
    // ************************************************************************************
    #include <FastLED.h>
    #include "JC_Button_old.h"

    FASTLED_USING_NAMESPACE

    #if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
    #warning "Requires FastLED 3.1 or later; check github for latest code."
    #endif


    // HELPER MACRO FOR CALCULATING THE LENGTH OF AN ARRAY
    // creates a macro that computes the length of an array (number of elements)
    // assuming all of the elements are the same size as the element in position 0
    #define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))



    // ************************************************************************************
    //    ARDUINO HARDWARE SETTINGS -- Change these according to your hardware
    // ************************************************************************************

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



    // ************************************************************************************
    //    FastLED LIBRARY AND OTHER LED RELATED GLOBAL VARIABLES
    // ************************************************************************************

    #define LED_TYPE NEOPIXEL
    #define FRAMES_PER_SECOND  60
    #define INITIAL_BRIGHTNESS  60  //set between 0 (off) to 255

    // variables for changing brightness
    #define BRIGHTNESS_INCREMENT    20 
    #define BRIGHTNESS_MAX_MODULO   180


    //******* VARIOUS LED RELATED CONSTANTS ********
    #define FULL_BRIGHT 255
    #define FULL_SAT    255
    #define WHITE_HUE   255
    #define GLOBAL_BPM   13



    //******* FIRE ANIMATION GLOBAL VARIABLES ********
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



    #define DEFAULT_UPDATE_INTERVAL 10




    // ************************************************************************************
    //    JC_BUTTON LIBRARY VARIABLES
    // ************************************************************************************

    #define LONG_PRESS   1000
    #define DEBOUNCE_MS  20
    #define PULLUP  true
    #define INVERT  true

    //The possible states for the button state machine
    enum {
            SHOW_PATTERN, 
            TO_CHANGE_BRIGHTNESS, 
            CHANGE_BRIGHTNESS, 
            TO_CHANGE_PALETTE, 
            CHANGE_PALETTE, 
            TO_SHOW_PATTERN
        };

    









#endif