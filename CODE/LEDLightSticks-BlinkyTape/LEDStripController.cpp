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
 * LEDStripController(*leds, stripLength, colorPalette, invertStrip = 0, stripStartIndex = 0 )     *
 * *leds            A reference to the array of LEDs                                                *
 * stripLength      The number of LEDs in the strip                                                 *
 * colorPalette     The color palette to use in certain animations                                  *
 * invertStrip     Whether the strip is regular orientation (0) or reversed (1)                    *
 * stripStartIndex       In case this controller is only supposed to control a subset of the leds array, * 
 *                  this would be the index at which to start from                                  *
 *                  (the endIndex can be calculated by adding _stripLength)                         *
 *--------------------------------------------------------------------------------------------------*/
LEDStripController::LEDStripController( CRGB *leds, 
                                        uint16_t stripLength, 
                                        CRGBPalette16 colorPalette, 
                                        uint8_t invertStrip, 
                                        uint16_t stripStartIndex)
{

    _leds = &leds[stripStartIndex];
    _stripLength = stripLength;    
    _invertStrip = invertStrip;

    // **********************************************************
    //      TIME KEEPING VARIABLES
    // ********************************************************** 
    _timeToUpdate = 0;
    _updateInterval = DEFAULT_UPDATE_INTERVAL;


    // **********************************************************
    //      PIXEL STATE VARIABLES
    // **********************************************************
    _hue = 0;
    _colorPalette = colorPalette;
    // the second half of this equation (ceil(...)) computes the amount to increment by for each brightness level
    // so we just multiply it by our INITIAL_BRIGHTNESS_LEVEL
    _brightness = INITIAL_BRIGHTNESS_LEVEL * ceil((MAX_BRIGHTNESS - MIN_BRIGHTNESS) / (NUM_BRIGHTNESS_LEVELS - 1));;
    _saturation = FULL_SAT;    


    // **********************************************************
    //      STRIP STATE VARIABLES
    // **********************************************************    
    _state = NORMAL_OPERATION;
    _showBrightnessColor = CRGB::Blue;
    _width = _stripLength;
    _center = stripLength / 2;


    // **********************************************************
    //      ANIMATION SPECIFIC VARIABLES
    // **********************************************************
    _bsTimebase = 0;
    _speedIndex = 0;
    _forward = true;
    _heat = new byte[stripLength];

    
    _animationFunctions = new AnimationFunction[TOTAL_AVAILABLE_ANIMATIONS];
    _animationFunctions[A_RAINBOW]          = &LEDStripController::rainbow;
    _animationFunctions[A_RAINBOW_GLITTER]  = &LEDStripController::rainbowWithGlitter;
    _animationFunctions[A_PALETTE]          = &LEDStripController::palette;
    _animationFunctions[A_PALETTE_GLITTER]  = &LEDStripController::paletteWithGlitter;
    _animationFunctions[A_CONFETTI]         = &LEDStripController::confetti;
    _animationFunctions[A_SINELON]          = &LEDStripController::sinelon;
    _animationFunctions[A_SINELON_DUAL]     = &LEDStripController::sinelonDual;

    _activeAnimation = animationsToUse[0];
    
    // this function initializes all the animation specific parameters
    // _bpm
    // _minBPM
    // _maxBPM 
    initializeActiveAnimation();



}




// ****************************************************************************************    
//      PUBLIC METHODS        
// ****************************************************************************************
/*--------------------------------------------------------------------------------------------------*
 *                          UPDATE METHOD                                                           *
 * This method is called externally everytime the caller wants our LEDStripController to Update     *
 * it's LEDs array.                                                                                 *
 *--------------------------------------------------------------------------------------------------*/
void LEDStripController::update(uint32_t now_ms) 
{

    if(now_ms == 0){ now_ms = millis(); }

    if( now_ms >= _timeToUpdate ){
        switch (_state) {
    
            case NORMAL_OPERATION:
            {
                (this->*(_animationFunctions[_activeAnimation]))();
                break;
            }
            case STATE_TRANSITION:
            {
                fastBlink();
                break;
            }
            case SHOW_BRIGHTNESS_LEVEL:
            {
                setStripCHSV(  CHSV( 90*2, FULL_SAT, _brightness)  );
                break;
            }
            case SHOW_SPEED_LEVEL:
            {
                setStripCHSV(  CHSV( 0, FULL_SAT, beatsin8(_bpm, MIN_BRIGHTNESS, MAX_BRIGHTNESS))  );
                break;
            }
            default:
            {
                break; 
            }
        }

        _timeToUpdate = now_ms + _updateInterval;
    }
}



