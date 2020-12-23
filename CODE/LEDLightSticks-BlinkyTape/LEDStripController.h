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

#include "LEDLightSticks.h"

//The possible states for the button state machine
enum LEDStripControllerState {
        RUN_ANIMATION,
        TRANSITION_STATE,
        SHOW_BRIGHTNESS_LEVEL
    };


class LEDStripController
{
    public:
        LEDStripController( CRGB *leds, uint16_t stripLength, CRGBPalette16 colorPalette, uint8_t reverseStrip = 0, uint16_t startIndex = 0 );
        void update();
        void nextPattern();
        void setState(LEDStripControllerState newState);
    

    private:
        CRGB *_leds;                    // the array of LEDs
        uint16_t _stripLength;          // the number of LEDs in the strip
        CRGBPalette16 _colorPalette;    // the color palette to use in certain animations
        uint8_t _reverseStrip;          // whether the strip is regular orientation (0) or reversed (1)
        uint16_t _startIndex;           // in case this controller is only supposed to control a subset of the leds array, this would be the index at which to start from (the endIndex can be calculated by adding _stripLength)

        // uint16_t* ledOrder;
        LEDStripControllerState _state; // the state of the controller to be updated by external input        
        CRGB _showBrightnessColor;      // the color of the strip when in SHOW_BRIGHTNESS_LEVEL state
        
        //uint32_t _lastUpdateTime;       // time the .Update function was last allowed to update the current animation
        uint8_t _updateInterval;        // milliseconds between updates. Likely needs to be 5-10


        //FIRE ANIMATION VARIABLE - convert to static function var eventually
        // Array of temperature readings at each simulation cell
        byte *heat;





        bool glitter = false;
        uint8_t hue = 0;



        void runAnimation(uint8_t animationType, uint32_t now_ms);


/*
        
        unsigned long lastHueUpdateTime = 0;  
        unsigned long lastCycleUpdateTime = 0;
    
        unsigned long hueUpdateInterval = 10;
        unsigned long fireUpdateInterval = 15;
        unsigned long cycleUpdateInterval = 10000;
        
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
