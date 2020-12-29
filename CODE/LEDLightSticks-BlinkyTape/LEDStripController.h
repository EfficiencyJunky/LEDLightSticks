/*----------------------------------------------------------------------------------*
 * LED Strip Controller                                                             *
 * Turner Kirk Dec 2020                                                             *
 *                                                                                  *
 * The MIT License (MIT)                                                            *
 *                                                                                  *
 * Copyright (c) 2020 Turner Kirk                                                   *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of  *
 * this software and associated documentation files (the "Software"), to deal in    *
 * the Software without restriction, including without limitation the rights to     *
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of *
 * the Software, and to permit persons to whom the Software is furnished to do so,  *
 * subject to the following conditions:                                             *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in all   *
 * copies or substantial portions of the Software.                                  *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS *
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR   *
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   *
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN          *
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.       *
 *----------------------------------------------------------------------------------*/
#ifndef LEDStripController_h
#define LEDStripController_h


// *********************************************************************************
//            Includes and Defines - FastLED required
// *********************************************************************************
#include <FastLED.h>
// FASTLED_USING_NAMESPACE
#include <EEPROM.h>


// FASTLED_USING_NAMESPACE

// #if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
// #warning "Requires FastLED 3.1 or later; check github for latest code."
// #endif

const uint8_t pixelSpread = (256 / 34) + 1;

// *********************************************************************************
//    Definitions for things that need to be used externally
// *********************************************************************************
//******* ENUM for managing strip controller states ********
//The possible states for the button state machine
enum StripControllerStates {
        NORMAL_OPERATION,
        STATE_TRANSITION,
        SHOW_BRIGHTNESS_LEVEL,
        SHOW_SPEED_LEVEL
    };

// *******  Helper macro for calculating the length of an array ******* 
// creates a macro that computes the length of an array (number of elements)
// assuming all of the elements are the same size as the element in position 0
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
// #define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


// *******  Human readable definition for when we want to invert a strip ******* 
// this will set whether or not the strip is inverted
// meaning the beginning is the end and the end is the beginning
#define INVERT_STRIP true


// *********************************************************************************
//    Global defines for colors and animation related functions
// *********************************************************************************
//******* VARIOUS LED RELATED CONSTANTS ********
#define FULL_BRIGHT 255
#define FULL_SAT    255
#define WHITE_HUE   255

// variables for changing brightness
#define MIN_BRIGHTNESS  40  //set between 0 (off) to 255
#define MAX_BRIGHTNESS   200
#define NUM_BRIGHTNESS_LEVELS    6 
// #define INITIAL_BRIGHTNESS_LEVEL  2 // this is now set by values saved in EEPROM


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


//******* ALL AVAILABLE ANIMATIONS ********
// the actual animations being used are defined in the .CPP file "animationsToUse" array
enum Animations {
                    A_RAINBOW,
                    A_RAINBOW_GLITTER,
                    A_PALETTE,
                    A_PALETTE_GLITTER,
                    A_CONFETTI,
                    A_SINELON,
                    A_SINELON_DUAL,
                    A_JUGGLE,
                    A_BPM,
                    A_FIRE,
                    A_CYCLE_ALL,
                    A_SOLID_COLOR,
                    A_COLORWAVES,
                    TOTAL_AVAILABLE_ANIMATIONS
                };


//******* COLOR PALETTES ********
const CRGBPalette16 DEFAULT_PALETTE = RainbowColors_p;

// extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
// extern const uint8_t gGradientPaletteCount;


// *********************************************************************************
//    Global settings for Animation Timings
// *********************************************************************************
//******* LED STRIP CONTROLLER TIMING VARIABLES ********
// UPDATE INTERVALS: this is the time in ms between updates to the LEDStripController
#define DEFAULT_UPDATE_INTERVAL 10
#define FIRE_UPDATE_INTERVAL 15
#define ANIMATION_CYCLE_INTERVAL 10000



// *********************************************************************************
//    SETTINGS FOR BMP RELATED ANIMATIONS
// *********************************************************************************
#define NORMAL_HUE_INDEX_BPM 13
#define NORMAL_HUE_INDEX_DIRECTION 1 // 1 means normal direction is forward (DONT CHANGE THIS!) if you want to invert a strip, use the INVERT_STRIP argument when calling the LEDStripController constructor

#define NUM_SPEED_LEVELS   6

#define RAINBOW_HUE_INDEX_BPM_MIN   13
#define RAINBOW_HUE_INDEX_BPM_MAX   13 * NUM_SPEED_LEVELS

#define PALETTE_HUE_INDEX_BPM_ADD   3

#define SINELON_PIXEL_INDEX_BPM_MIN   13
#define SINELON_PIXEL_INDEX_BPM_MAX   13 * NUM_SPEED_LEVELS
#define JUGGLE_PIXEL_INDEX_BPM_ADD    -6



// our base address is where we are starting our storage of settings
// the first two bytes are used to store the total number of times 
// we've written to EEPROM just in case it gets super high and we need to change addresses
#define EEPROM_ADDR_BASE 31
#define EEPROM_ADDR_ANIMATION_INDEX 0
#define EEPROM_ADDR_BRIGHTNESS_INDEX 1
#define EEPROM_ADDR_PALETTE_INDEX 2
#define EEPROM_ADDR_SOLID_COLOR_INDEX 3
#define EEPROM_ADDR_SPEED_INDEX 4