/*--------------------------------------------------------------------------------------------------*
 *                          NEXT PATTERN                                                            *
 *                                                                                                  *
 *--------------------------------------------------------------------------------------------------*/
void LEDStripController::nextAnimation(){

    // cycle through the array of animationsToUse.
    // figure out which index matches our current _activeAnimation
    // increment the index and modulo with the size of the array
    // use that incremented index as the new index into our animationsToUse array
    // set that as our new _activeAnimation
    for(uint8_t i = 0; i < ARRAY_SIZE(animationsToUse); i++){
        
        if(animationsToUse[i] == _activeAnimation){
            _activeAnimation = animationsToUse[(i + 1) % ARRAY_SIZE(animationsToUse)];
           break; 
        }
    }
    

    initializeActiveAnimation();

    return;

}


void LEDStripController::nextPalette(){

    // cycle through the array of available palettes.
    // figure out which index matches our current palette
    // increment the index and modulo with the size of the array
    // use that incremented index as the new index into our pallettes array
    for(uint8_t i = 0; i < NUM_COLOR_PALETTES; i++){
        
        if(COLOR_PALETTES[i] == _colorPalette){
            _colorPalette = COLOR_PALETTES[(i + 1) % NUM_COLOR_PALETTES];
            return;
        }
    }

}



void LEDStripController::nextBrightness(){

    _brightness += ceil((MAX_BRIGHTNESS - MIN_BRIGHTNESS) / (NUM_BRIGHTNESS_LEVELS - 1));

    if(_brightness > MAX_BRIGHTNESS){
        _brightness = MIN_BRIGHTNESS;
    }

}


void LEDStripController::nextSpeed(){

    
    _speedIndex = (_speedIndex + 1) % NUM_SPEED_LEVELS;

    updateBPM();

}




void LEDStripController::setBrightness(uint8_t brightness){
    _brightness = brightness;
}




void LEDStripController::setOperationState(LEDStripControllerState newState){

    _state = newState;

    switch(_state){
        case NORMAL_OPERATION:
        {
            break;
        }
        case STATE_TRANSITION:
        {
            _bsTimebase = millis();
            break;
        }
        case SHOW_BRIGHTNESS_LEVEL:
        {
            //fill_solid( _leds, _stripLength, CRGB::Blue );
            break;
        }
        default:
        {
            break;
        }
    }

}



// ****************************************************************************************    
//      PRIVATE METHODS        
// ****************************************************************************************

// *********************************************************************************
//      Basic functions for setting the strip to a solid color
// *********************************************************************************
//Used for button long press feedback
// creates a sine wave at 60 bpm and then turns the strip on half the time
void LEDStripController::fastBlink() {
    static uint8_t bpm = 60;
    uint8_t sin60bpm = beatsin8(bpm, 0, 255, _bsTimebase, 256 / 2 - 1);
    if (sin60bpm > 127) {
        fill_solid( _leds, _stripLength, CHSV( 255, 0, 80) );
    } 
    else {
        fill_solid( _leds, _stripLength, CRGB::Black );
        //fill_solid(&(_leds[_stripStartIndex]), _stripLength, CRGB::Black);    
    }
}


// set strip to color based on CHSV input
void LEDStripController::setStripCHSV(CHSV newCHSV) {

    // for( int i = 0; i < _stripLength; ++i) {
    //     _leds[i] = newCHSV;
    // }
    fill_solid( _leds, _stripLength, newCHSV );
}


// set strip to color based on CRGB input
void LEDStripController::setStripCRGB(CRGB newCRGB) {

    fill_solid( _leds, _stripLength, newCRGB );
}






/*--------------------------------------------------------------------------------------------------*
 *                          PLACEHOLDER                                                             *
 *                                                                                                  *
 *--------------------------------------------------------------------------------------------------*/
void LEDStripController::rainbow(){    

    fill_palette( _leds, _stripLength, getHueIndex(_bpm, _invertStrip), 7, RainbowColors_p, _brightness, LINEARBLEND);
}


void LEDStripController::palette(){

    fill_palette( _leds, _stripLength, getHueIndex(_bpm, _invertStrip), 7, _colorPalette, _brightness, LINEARBLEND);
}


// same as the above rainbow function except this also ads glitter
void LEDStripController::rainbowWithGlitter() {
  // reference our rainbow function, plus some random sparkly glitter
  rainbow();
  addGlitter(80); // MAGIC NUMBER ALERT!!!
}

// same as the above palette function except this also ads glitter
void LEDStripController::paletteWithGlitter() {
  // reference our palette function, plus some random sparkly glitter
  palette();
  addGlitter(80); // MAGIC NUMBER ALERT!!!
}




