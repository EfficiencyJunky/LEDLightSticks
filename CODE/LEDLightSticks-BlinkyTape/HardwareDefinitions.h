/*
  GlobalVariables.h  - Globally defined variables to be used throughout the sketch
                    -- Hardware definitions for various testing setups etc/
*/

#ifndef HardwareDefinitions_h
#define HardwareDefinitions_h


// *********************************************************************************
//    ARDUINO HARDWARE SETTINGS -- Change these according to your hardware
// *********************************************************************************

#define __BLINKY_TAPE__
// #define __TEENSY__

// ******* Blinky Tape Pins *******
#if defined(__BLINKY_TAPE__)
    
    // LED STRIP DEFINITIONS
    #define LEDS_01_PIN 13
    #define LEDS_01_NUM_LEDS 34

    // BUTTON DEFINITIONS
    #define PRIMARY_BUTTON_PIN  11

    // this is the button sodered directly to the blinkytape
    #define PRIMARY_BUTTON_PIN_BLINKYTAPE  10

    #define SECONDARY_BUTTON_PIN  7


// ******* Teensy Pins *******
#elif defined(__TEENSY__)

    // LED STRIP DEFINITIONS
    #define LEDS_01_PIN 3
    #define LEDS_02_PIN 4
    #define LEDS_01_NUM_LEDS 30
    #define LEDS_02_NUM_LEDS 30

    // BUTTON DEFINITIONS
    #define PRIMARY_BUTTON_PIN  1
    #define SECONDARY_BUTTON_PIN    2

#endif



// *********************************************************************************
//    FastLED LIBRARY DEFINITIONS
// *********************************************************************************

#define LED_TYPE NEOPIXEL
#define FRAMES_PER_SECOND  120

#define FAST_LED_MAX_BRIGHTNESS 255


#define BRIGHTNESS_MAX_MODULO   180


// *********************************************************************************
//    JC_BUTTON LIBRARY DEFINITIONS
// *********************************************************************************
#define LONG_PRESS   1000
#define DEBOUNCE_MS  20
#define PULLUP  true
#define INVERT  true



#endif
