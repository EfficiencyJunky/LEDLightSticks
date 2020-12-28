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

// #if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
// #warning "Requires FastLED 3.1 or later; check github for latest code."
// #endif


// *********************************************************************************
//    Definitions for things that need to be used externally
// *********************************************************************************
//******* ENUM for managing strip controller states ********
//The possible states for the button state machine
enum LEDStripControllerState {
        NORMAL_OPERATION,
        STATE_TRANSITION,
        SHOW_BRIGHTNESS_LEVEL,
        SHOW_SPEED_LEVEL
    };

// *******  Helper macro for calculating the length of an array ******* 
// creates a macro that computes the length of an array (number of elements)
// assuming all of the elements are the same size as the element in position 0
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
//#define ENUM_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#define EEPROM_ADDR_BASE 31
#define EEPROM_ADDR_ANIMATION_INDEX 1
#define EEPROM_ADDR_BRIGHTNESS_INDEX 2
#define EEPROM_ADDR_PALETTE_INDEX 3
#define EEPROM_ADDR_SPEED_INDEX 4


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
#define INITIAL_BRIGHTNESS_LEVEL  2


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


//******* ANIMATIONS ********
enum Animations {
                    A_RAINBOW,
                    A_RAINBOW_GLITTER,
                    A_PALETTE,
                    A_PALETTE_GLITTER,
                    A_CONFETTI,
                    A_SINELON,
                    A_SINELON_DUAL,
                    TOTAL_AVAILABLE_ANIMATIONS
                };

//******* ORDER OF ANIMATIONS ********
const Animations animationsToUse[] = {
                                        //A_RAINBOW,
                                        A_PALETTE,
                                        //A_RAINBOW_GLITTER,
                                        A_PALETTE_GLITTER,
                                        A_CONFETTI,
                                        A_SINELON,
                                        A_SINELON_DUAL
                                     };


//******* COLOR PALETTES ********
const CRGBPalette16 DEFAULT_PALETTE = RainbowColors_p;

const CRGBPalette16 COLOR_PALETTES[] = {
                                            RainbowColors_p,
                                            ForestColors_p,
                                            CloudColors_p,
                                            LavaColors_p,
                                            OceanColors_p,
                                            PartyColors_p,
                                            HeatColors_p, // fire
                                            RainbowStripeColors_p,
                                        };

const uint8_t NUM_COLOR_PALETTES = ARRAY_SIZE(COLOR_PALETTES);

// *********************************************************************************
//    Global settings for Animation Timings
// *********************************************************************************
//******* LED STRIP CONTROLLER TIMING VARIABLES ********
// UPDATE INTERVALS: this is the time in ms between updates to the LEDStripController
#define DEFAULT_UPDATE_INTERVAL 10



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
        void setOperationState(LEDStripControllerState newState);


    private:
        CRGB *_leds;                    // the array of LEDs
        uint16_t _stripLength;          // the number of LEDs in the strip
        uint8_t _invertStrip;          // whether the strip is regular orientation (0) or reversed (1)
        
        // **********************************************************
        //      TIME KEEPING VARIABLES
        // **********************************************************        
        uint32_t _timeToUpdate;       // time the .update() function should be called
        uint8_t _updateInterval;      // milliseconds between updates. Likely needs to be 5-10


        // **********************************************************
        //      PIXEL STATE VARIABLES
        // **********************************************************
        uint8_t _hue;
        uint8_t _brightness;
        uint8_t _brightnessLevel;
        uint8_t _saturation;
        // uint8_t _hueIndex;
        CRGBPalette16 _colorPalette;   // the color palette being used

        // **********************************************************
        //      STRIP STATE VARIABLES
        // **********************************************************
        LEDStripControllerState _state; // the state of the controller to be updated by external input        
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


        typedef void (LEDStripController::*AnimationFunction)();
        
        AnimationFunction *_animationFunctions;
        Animations _activeAnimation;


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


        // **** Animation Helper Methods ******
        void initializeActiveAnimation();
        void updateBPM();
        void addGlitter( fract8 chanceOfGlitter );
        uint8_t getHueIndex(uint8_t bpm = NORMAL_HUE_INDEX_BPM, uint8_t direction = NORMAL_HUE_INDEX_DIRECTION);



        // **** OTHER Helper Methods ******








/*
            
        uint32_t long hueUpdateInterval = 10;
        uint32_t long fireUpdateInterval = 15;
        uint32_t long cycleUpdateInterval = 10000;
        
        typedef void (LEDStripSegment::*AnimationsList[13])(); // make sure to update the number (currently 13) when adding animations to the structure below
    
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
        


        uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
        uint8_t gCurrentPaletteNumber = 0; // Index number of which palette is current
        uint8_t gHue = 0; // rotating "base color" used by many of the patterns

        uint8_t cycleFunctionPatternIndex = 0;

*/



};



#endif
