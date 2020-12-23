/*----------------------------------------------------------------------------------*
 * LED Strip Controller                                                             *
 * Turner Kirk Dec 2020                                                             *
 *                                                                                  *
 * The LEDStripController class was built to manage the state of a single LED Strip *
 * and relies on the functions of the FastLED library which you can find more info  *
 * on here: https://github.com/FastLED/FastLED                                      *
 *                                                                                  *
 * This class takes in a reference to a CRGB array from the FastLED library and     *
 * makes it easy to trigger different animations that will run on that array        *
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


#include "LEDStripController.h"


/*--------------------------------------------------------------------------------------------------*
 *                          CONSTRUCTOR                                                             *
 * LEDStripController(*leds, stripLength, colorPalette, reverseStrip = 0, startIndex = 0 )     *
 * *leds            A reference to the array of LEDs                                                *
 * stripLength      The number of LEDs in the strip                                                 *
 * colorPalette     The color palette to use in certain animations                                  *
 * reverseStrip     Whether the strip is regular orientation (0) or reversed (1)                    *
 * startIndex       In case this controller is only supposed to control a subset of the leds array, * 
 *                  this would be the index at which to start from                                  *
 *                  (the endIndex can be calculated by adding _stripLength)                         *
 *--------------------------------------------------------------------------------------------------*/
LEDStripController::LEDStripController( CRGB *leds, 
                                        uint16_t stripLength, 
                                        CRGBPalette16 colorPalette, 
                                        uint8_t reverseStrip, 
                                        uint16_t startIndex)
{

    _leds = leds;
    _stripLength = stripLength;
    _colorPalette = colorPalette;
    _reverseStrip = reverseStrip;
    _startIndex = startIndex;

    _state = RUN_ANIMATION;
    _showBrightnessColor = CRGB::Blue;

    
    _updateInterval = DEFAULT_UPDATE_INTERVAL;

    heat = new byte[stripLength];


}




// ****************************************************************************************    
//      PUBLIC METHODS        
// ****************************************************************************************
/*--------------------------------------------------------------------------------------------------*
 *                          UPDATE METHOD                                                           *
 * This method is called externally everytime the caller wants our LEDStripController to Update     *
 * it's LEDs array.                                                                                 *
 *--------------------------------------------------------------------------------------------------*/
void LEDStripController::update() {

    // static variables for time keeping
    static uint32_t now_ms;
    static uint32_t lastUpdateTime = 0;

    now_ms = millis();

    if( (now_ms - lastUpdateTime) > _updateInterval ){
        switch (_state) {
    
            case RUN_ANIMATION:
                runAnimation(1, now_ms);                     
            break;

            case TRANSITION_STATE:      
                runAnimation(2, now_ms);
                break;

            case SHOW_BRIGHTNESS_LEVEL:
                //runAnimation(3, now_ms);
                break;   

            default:
                break; 

        }

        lastUpdateTime = now_ms;
    }
}



/*--------------------------------------------------------------------------------------------------*
 *                          NEXT PATTERN                                                            *
 *                                                                                                  *
 *--------------------------------------------------------------------------------------------------*/
void LEDStripController::nextPattern(){

    glitter = !glitter;

}


void LEDStripController::setState(LEDStripControllerState newState){

    _state = newState;

    switch(_state){

        case SHOW_BRIGHTNESS_LEVEL:
            fill_solid( _leds, _stripLength, CRGB::Blue );
            break;
        
        default:
            break;
    }

}



// ****************************************************************************************    
//      PRIVATE METHODS        
// ****************************************************************************************

/*--------------------------------------------------------------------------------------------------*
 *                          PLACEHOLDER                                                             *
 *                                                                                                  *
 *--------------------------------------------------------------------------------------------------*/
void LEDStripController::runAnimation(uint8_t animationType, uint32_t now_ms){

    static uint32_t lastBlinkTime = 0;

    if(animationType == 1){
        // mimmick led strip animation with rainbow + glitter
        hue++;
        fill_rainbow( _leds, _stripLength, hue, 7);

        if(glitter){
            if( random8() < 80) {
            _leds[ random16(_stripLength) ] += CRGB::White;
            }        
        }

    }
    else if(animationType == 2){
        if( (now_ms - lastBlinkTime) < 500 ){
            fill_solid( _leds, _stripLength, CHSV( 255, 0, 100) );
        }
        else if( (now_ms - lastBlinkTime) < 1000 ){
            fill_solid( _leds, _stripLength, CRGB::Black );
        }
        else{
            lastBlinkTime = now_ms;
        }
    }


}
