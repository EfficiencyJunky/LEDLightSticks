/*
  GlobalVariables.h  - Globally defined variables to be used throughout the sketch
                    -- Hardware definitions for various testing setups etc/
*/

#ifndef HardwareDefinitions_h
#define HardwareDefinitions_h


// *********************************************************************************
//    ARDUINO HARDWARE SETTINGS -- Change these according to your hardware
// *********************************************************************************
// Official Documentation Hardware definitions for BlinkyTape
// #define LED_OUT       13
// #define BUTTON_IN     10
// #define ANALOG_INPUT  A9
// #define EXTRA_PIN_A    7
// #define EXTRA_PIN_B   11
// Usecase examples in the official Github Repo can be found here: https://github.com/Blinkinlabs/BlinkyTape_Arduino/blob/2.1.0/examples/ColorSwirl/ColorSwirl.ino


#define __BLINKY_TAPE_TWO_BUTTON__
// #define __BLINKY_TAPE_ONE_BUTTON__
// #define __TEENSY__

// ******* Blinky Tape With TWO External Button *******
#if defined(__BLINKY_TAPE_TWO_BUTTON__)

    // IF IT HAS AN OFF SWITCH ON THE DEVICE (V2 doesn't have this)
    #define HAS_ON_OFF_SWITCH true
    
    // LED STRIP DEFINITIONS
    #define LEDS_01_PIN 13
    #define LEDS_01_NUM_LEDS 34

    // BUTTON DEFINITIONS
    #define EXT_PRIMARY_BUTTON_PIN  11

    // this is the button sodered directly to the blinkytape
    #define ONBOARD_PRIMARY_BUTTON_PIN  10

    // this is the second button used mostly for color changes
    #define EXT_SECONDARY_BUTTON_PIN  7
    
    // analog pin used to generate a semi random seed for random number generation
    // example here: https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
    #define ANALOG_PIN  A9

// ******* Blinky Tape With ONE External Button *******
#elif defined(__BLINKY_TAPE_ONE_BUTTON__)
    
    // IF IT HAS AN OFF SWITCH ON THE DEVICE (V2 doesn't have this)
    #define HAS_ON_OFF_SWITCH true
    
    // LED STRIP DEFINITIONS
    #define LEDS_01_PIN 13
    #define LEDS_01_NUM_LEDS 34

    // BUTTON DEFINITIONS
    #define EXT_PRIMARY_BUTTON_PIN  11

    // this is the button sodered directly to the blinkytape
    #define ONBOARD_SECONDARY_BUTTON_PIN  10

    // analog pin used to generate a semi random seed for random number generation
    // example here: https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
    #define ANALOG_PIN  A9


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

    #define ANALOG_PIN A9

#endif



// *********************************************************************************
//    FastLED LIBRARY DEFINITIONS
// *********************************************************************************

#define LED_TYPE NEOPIXEL
#define FRAMES_PER_SECOND  120

#define FAST_LED_MAX_BRIGHTNESS 255


// *********************************************************************************
//    JC_BUTTON LIBRARY DEFINITIONS
// *********************************************************************************
#define LONG_PRESS   1000
#define DEBOUNCE_MS  20
#define PULLUP  true
#define INVERT  true



#endif
