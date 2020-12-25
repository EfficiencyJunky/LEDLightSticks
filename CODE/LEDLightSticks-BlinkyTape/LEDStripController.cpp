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
    _brightness = INITIAL_BRIGHTNESS;
    _brightness = FULL_BRIGHT;
    _saturation = FULL_SAT;
    _paletteHue = 0;
    _colorPalette = colorPalette;


    // **********************************************************
    //      STRIP STATE VARIABLES
    // **********************************************************    
    _state = NORMAL_OPERATION;
    _showBrightnessColor = CRGB::Blue;
    _width = _stripLength;
    _center = stripLength / 2;


    // **********************************************************
    //      ANIMATIOIN SPECIFIC VARIABLES
    // **********************************************************
    _activeAnimationIndex = 0;
    _bpm = GLOBAL_BPM;
    _bsTimebase = 0;
    _glitter = false;
    _forward = true;
    _heat = new byte[stripLength];

    _numAnimations = 2;
    _animations = new Animation[_numAnimations];
    _animations[0] = &LEDStripController::rainbow;
    // _animations[1] = &LEDStripController::rainbowWithGlitter;
    _animations[1] = &LEDStripController::palette;
    // _animations[3] = &LEDStripController::paletteWithGlitter;
    // _animations[3] = &LEDStripController::confetti;
    // _animations[4] = &LEDStripController::sinelon;
    // _animations[5] = &LEDStripController::sinelonDual;


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
                (this->*(_animations[_activeAnimationIndex]))();
                break;
            }
            case STATE_TRANSITION:
            {
                fastBlink();
                break;
            }
            case SHOW_BRIGHTNESS_LEVEL:
            {
                setStripCHSV(CHSV( 92*2, FULL_SAT, _brightness));
                break;
            }
            case SHOW_SPEED_LEVEL:
            {
                setStripCHSV(CHSV( _bpm*2, FULL_SAT, _brightness));
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

    _activeAnimationIndex++;

    if(_activeAnimationIndex >= _numAnimations ){
    //if(_activeAnimationIndex >= 6){
        _activeAnimationIndex = 0;
    }


}


void LEDStripController::nextPalette(){

    Serial.print("BPM: ");
    Serial.println(_bpm);
    Serial.println("***********************");

}


void LEDStripController::nextBrightness(){

    if(_brightness <= MAX_BRIGHTNESS - BRIGHTNESS_INCREMENT){
        _brightness += BRIGHTNESS_INCREMENT;
    }
    else {
        _brightness = LOWEST_BRIGHTNESS;
    }

}


void LEDStripController::nextSpeed(){

    _bpm += SPEED_INCREMENT;

    // if our current BPM is greater than the max speed defined by number of speeds, speed increment, and base speed
    if(_bpm >= PALETTE_BPM + (NUM_SPEEDS * SPEED_INCREMENT) ){
        _bpm = PALETTE_BPM;
    }
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

    // mimmick led strip animation with rainbow + glitter
    if(_invertStrip){
        _paletteHue++;
    }
    else{
        _paletteHue--;
    }
    
    _paletteHue = beat8(_bpm);

    fill_rainbow( _leds, _stripLength, _paletteHue, 7);

    if(_activeAnimationIndex > 3){
        addGlitter(80);
    }


}


void LEDStripController::palette(){

    // mimmick led strip animation with rainbow + glitter
    if(_invertStrip){
        _paletteHue++;
    }
    else{
        _paletteHue--;
    }
    
    fill_palette( _leds, _stripLength, _paletteHue, 7, _colorPalette, 255, LINEARBLEND);
    // fill_rainbow( _leds, _stripLength, _paletteHue, 7);
}

// the glitter function, randomly selects a pixel and sets it to white (aka glitter)
void LEDStripController::addGlitter( fract8 chanceOfGlitter ) {
  if( random8() < chanceOfGlitter) {
    _leds[ random16(_stripLength) ] += CRGB::White;
    //_leds[ random16(_stripLength) ] = CHSV( 0, 0, brightness);
  }
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
  
  _paletteHue++;
  
  fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!
  uint16_t pos = random16(_stripLength);  

  // here's an alternate method that just cycles through the rainbow  
  _leds[pos] += CHSV( _paletteHue + random8(64), 200, FULL_BRIGHT); //, _brightness);
  
}


// Pop and Fade. like confetti!!! random colored speckles that blink in and fade smoothly
void LEDStripController::confettiFromPalette() {
  
  _paletteHue++;
  
  fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!
  uint16_t pos = random16(_stripLength);  
  
  // if you want to draw from a palette use this method
  _leds[pos] += ColorFromPalette( _colorPalette, _paletteHue + random8(64), FULL_BRIGHT); //, _brightness);
  //_leds[pos] += ColorFromPalette( _colorPalette, random8(), FULL_BRIGHT); //, _brightness);
  
}


// a colored dot sweeping back and forth, with fading trails
void LEDStripController::sinelon(){

    _paletteHue++;

    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!

    uint16_t pos = beatsin16( 13, 0, _stripLength - 1 );

    _leds[pos] += CHSV( _paletteHue, 255, FULL_BRIGHT);

}


// a colored dot sweeping back and forth, with fading trails
void LEDStripController::sinelonDual(){

    _paletteHue++;

    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!

    uint16_t pos1 = beatsin16( 13, 0, floor(_stripLength/2.0) - 1 );
    uint16_t pos2 = beatsin16( 13, ceil(_stripLength/2.0) - 1, _stripLength - 1 );

    _leds[pos1] += CHSV( _paletteHue, 255, FULL_BRIGHT);
    _leds[pos2] += CHSV( _paletteHue, 255, FULL_BRIGHT);

}