// *********************************************************************************
//    MAIN CLASS DEFINITION
// *********************************************************************************
class LEDStripController
{
    public:
        LEDStripController( CRGB *leds, 
                            uint16_t stripLength, 
                            //CRGBPalette16 colorPalette = (CRGBPalette16)RainbowColors_p, 
                            CRGBPalette16 colorPalette = DEFAULT_PALETTE, 
                            uint8_t invertStrip = 0, 
                            uint16_t stripStartIndex = 0 );
        void update(uint32_t now_ms = 0);
        void nextAnimation();
        void nextPalette();
        void nextBrightness();
        void nextSpeed();
        void setBrightness(uint8_t brightness);
        void setOperationState(StripControllerStates newState);


    private:
        CRGB *_leds;                    // the array of LEDs
        uint16_t _stripLength;          // the number of LEDs in the strip
        uint8_t _invertStrip;          // whether the strip is regular orientation (0) or reversed (1)
        
        // **********************************************************
        //      TIME KEEPING VARIABLES
        // **********************************************************        
        uint32_t _timeToUpdate;       // time the .update() function should be called
        uint8_t _updateInterval;      // milliseconds between updates. Likely needs to be 5-10
        uint32_t _timeToCycleAnimations;

        // **********************************************************
        //      PIXEL STATE VARIABLES
        // **********************************************************
        uint8_t _hue;
        uint8_t _brightness;
        uint8_t _brightnessLevel;
        uint8_t _saturation;
        CRGBPalette16 _colorPalette;   // the color palette being used
        CRGBPalette16 _gradientPalette;   // the color palette being used
        uint8_t _solidColor;


        // **********************************************************
        //      STRIP STATE VARIABLES
        // **********************************************************
        StripControllerStates _state; // the state of the controller to be updated by external input        
        CRGB _showBrightnessColor;      // the color of the strip when in SHOW_BRIGHTNESS_LEVEL state        
        uint16_t _width;
        uint16_t _center;
        

        // **********************************************************
        //      ANIMATION SPECIFIC VARIABLES
        // **********************************************************                
        uint8_t _bpm;
        uint8_t _speedLevel;
        uint8_t _minBPM;
        uint8_t _maxBPM;
        uint32_t _bsTimebase; // used to reset beatsin() phase to 0


        uint8_t _forward;  // used to set which direction palette animations are going
        byte *_heat; // FIRE - Array of temperature readings at each simulation cell
        uint8_t _cycleAnimationsIndex;  

        // **********************************************************
        //      VARIABLES FOR ANIMATION FUNCTIONS
        // **********************************************************   
        typedef void (LEDStripController::*AnimationFunction)();
        
        AnimationFunction *_animationFunctions;
        Animations _activeAnimation;
        Animations _activeCycleAnimation;


        // **********************************************************
        //      STRUCT TO LOAD SETTINGS FROM EEPROM AT STARTUP
        // **********************************************************   
        struct Settings {
            uint8_t animationIndex;
            uint8_t brightnessLevel;
            uint8_t paletteIndex;
            uint8_t solidColorIndex;
            uint8_t speedLevel;
        };


        // **********************************************************
        //      STATIC MEMBERS TO SET FUNCTIONALITY OF CLASS
        //          these are defined in the .CPP file
        // **********************************************************   
        static const Animations animationsToUse[];
        static const CRGBPalette16 COLOR_PALETTES[];        
        //static const TProgmemRGBGradientPalettePtr GRADIENT_PALETTES[];
        static const CRGBPalette16 GRADIENT_PALETTES[];
        uint8_t _gradientPaletteIndex;
        static const uint8_t SOLID_COLORS[];


        // **********************************************************
        //      PRIVATE METHODS
        // **********************************************************
        void fastBlink();
        void setStripCHSV(CHSV newCHSV);
        void setStripCRGB(CRGB newCRGB);
        
        
        // **** Animation Methods ******        
        void rainbow();
        void palette();        
        void rainbowWithGlitter();
        void paletteWithGlitter();
        void confetti();
        void sinelon();
        void sinelonDual();
        void juggle();
        void bpm();
        void fire2012WithPalette();
        void cycleThroughAllAnimations();
        void solidColor();
        void colorwavesFinal();
        void colorwaves();


        // **** Animation Helper Methods ******
        void initializeAnimation(Animations animationToInitialize);
        void updateBPM();
        void addGlitter( fract8 chanceOfGlitter );
        uint8_t getHueIndex(uint8_t hueIndexBPM = NORMAL_HUE_INDEX_BPM, uint8_t direction = NORMAL_HUE_INDEX_DIRECTION);



        // **** OTHER Helper Methods ******
        void loadSettingsFromEEPROM(Settings *settings);
        // Settings loadSettingsFromEEPROM(); // THIS IS ANOTHER WAY TO DO THE ABOVE
        void saveSettingsToEEPROM(uint8_t value, uint8_t addrIndex);


};



#endif