// Pop and Fade. like confetti!!! random colored speckles that blink in and fade smoothly
void LEDStripController::confetti() {
  
    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!
    uint16_t pos = random16(_stripLength);  

    if(random8() > 20){ // MAGIC NUMBER ALERT!!!
        // this method that just cycles through the rainbow and     
        // uses qadd8 to clamp the addition of _brightness+40 to a max of 255
        // then converts the rgb value to CHSV
        CHSV newHue = rgb2hsv_approximate( ColorFromPalette( _colorPalette, getHueIndex() + random8(32), qadd8(_brightness, 40 )) );// MAGIC NUMBER ALERT!!!
        // drop the saturation
        newHue.saturation = 200; // MAGIC NUMBER ALERT!!!
        // add to the mix
        _leds[pos] += newHue;
        //   _leds[pos] += CHSV( getHueIndex() + random8(64), 200, brightness);
    }
}





// a colored dot sweeping back and forth, with fading trails
void LEDStripController::sinelon(){

    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!

    uint16_t pos = beatsin16( _bpm, 0, _stripLength - 1 );

    // _leds[pos] += ColorFromPalette( _colorPalette, getHueIndex(), qadd8(_brightness, 40 ));
    _leds[pos] += ColorFromPalette( _colorPalette, getHueIndex(), qadd8(_brightness, 40 ));
    // _leds[pos] += CHSV( getHueIndex(), 255, FULL_BRIGHT);

}


// a colored dot sweeping back and forth, with fading trails
void LEDStripController::sinelonDual(){

    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!

    uint16_t pos1 = beatsin16( _bpm, 0, floor(_stripLength/2.0) - 1 );
    uint16_t pos2 = beatsin16( _bpm, ceil(_stripLength/2.0) - 1, _stripLength - 1 );
    
    _leds[pos1] += ColorFromPalette( _colorPalette, getHueIndex(), qadd8(_brightness, 40 ));
    _leds[pos2] += ColorFromPalette( _colorPalette, getHueIndex(), qadd8(_brightness, 40 ));

    // _leds[pos1] += CHSV( getHueIndex(), 255, FULL_BRIGHT);
    // _leds[pos2] += CHSV( getHueIndex(), 255, FULL_BRIGHT);

}





// **********************************************************
//      ANIMATION HELPER METHODS
// **********************************************************

// _bpm, _minBPM, _maxBPM are all initialized here
void LEDStripController::initializeActiveAnimation(){

    
    // need to set the BPM according to the animation
    switch(_activeAnimation){
        case A_RAINBOW:
        case A_RAINBOW_GLITTER:
        {
            _minBPM = RAINBOW_HUE_INDEX_BPM_MIN;
            _maxBPM = RAINBOW_HUE_INDEX_BPM_MAX;
            break;
        }
        case A_PALETTE:
        case A_PALETTE_GLITTER:
        {
            _minBPM = PALETTE_HUE_INDEX_BPM_MIN;
            _maxBPM = PALETTE_HUE_INDEX_BPM_MAX;
            break;
        }
        case A_CONFETTI:
        case A_SINELON:
        case A_SINELON_DUAL:
        {
            _minBPM = SINELON_PIXEL_INDEX_BPM_MIN;
            _maxBPM = SINELON_PIXEL_INDEX_BPM_MAX;            
            break;
        }        
        default:
        {
            _minBPM = NORMAL_HUE_INDEX_BPM;
            _maxBPM = NORMAL_HUE_INDEX_BPM*6;
            break;
        }
    }

    // update our _bpm variable based on all of our bpm related variables
    updateBPM();

}


// update our _bpm variable based on all of our bpm related variables
void LEDStripController::updateBPM(){

    _bpm = _minBPM + (uint8_t)((_speedIndex / (float)(NUM_SPEED_LEVELS - 1)) * (_maxBPM - _minBPM));

}




// the glitter function, randomly selects a pixel and sets it to white (aka glitter)
void LEDStripController::addGlitter( fract8 chanceOfGlitter ) {
  if( random8() < chanceOfGlitter) {
    _leds[ random16(_stripLength) ] += CRGB::White;
    //_leds[ random16(_stripLength) ] = CHSV( 0, 0, brightness);
  }
}


// get the next hue based on the bpm and if the strip is inverted or not
uint8_t LEDStripController::getHueIndex(uint8_t bpm, uint8_t direction){

    if(direction == NORMAL_HUE_INDEX_DIRECTION){
        return beat8(bpm);
    }
    else {
        return 255 - beat8(bpm);
    }    
}





// **********************************************************
//      OTHER HELPER METHODS
// **********************************************************
