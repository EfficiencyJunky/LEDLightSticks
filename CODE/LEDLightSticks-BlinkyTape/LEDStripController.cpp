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
#include "GradientPalettes.h"
#include "HardwareDefinitions.h"

// **********************************************************
//      STATIC MEMBER DEFINITIONS
// **********************************************************



// ********* THE 3 DATA STRUCTURES BELOW ARE THE CODE FOR THE CURRENT VERSION OF THE VR HEADSET ******
#if defined(__VR_HEADSET__)
    //******* ORDER OF ANIMATIONS ********
    // this is how we set the order in which animations actually appear
    const Animations LEDStripController::animationsToUse[] = {
                                                                A_PALETTE,
                                                                A_PALETTE_GLITTER,
                                                                A_CONFETTI,
                                                                A_COLORWAVES,
                                                                A_VR_ANIMATION_01,
                                                                A_VR_ANIMATION_02,
                                                                A_VR_ANIMATION_03,
                                                            };


    //******* ORDER OF COLOR PALETTES ********
    // ARRAY OF GRADIENT PALETTES FOR ALL OUR USUAL ANIMATIONS
    const TProgmemRGBGradientPalettePtr LEDStripController::COLOR_PALETTES[] = {
                                                                    tk_vr_headset_01_gp
                                                                };



    // ARRAY OF ALL GRADIENT PALETTES FOR COLORWAVE ANIMATION
    const TProgmemRGBGradientPalettePtr LEDStripController::CW_PALETTES[] = {    
        tk_vr_headset_02_gp 
    };



#else

    // ********* THE 3 DATA STRUCTURES BELOW ARE THE CODE FOR THE CURRENT VERSION OF THE LED LIGHT STICKS ******

    //******* ORDER OF ANIMATIONS ********
    // this is how we set the order in which animations actually appear
    const Animations LEDStripController::animationsToUse[] = {
                                                                // A_RAINBOW,
                                                                // A_RAINBOW_GLITTER,
                                                                A_PALETTE,
                                                                A_PALETTE_GLITTER,
                                                                // A_BPM,
                                                                A_CONFETTI,
                                                                A_SINELON,
                                                                A_SINELON_DUAL,
                                                                A_JUGGLE,
                                                                A_PRIDE,
                                                                A_COLORWAVES,
                                                                A_FIRE,
                                                                A_CYCLE_ALL,
                                                                A_SOLID_COLOR,
                                                                // A_PRIDE_GLITTER
                                                                // A_DEVIN_ANIMATION,
                                                            };


    //******* ORDER OF COLOR PALETTES ********
    // ARRAY OF GRADIENT PALETTES FOR ALL OUR USUAL ANIMATIONS
    const TProgmemRGBGradientPalettePtr LEDStripController::COLOR_PALETTES[] = {
                                                                    tk_Rainbow_gp,
                                                                    tk_Peacock_Colors_gp,
                                                                    Analogous_1_gp,
                                                                    tk_Fire_Multi_Pink_gp,
                                                                    Sunset_Real_gp,
                                                                    tk_Party_gp,
                                                                    rainbowsherbet_gp,
                                                                    ib_jul01_gp,
                                                                    tricias_Fairy_Fire_gp,
                                                                    tricias_Fairy_Wings_gp
                                                                };


    // ARRAY OF ALL GRADIENT PALETTES FOR COLORWAVE ANIMATION
    const TProgmemRGBGradientPalettePtr LEDStripController::CW_PALETTES[] = {    
        es_autumn_19_gp,
        es_emerald_dragon_08_gp,
        es_landscape_64_gp,
        es_landscape_33_gp,
        Blue_Cyan_Yellow_gp,
        Coral_reef_gp,
        gr65_hult_gp,
        ib15_gp,
        Analogous_1_gp,
        tricias_Fairy_Wings_gp,
        es_pinksplash_07_gp,
        rgi_15_gp,
        
        // here's all the color palettes from the normal COLOR_PALETTES array
        // tk_Rainbow_gp,
        tk_Peacock_Colors_gp,
        tk_Fire_Multi_Pink_gp,
        Sunset_Real_gp,
        tk_Party_gp,
        rainbowsherbet_gp,
        ib_jul01_gp,
        tricias_Fairy_Fire_gp,
        tricias_Fairy_Wings_gp    
    };

#endif








// ARRAY OF FIRE ANIMATIONS FOR FIRE ANIMATION
//   uint8_t hue = whatever_color_you_want;
//   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
//   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
//   CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);
const TProgmemRGBGradientPalettePtr LEDStripController::FIRE_PALETTES[] = {    
    tk_Fire_Candle_gp,
    tk_Fire_Red_gp,
    tk_Fire_Blue_gp,
    tk_Fire_Green_gp,
    tk_Fire_Pink_gp,
    tk_Fire_Multi_Pink_gp,
    tricias_Fairy_Fire_gp
};





//******* ORDER OF SOLID COLORS ********
// based off of the FastLED specification for HSV colors in the "Rainbow" color space
const uint8_t LEDStripController::SOLID_COLORS[] = {
                                                        0,    // red
                                                        32,   // orange
                                                        64,   // yellow
                                                        96,   // green
                                                        128,  // aqua
                                                        160,  // blue
                                                        192,  // purple
                                                        224,  // pink
                                                        255   // white
                                                    };


// using a static variable for saving the call to millis() in each of our functions
// saves a small amount of space and makes writing animation functions more uniform to use the same variable
uint8_t LEDStripController::numLEDStripControllers = 0;
uint8_t LEDStripController::sourceControllerExists = false;
uint32_t LEDStripController::ms_uint32 = 0;
uint8_t LEDStripController::s_assignStaticHeatArray = false;




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
                                        uint16_t stripStartIndex,
                                        uint16_t stripLength, 
                                        uint8_t invertStrip,
                                        StripControllerTypes stripType)
{

    // **********************************************************
    //      STRIP TYPE VARIABLES
    // **********************************************************    
    numLEDStripControllers++;

    // if this is the first SOURCE or REPLICA strip, and no SOURCE exists yet,
    // we need to force this one to be SOURCE and update sourceControllerExists to = "true"
    if( (stripType == SOURCE || stripType == REPLICA ) && sourceControllerExists == false ){
        _stripType = SOURCE;
        sourceControllerExists = true;
    }
    // otherwise if it is a source strip but one already exists, we set it to SOLO
    else if( stripType == SOURCE && sourceControllerExists ){
        _stripType = SOLO;
    }
    else{
        _stripType = stripType;
    }


    // **********************************************************
    //      STRIP DEFINITION VARIABLES
    // **********************************************************    
    _leds = &leds[stripStartIndex];
    _stripLength = stripLength;
    _invertStrip = invertStrip;    

    // **********************************************************
    //      TIME KEEPING AND STATE VARIABLES
    // ********************************************************** 
    _state = NORMAL_OPERATION;
    _timeToUpdate = 0;
    _updateInterval = DEFAULT_UPDATE_INTERVAL;
    _timeToCycleAnimations = 0; // only used for the cycle animation


    // **********************************************************
    //      STRIP STATE VARIABLES
    // **********************************************************    
    _hue = 0;
    _saturation = FULL_SAT;    
    _brightness = FULL_BRIGHT;  // this gets overwritten with our settings struct below
    _width = _stripLength;
    _center = _stripLength / 2;


    // **********************************************************
    //      ANIMATION SPECIFIC VARIABLES
    // **********************************************************
    _bsTimebase = 0;

    // if this a SOURCE strip or a SOLO strip, we need to allocate our f_Heat array    
    if(_stripType == SOURCE || _stripType == SOLO){
        f_Heat = new byte[_stripLength];
    }    
    // and then assign our static fire function s_Heat array to point to our newly allocated f_Heat
    if(_stripType == SOURCE){
        s_assignStaticHeatArray = true;
        fire2012WithPalette();
    }


    d_lfos = new LFO[_stripLength];

    for(uint16_t i=0; i < _stripLength; i++){
        d_lfos[i].rate = random8(13, 25);
        d_lfos[i].minb = random8(40, 80);
        d_lfos[i].maxb = random8(150, 255);
    }

    // we don't care about saving the cycleAnimation index so we just always start at 0
    cycle_activeAnimation = animationsToUse[ 0 ];

    // but we don't want to start at 0 if that happens to be the cycle animation itself or solid color
    if(cycle_activeAnimation == A_CYCLE_ALL || cycle_activeAnimation == A_SOLID_COLOR){
        cycle_activeAnimation = animationsToUse[ 1 ];
    }
    if(cycle_activeAnimation == A_CYCLE_ALL || cycle_activeAnimation == A_SOLID_COLOR){
        cycle_activeAnimation = animationsToUse[ 2 ];
    }

    // **********************************************************
    //    IMPORTANT VARIABLES DEPENDENT ON SETTINGS IN EEPROM
    // **********************************************************
    // LOAD OUR SETTINGS SAVED IN EEPROM into the stg struct
    loadAllSettingsFromEEPROM(&stg);

    // IMPORTANT: don't change these lines!!!
    // this is where we use the settings to initialize our program     
    _brightness = map(stg.brightnessLevel, 0, NUM_BRIGHTNESS_LEVELS - 1, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

    // this function initializes all the animation specific parameters
    _activeAnimation = animationsToUse[ stg.animationIndex ];
    initializeAnimation(_activeAnimation);


    // **********************************************************
    //    ARRAY OF ALL OUR ANIMATIONS -- !!! DON'T TOUCH THIS !!!
    // **********************************************************
    // LOAD THE AnimationFunction ARRAY WITH THE ENTIRE SET OF AVAILABLE Animations
    // !!!!! NOTE !!!!!
    // THIS ARRAY IS NOT IN ANY SPECIFIC ORDER. 
    // THE ORDER THE ANIMATIONS WILL APPEAR IS DEFINED BY THE "animationsToUse[]"" ARRAY
    // which is a static variable defined in the .cpp file
    _animationFunctions = new AnimationFunction[TOTAL_AVAILABLE_ANIMATIONS];
    _animationFunctions[A_RAINBOW]          = &LEDStripController::rainbow;
    _animationFunctions[A_RAINBOW_GLITTER]  = &LEDStripController::rainbowWithGlitter;
    _animationFunctions[A_PALETTE]          = &LEDStripController::palette;
    _animationFunctions[A_PALETTE_GLITTER]  = &LEDStripController::paletteWithGlitter;
    _animationFunctions[A_CONFETTI]         = &LEDStripController::confetti;
    _animationFunctions[A_SINELON]          = &LEDStripController::sinelon;
    _animationFunctions[A_SINELON_DUAL]     = &LEDStripController::sinelonDual;
    _animationFunctions[A_JUGGLE]           = &LEDStripController::juggle;
    _animationFunctions[A_BPM]              = &LEDStripController::bpm;
    _animationFunctions[A_FIRE]             = &LEDStripController::fire2012WithPalette;
    _animationFunctions[A_CYCLE_ALL]        = &LEDStripController::cycleThroughAllAnimations;
    _animationFunctions[A_SOLID_COLOR]      = &LEDStripController::solidColor;
    _animationFunctions[A_COLORWAVES]       = &LEDStripController::colorwaves;
    _animationFunctions[A_PRIDE]            = &LEDStripController::pride;
    _animationFunctions[A_PRIDE_GLITTER]    = &LEDStripController::prideWithGlitter;
    _animationFunctions[A_DEVIN_ANIMATION]  = &LEDStripController::devinAnimation;
    _animationFunctions[A_VR_ANIMATION_01]  = &LEDStripController::vrAnimation01;
    _animationFunctions[A_VR_ANIMATION_02]  = &LEDStripController::vrAnimation02;
    _animationFunctions[A_VR_ANIMATION_03]  = &LEDStripController::vrAnimation03;

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

    if(now_ms == 0){ ms_uint32 = millis(); }
    else{ ms_uint32 = now_ms; }

    if( ms_uint32 >= _timeToUpdate ){
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
                setStripCHSV(  CHSV( 180, FULL_SAT, _brightness)  );
                break;
            }
            case SHOW_SPEED_LEVEL:
            {
                setStripCHSV(  CHSV( 0, FULL_SAT, beatsin8(_bpm, MIN_BRIGHTNESS, MAX_BRIGHTNESS))  );
                break;
            }
            case SHOW_PALETTE:
            {
                // show the entire palette across the entire length of the strip
                fill_palette( _leds, _stripLength, 0, (256 / _stripLength) , _colorPalette, _brightness, LINEARBLEND);
                break;
            }
            case STRIP_OFF:
            {
                fadeToBlack();
                break;
            }
            default:
            {
                //(this->*(_animationFunctions[_activeAnimation]))();
                break; 
            }
        }

        _timeToUpdate = ms_uint32 + _updateInterval;
    }
}



/*--------------------------------------------------------------------------------------------------*
 *                          NEXT ANIMATION (PATTERN)                                                *
 *                                                                                                  *
 *--------------------------------------------------------------------------------------------------*/
// the technique used here means we don't need to save an animationIndex variable
// and the reason we don't want to do that is....because I just didn't want one more freaking variable!!
void LEDStripController::nextAnimation(){

    // increment the animation index and mod with the size of the animationsToUse array
    stg.animationIndex = addmod8( stg.animationIndex, 1, ARRAY_SIZE(animationsToUse));

    // save setting to EEPROM
    if(_stripType == SOURCE){
        saveSettingToEEPROM("animationIndex");
    }

    // assign the new animation
    _activeAnimation = animationsToUse[ stg.animationIndex ];
    
    // Initialize new animation
    initializeAnimation(_activeAnimation);

    return;

}



void LEDStripController::nextPalette(){


    switch(_activeAnimation){
        case A_SOLID_COLOR:
        {
            // if we're in SHOW_PALETTE mode, do the default behavior
            if(_state == SHOW_PALETTE){

                // increment the palette index and mod with the size of the COLOR_PALETTES array
                stg.paletteIndex = addmod8( stg.paletteIndex, 1, ARRAY_SIZE(COLOR_PALETTES));

                // save setting to EEPROM
                if(_stripType == SOURCE){                
                    saveSettingToEEPROM("paletteIndex");
                }

                // assign the new solid color
                _colorPalette = COLOR_PALETTES[stg.paletteIndex];

            }
            else{
                
                // increment the solid color index and mod with the size of the SOLID_COLORS array
                stg.solidColorIndex = addmod8( stg.solidColorIndex, 1, ARRAY_SIZE(SOLID_COLORS));

                if(_stripType == SOURCE){
                    // save setting to EEPROM
                    saveSettingToEEPROM("solidColorIndex");
                }

                if(stg.solidColorIndex == ARRAY_SIZE(SOLID_COLORS) - 1){
                    sc_Hue = SOLID_COLORS[ stg.solidColorIndex ];
                }
                else{
                    sc_Hue = SOLID_COLORS[ random(ARRAY_SIZE(SOLID_COLORS)) ];
                    // sc_Hue = SOLID_COLORS[ stg.solidColorIndex ];
                }
                
            }
       
            break;
        }
        case A_FIRE:
        {
            
            // increment the palette index and mod with the size of the FIRE_PALETTES array
            stg.firePaletteIndex = addmod8( stg.firePaletteIndex, 1, ARRAY_SIZE(FIRE_PALETTES));

            // save setting to EEPROM
            if(_stripType == SOURCE){
                saveSettingToEEPROM("firePaletteIndex");
            }

            // assign the new solid color
            _colorPalette = FIRE_PALETTES[ stg.firePaletteIndex ];

            break;
        }
        case A_COLORWAVES:
        {
            // if we're in SHOW_PALETTE mode, we want to swap the palette now
            if(_state == SHOW_PALETTE){
                // increment the palette index
                cw_PaletteIndex = addmod8( cw_PaletteIndex, 1, ARRAY_SIZE(CW_PALETTES));
            
                // // swap out the target palette
                _colorPalette = CW_PALETTES[ cw_PaletteIndex ];       

                // update the time we change to the next palette
                cw_timeToChangePalette = millis() + CW_PALETTE_CHANGE_INTERVAL;
            }
            // otherwise we just want to set the time to change palettes to now
            // and let the colorwaves animation function do the swapping
            else{
                cw_timeToChangePalette = millis();
            }

            break;
        }
        default:
        {
            
            // increment the palette index and mod with the size of the COLOR_PALETTES array
            stg.paletteIndex = addmod8( stg.paletteIndex, 1, ARRAY_SIZE(COLOR_PALETTES));

            // save setting to EEPROM
            if(_stripType == SOURCE){
                saveSettingToEEPROM("paletteIndex");
            }

            // assign the new solid color
            _colorPalette = COLOR_PALETTES[stg.paletteIndex];
     
            break;
        }
    }

}



void LEDStripController::nextBrightness(){

    stg.brightnessLevel = addmod8( stg.brightnessLevel, 1, NUM_BRIGHTNESS_LEVELS); 

    _brightness = map(stg.brightnessLevel, 0, NUM_BRIGHTNESS_LEVELS - 1, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

    if(_stripType == SOURCE){
        saveSettingToEEPROM("brightnessLevel");
    }

}


void LEDStripController::nextSpeed(){
    
    stg.speedLevel = addmod8( stg.speedLevel, 1, NUM_SPEED_LEVELS);

    updateBPM();

    if(_stripType == SOURCE){
        saveSettingToEEPROM("speedLevel");
    }

}

// initializes any parameters that rely on random numbers to be set up correctly
void LEDStripController::initRandomParams(){
    cw_PaletteIndex = random( ARRAY_SIZE(CW_PALETTES) );

    if(_activeAnimation == A_COLORWAVES){
        initializeAnimation(_activeAnimation);
    }
}


void LEDStripController::setBrightness(uint8_t brightness){
    _brightness = brightness;
}




void LEDStripController::setOperationState(StripControllerStates newState){

    _state = newState;

    String s_newState;

    switch(_state){
        case NORMAL_OPERATION:
        {
            s_newState = "NORMAL_OPERATION";
            break;
        }
        case STATE_TRANSITION:
        {
            s_newState = "STATE_TRANSITION";
            _bsTimebase = millis();
            break;
        }
        case SHOW_BRIGHTNESS_LEVEL:
        {
            s_newState = "SHOW_BRIGHTNESS_LEVEL";
            break;
        }
        case SHOW_SPEED_LEVEL:
        {
            s_newState = "SHOW_SPEED_LEVEL";
            break;
        }        
        case SHOW_PALETTE:
        {
            s_newState = "SHOW_PALETTE";
            break;
        }
        case STRIP_OFF:
        {
            s_newState = "STRIP_OFF";
            break;
        }                
        default:
        {
            s_newState = "unknown_state";
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
    static uint8_t blinkBPM = 60;
    uint8_t sin60bpm = beatsin8(blinkBPM, 0, 255, _bsTimebase, 256 / 2 - 1);
    if (sin60bpm > 127) {
        fill_solid( _leds, _stripLength, CHSV( 255, 0, 80) );
    } 
    else {
        fill_solid( _leds, _stripLength, CRGB::Black );
    }
}


// set strip to color based on CHSV input
void LEDStripController::setStripCHSV(CHSV newCHSV) {

    fill_solid( _leds, _stripLength, newCHSV );
}


// set strip to color based on CRGB input
void LEDStripController::setStripCRGB(CRGB newCRGB) {

    fill_solid( _leds, _stripLength, newCRGB );
}



// set strip to color based on CRGB input
void LEDStripController::fadeToBlack() {

    fadeToBlackBy( _leds, _stripLength, 10); // MAGIC NUMBER ALERT!!!
}






/*--------------------------------------------------------------------------------------------------*
 *                          PLACEHOLDER                                                             *
 *                                                                                                  *
 *--------------------------------------------------------------------------------------------------*/
void LEDStripController::rainbow(){    

    // fill_palette( _leds, _stripLength, getHueIndex(_bpm), 7, RainbowColors_p, _brightness, LINEARBLEND);
    fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, RainbowColors_p, _brightness, LINEARBLEND);
}


void LEDStripController::palette(){

    // this sets the number of colors in a color palette to skip between LED indexes
    // essentially the width of the palette to be shown across the strip
    // lower numbers have wider fill and higher numbers have tighter fill
    static uint8_t incrementIndex = 1;

    // if the color palette is rainbow, spread it evenly across the entire strip
    if(_colorPalette == (CRGBPalette16)tk_Rainbow_gp){
        incrementIndex = (256 / _stripLength) + 1;
    }
    // otherwise, lock our incrementIndex to 3 (this will spread the color palette wider than the strip if it's less than 85 LEDs)
    else{
        incrementIndex = 3;
    }

    // fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _colorPalette, _brightness, LINEARBLEND);
    fill_palette( _leds, _stripLength, getHueIndex(_bpm), incrementIndex, _colorPalette, _brightness, LINEARBLEND);
}


// same as the above rainbow function except this also ads glitter
void LEDStripController::rainbowWithGlitter() {
  // reference our rainbow function, plus some random sparkly glitter
  rainbow();
  addGlitter(80, _brightness, 100); // MAGIC NUMBER ALERT!!!
}

// same as the above palette function except this also ads glitter
void LEDStripController::paletteWithGlitter() {
  // reference our palette function, plus some random sparkly glitter
  palette();
  addGlitter(80, _brightness, 100); // MAGIC NUMBER ALERT!!!
}




// Pop and Fade. like confetti!!! random colored speckles that blink in and fade smoothly
void LEDStripController::confetti() {
  
    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!
    uint16_t pos = random16(_stripLength);  
    uint8_t randNum = random8();

    if( (randNum > (20 * numLEDStripControllers) ) || randNum > 127 ){ // MAGIC NUMBER ALERT!!!
        // this method that just cycles through the rainbow and     
        // uses qadd8 to clamp the addition of _brightness+40 to a max of 255
        // then converts the rgb value to CHSV
        CHSV newColor = rgb2hsv_approximate( ColorFromPalette( _colorPalette, getHueIndex(NORMAL_HUE_INDEX_BPM) + random8(24), qadd8(_brightness, 40 )) );// MAGIC NUMBER ALERT!!!
        
        // drop the saturation
        newColor.saturation = 200; // MAGIC NUMBER ALERT!!!
        
        // add to the mix
        _leds[pos] += newColor;
    }
}





// a colored dot sweeping back and forth, with fading trails
void LEDStripController::sinelon(){

    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!

    uint16_t pos = beatsin16( _bpm, 0, _stripLength - 1 );

    if( _invertStrip ) {
        pos = (_stripLength-1) - pos;
    }

    _leds[pos] += ColorFromPalette( _colorPalette, getHueIndex(NORMAL_HUE_INDEX_BPM), qadd8(_brightness, 40 ));
    // _leds[pos] += CHSV( getHueIndex(NORMAL_HUE_INDEX_BPM), 255, FULL_BRIGHT);

}


// a colored dot sweeping back and forth, with fading trails
void LEDStripController::sinelonDual(){

    fadeToBlackBy( _leds, _stripLength, 20); // MAGIC NUMBER ALERT!!!

    uint16_t pos1 = beatsin16( _bpm, 0, floor(_stripLength/2.0) - 1 );
    uint16_t pos2 = beatsin16( _bpm, ceil(_stripLength/2.0) - 1, _stripLength - 1 );

    if( _invertStrip ) {
        pos1 = (_stripLength-1) - pos1;
        pos2 = (_stripLength-1) - pos2;
    }
    
    _leds[pos1] += ColorFromPalette( _colorPalette, getHueIndex(NORMAL_HUE_INDEX_BPM), qadd8(_brightness, 40 ));
    _leds[pos2] += ColorFromPalette( _colorPalette, getHueIndex(NORMAL_HUE_INDEX_BPM), qadd8(_brightness, 40 ));

    // _leds[pos1] += CHSV( getHueIndex(NORMAL_HUE_INDEX_BPM), 255, FULL_BRIGHT);
    // _leds[pos2] += CHSV( getHueIndex(NORMAL_HUE_INDEX_BPM), 255, FULL_BRIGHT);

}


void LEDStripController::juggle() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy( _leds, _stripLength, 20);

    byte dothue = 0;

    for( uint16_t i = 0; i < 8; i++) {

        CHSV newColor = rgb2hsv_approximate( ColorFromPalette( _colorPalette, dothue, qadd8(_brightness, 40 )) );// MAGIC NUMBER ALERT!!!

        // drop the saturation
        newColor.saturation = 200;

        // get the position in the strip
        uint16_t pos = beatsin16( i+_bpm, 0, _stripLength - 1 );

        if( _invertStrip ) {
          pos = (_stripLength-1) - pos;

        }        

        // add to the mix
        _leds[pos] |= newColor;
        
        // original way of doing it without dropping saturation
        //_leds[beatsin16( i+7, 0, _stripLength - 1 )] |= CHSV(dothue, 200, qadd8(_brightness, 40 ));
        
        dothue += 32;
    }
}


void LEDStripController::bpm(){
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    // uint8_t beatsPerMinute = 62;
    uint8_t beatsPerMinute = _bpm + 50;

    uint8_t beat = beatsin8( beatsPerMinute, 64, 255);
    
    uint8_t hue = getHueIndex(_bpm);
    // uint8_t hue = getHueIndex(NORMAL_HUE_INDEX_BPM);
    

    for( uint16_t i = 0; i < _stripLength; i++) { //9948
        _leds[i] = ColorFromPalette( _colorPalette, hue+(i*2), scale8_video(beat-hue+(i*10), _brightness) );
    }
}



void LEDStripController::fire2012WithPalette() {

    // *********** THIS HAPPENS ONCE  ***********
    // -- setup our static function member s_Heat array
    static byte *s_Heat;

    // this is where we initialize our static function member s_Heat array
    // we only call this once during the constructor of the SOURCE strip
    // all we are doing is setting the s_Heat pointer to point at the 
    // SOURCE strip's instance member f_Heat array so that it can be used by other REPLICA strips
    if(_stripType == SOURCE && s_assignStaticHeatArray){
        s_Heat = f_Heat;
        s_assignStaticHeatArray = false;
        return;
    }
    else if(_stripType == REPLICA && s_assignStaticHeatArray){
        return;
    }


    // *********** EVERYTHING BELOW THIS HAPPENS EACH TIME ***********
    // we'll use a temporary pointer to perform the necessary updates to our strip
    byte *heat;

    // if this is a SOURCE or SOLO strip, assign our heat array to point to the instance member array
    if(_stripType == SOURCE || _stripType == SOLO){
        heat = f_Heat;
    }
    // if this is a REPLICA strip, assign our heat array to point to the static function array
    else if(_stripType == REPLICA){        
        heat = s_Heat;
    }


    // if we are the SOURCE or SOLO strip, we need to actually update the heat array
    // otherwise we will just use the s_Heat array that's already been updated
    if(_stripType == SOURCE || _stripType == SOLO){

        // Fourth, the most sophisticated: this one sets up a new palette every
        // time through the loop, based on a hue that changes every time.
        // The palette is a gradient from black, to a dark color based on the hue,
        // to a light color based on the hue, to white.
        //
        //   static uint8_t hue = 0;
        //   hue++;
        //   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
        //   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
        //   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);

        // Array of temperature readings at each simulation cell
        // Since this is in a class now, the heat array has been declared as a class member
        //  static byte heat[_stripLength];

        // Step 1.  Cool down every cell a little
        for( uint16_t i = 0; i < _stripLength; i++) {
            heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / _stripLength) + 2));
        }

        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( uint16_t k= _stripLength - 1; k >= 2; k--) {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
        }
        
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < SPARKING ) {
            uint16_t y = random8(7);
            heat[y] = qadd8( heat[y], random8(160,255) );
        }

    }


    // Step 4.  Map from heat cells to LED colors
    for( uint16_t j = 0; j < _stripLength; j++) {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        byte colorindex = scale8( heat[j], 240);
        CRGB color = ColorFromPalette( _colorPalette, colorindex, _brightness); // qadd8(_brightness, 40 ));
        
        uint16_t pixelIndex;
        
        if( _invertStrip ) {
            pixelIndex = (_stripLength-1) - j;
        } else {
            pixelIndex = j;
        }
        
        _leds[pixelIndex] = color;
    
    }


}

void LEDStripController::cycleThroughAllAnimations(){


    (this->*(_animationFunctions[cycle_activeAnimation]))();

    
    ms_uint32 = millis();

    // every 10 seconds we switch the animation    
    if( ms_uint32 >= _timeToCycleAnimations ){

        // this method doesn't require us to save an index variable for the cycle animation
        for(uint8_t i = 0; i < ARRAY_SIZE(animationsToUse); i++){
            
            if(animationsToUse[i] == cycle_activeAnimation){
                cycle_activeAnimation = animationsToUse[(i + 1) % ARRAY_SIZE(animationsToUse)];   

                // if the next cycle_activeAnimation is the cycle animation this will break the program
                // so we want to skip it. We also want to skip solidColor because it's not doing anything
                // so that's why we have two if statements here. In case the two are right after eachother.
                if(cycle_activeAnimation == A_CYCLE_ALL || cycle_activeAnimation == A_SOLID_COLOR){
                    cycle_activeAnimation = animationsToUse[(i + 2) % ARRAY_SIZE(animationsToUse)];
                }
                if(cycle_activeAnimation == A_CYCLE_ALL || cycle_activeAnimation == A_SOLID_COLOR){
                    cycle_activeAnimation = animationsToUse[(i + 3) % ARRAY_SIZE(animationsToUse)];
                }
                break;
            }
        }    

        initializeAnimation(cycle_activeAnimation);

        _timeToCycleAnimations = ms_uint32 + CYCLE_ANIMATION_CHANGE_INTERVAL;
    }
}


void LEDStripController::solidColor() {

    CRGB newColor;

    // if it's white and we have more than one strip controller
    // we want to set one strip controller to full white brightness and the other to black
    // this will make the LED stick act as a semi directional flashlight
    if(sc_Hue == 255 && numLEDStripControllers > 1 && stg.solidColorIndex == ARRAY_SIZE(SOLID_COLORS) - 1){
        if(_stripType == SOURCE){
            newColor = CHSV( sc_Hue, 0, _brightness );
        }
        else if(_stripType == REPLICA){
            newColor = CRGB::Black;
        }
        else{ // if(_stripType == SOLO){
            newColor = CHSV( sc_Hue, 0, scale8(_brightness, MAX_BRIGHTNESS * 0.85) );
            // newColor = CHSV( 240, 255, _brightness ); // for testing
        }
    }
    else if(sc_Hue == 255){
        newColor = CHSV( sc_Hue, 0, scale8(_brightness, MAX_BRIGHTNESS * 0.85) );
    }
    else{
        newColor = CHSV( sc_Hue, FULL_SAT, _brightness);
    }


    setStripCRGB(newColor);

}


// this animation adapted from the original by Mark Kriegsman
// https://gist.github.com/kriegsman/8281905786e8b2632aeb
// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void LEDStripController::colorwaves() {

    ms_uint32 = millis();

    uint8_t brightdepth = beatsin88( 341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = cwp_sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 300, 1500);

    // not sure why it was decided to use uint16_t variables but maybe to save space?
    uint16_t ms = ms_uint32;
    uint16_t deltams = ms - cwp_sLastMillis;
    cwp_sLastMillis  = ms;
    cwp_sPseudotime += deltams * msmultiplier;
    cwp_sHue16 += deltams * beatsin88( 400, 5,9);
    uint16_t brightnesstheta16 = cwp_sPseudotime;

    for( uint16_t i = 0 ; i < _stripLength; i++) {
        hue16 += hueinc16;
        uint8_t hue8 = hue16 / 256;
        uint16_t h16_128 = hue16 >> 7;
        if( h16_128 & 0x100) {
            hue8 = 255 - (h16_128 >> 1);
        } else {
            hue8 = h16_128 >> 1;
        }

        brightnesstheta16  += brightnessthetainc16;
        uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        uint8_t index = hue8;
        //index = triwave8( index);
        index = scale8( index, 240);

        // scale the brightness but maximize the high end potential
        CRGB newcolor = ColorFromPalette( cw_Palette, index, scale8_video(bri8, qadd8(_brightness, 255 - MAX_BRIGHTNESS )) );
        
        uint16_t pixelIndex;

        if( _invertStrip ) {
            pixelIndex = i;
        } else {
            pixelIndex = (_stripLength-1) - i;
        }

        nblend( _leds[pixelIndex], newcolor, 128);
    }

    
    // ***** ADDITIONAL TIMING - PALETTE UPDATES **********    
    if( ms_uint32 >= cw_timeToChangePalette ){
        
        cw_PaletteIndex = addmod8( cw_PaletteIndex, 1, ARRAY_SIZE(CW_PALETTES));
        
        _colorPalette = CW_PALETTES[ cw_PaletteIndex ];       

        cw_timeToChangePalette = ms_uint32 + CW_PALETTE_CHANGE_INTERVAL; // add 20 seconds in ms
    }
    if( ms_uint32 >= cw_timeToBlendPalettes ){

        // nblendPaletteTowardPalette( gCurrentPalette, _colorPalette, CW_PALETTE_BLEND_INCREMENT);
        nblendPaletteTowardPalette( cw_Palette, _colorPalette, CW_PALETTE_BLEND_INCREMENT);

        cw_timeToBlendPalettes = ms_uint32 + 40; // add 40 ms
    }

}

// this animation adapted from the original by Mark Kriegsman
// https://gist.github.com/kriegsman/964de772d64c502760e5
// This function draws rainbows with an ever-changing,
// widely-varying set of parameters.
void LEDStripController::pride() 
{

    ms_uint32 = millis();
    
    uint8_t sat8 = beatsin88( 87, 220, 250);
    uint8_t brightdepth = beatsin88( 341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = cwp_sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 1, 3000);
    
    uint16_t ms = ms_uint32;
    uint16_t deltams = ms - cwp_sLastMillis ;
    cwp_sLastMillis  = ms;
    cwp_sPseudotime += deltams * msmultiplier;
    cwp_sHue16 += deltams * beatsin88( 400, 5,9);
    uint16_t brightnesstheta16 = cwp_sPseudotime;
  
    for( uint16_t i = 0 ; i < _stripLength; i++) {
        hue16 += hueinc16;
        uint8_t hue8 = hue16 / 256;

        brightnesstheta16  += brightnessthetainc16;
        uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);
        
        p_bri8 = scale8_video(bri8, qadd8(_brightness, 255 - MAX_BRIGHTNESS ));
        
        CRGB newcolor = CHSV( hue8, sat8, p_bri8);

        uint16_t pixelIndex;

        if( _invertStrip ) {
            pixelIndex = i;
        } else {
            pixelIndex = (_stripLength-1) - i;
        }        
        
        nblend( _leds[pixelIndex], newcolor, 64);
    }
    

}


// same as the above pride function except this also ads glitter
void LEDStripController::prideWithGlitter() {
    // reference our pride function, plus some random sparkly glitter
    pride();
    uint8_t brightnessToAdd = 0;
    
    if(_brightness < 100){
        brightnessToAdd = 50;
    }
    if(_brightness < 150){
        brightnessToAdd = 30;
    }
    addGlitter(30, _brightness, brightnessToAdd); // MAGIC NUMBER ALERT!!!
    
    // if(p_bri8 < 150){
    //     brightnessToAdd = 50;
    // }

    // addGlitter(50, p_bri8, brightnessToAdd); // MAGIC NUMBER ALERT!!!
}



// **********************************************************
//      TESTING NEW ANIMATIONS HERE
// **********************************************************
// ABRACADABRA
// Alternate rendering function just scrolls the current palette 
// across the defined LED strip.
// void LEDStripController::palettetest(){
void LEDStripController::gradientPalettesTest(){
//   static uint8_t startindex = 0;
//   startindex--;

    fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _colorPalette, 255, LINEARBLEND);
    // fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _gradientTestPalette, 255, LINEARBLEND);
    //fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _gradientTestPalette, 255, LINEARBLEND);
}



// a re-creation of Devin Smith's LFO animation
void LEDStripController::devinAnimation(){

    ms_uint32 = millis();

    uint8_t brightness;

    uint8_t hueIndex = (beatsin8(2, 1, 255) * beatsin8(2, 10, 50)) / 50;

    for(uint16_t i=0; i < _stripLength; i++){
        
        brightness = beatsin8(d_lfos[i].rate * (stg.speedLevel+1), d_lfos[i].minb, d_lfos[i].maxb );
        // brightness = beatsin8(d_lfotest.rate * (stg.speedLevel+1), d_lfotest.minb, d_lfotest.maxb );


        // CRGB newcolor = ColorFromPalette( cw_Palette, i * (256 / _stripLength)+ hueIndex, scale8(brightness, _brightness));
        // nblend( _leds[i], newcolor, 128);

        // _leds[i] = CHSV( 95*2, FULL_SAT, brightness);
        _leds[i] = ColorFromPalette( cw_Palette, i * (256 / _stripLength) + hueIndex, scale8(brightness, _brightness));


        // CRGB newcolor = CHSV( 95*2, FULL_SAT, brightness);
        // ledStrip[i] = ColorFromPalette( _colorPalette, i * (256 / _stripLength), scale8(brightness, _brightness));
        // _leds[i] = ColorFromPalette( _colorPalette, i * (256 / _stripLength), brightness);
        // _leds[i] = CHSV( 95*2, FULL_SAT, brightness);
    }

    // ***** ADDITIONAL TIMING - PALETTE UPDATES **********
    // it was probably a bad idea to use the ms from this function since it is a uint16_t but oh well
    if( ms_uint32 >= cw_timeToChangePalette ){
        
        d_PaletteIndex = addmod8( d_PaletteIndex, 1, ARRAY_SIZE(CW_PALETTES));
        
        _colorPalette = CW_PALETTES[ d_PaletteIndex ];       

        cw_timeToChangePalette = ms_uint32 + DEVIN_PALETTE_CHANGE_INTERVAL; // add 20 seconds in ms
    }
    if( ms_uint32 >= cw_timeToBlendPalettes ){

        // nblendPaletteTowardPalette( gCurrentPalette, _colorPalette, CW_PALETTE_BLEND_INCREMENT);
        nblendPaletteTowardPalette( cw_Palette, _colorPalette, CW_PALETTE_BLEND_INCREMENT);

        cw_timeToBlendPalettes = ms_uint32 + 40; // add 40 ms
    }



}



void LEDStripController::vrAnimation01(){
//   static uint8_t startindex = 0;
//   startindex--;

    fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _colorPalette, _brightness, LINEARBLEND);
    // fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _gradientTestPalette, 255, LINEARBLEND);
    //fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _gradientTestPalette, 255, LINEARBLEND);
}



// a re-creation of Devin Smith's LFO animation adapted for the VR Headset
// this spreads the whole palette across the entire strip
void LEDStripController::vrAnimation02() {
  
    ms_uint32 = millis();

    uint8_t brightness;

    uint8_t hueIndex = (beatsin8(2, 1, 255) * beatsin8(2, 10, 50)) / 50;

    for(uint16_t i=0; i < _stripLength; i++){
        
        brightness = beatsin8(d_lfos[i].rate * (stg.speedLevel+1), d_lfos[i].minb, d_lfos[i].maxb );

        _leds[i] = ColorFromPalette( cw_Palette, i * (256 / _stripLength) + hueIndex, scale8(brightness, _brightness));
        // _leds[i] = ColorFromPalette( cw_Palette, hueIndex, scale8(brightness, _brightness));

    }

}



// a re-creation of Devin Smith's LFO animation adapted for the VR Headset 
// this one uses the same color for the entire strip
void LEDStripController::vrAnimation03() {
  
    ms_uint32 = millis();

    uint8_t brightness;

    uint8_t hueIndex = (beatsin8(2, 1, 255) * beatsin8(2, 10, 50)) / 50;

    for(uint16_t i=0; i < _stripLength; i++){
        
        brightness = beatsin8(d_lfos[i].rate * (stg.speedLevel+1), d_lfos[i].minb, d_lfos[i].maxb );

        // _leds[i] = ColorFromPalette( cw_Palette, i * (256 / _stripLength) + hueIndex, scale8(brightness, _brightness));
        _leds[i] = ColorFromPalette( cw_Palette, hueIndex, scale8(brightness, _brightness));

    }

}





// **********************************************************
//      ANIMATION HELPER METHODS
// **********************************************************

// if an animation uses BPM, then we need to set _minBPM, _maxBPM here
// and the call to "setBPM()" will initialize our _bpm
void LEDStripController::initializeAnimation(Animations animationToInitialize){

    ms_uint32 = millis();

    // general settings used in most of our animations
    _updateInterval = DEFAULT_UPDATE_INTERVAL;
    _minBPM = NORMAL_HUE_INDEX_BPM;
    _maxBPM = NORMAL_HUE_INDEX_BPM * NUM_SPEED_LEVELS;    
    _colorPalette = COLOR_PALETTES[ stg.paletteIndex ];
    
    // need to set the BPM according to the animation
    switch(animationToInitialize){
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
            _minBPM = RAINBOW_HUE_INDEX_BPM_MIN + PALETTE_HUE_INDEX_BPM_ADD;
            _maxBPM = RAINBOW_HUE_INDEX_BPM_MAX + PALETTE_HUE_INDEX_BPM_ADD;
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
        case A_JUGGLE:
        {
            _minBPM = SINELON_PIXEL_INDEX_BPM_MIN + JUGGLE_PIXEL_INDEX_BPM_ADD;
            _maxBPM = SINELON_PIXEL_INDEX_BPM_MAX + JUGGLE_PIXEL_INDEX_BPM_ADD;            
            break;
        }
        case A_FIRE:
        {
            _updateInterval = FIRE_UPDATE_INTERVAL;
            _colorPalette = FIRE_PALETTES[ stg.firePaletteIndex ];

            if(_stripType == SOURCE || _stripType == SOLO){
                for( uint16_t i = 0; i < _stripLength; i++) {
                    f_Heat[i] = 0;
                }
            }

            break;
        }
        case A_CYCLE_ALL:
        {
            initializeAnimation(cycle_activeAnimation);
            _timeToCycleAnimations = ms_uint32 + CYCLE_ANIMATION_CHANGE_INTERVAL;
            return;
            break;
        }
        case A_SOLID_COLOR:
        {
            sc_Hue = SOLID_COLORS[ stg.solidColorIndex ];
            break;
        }
        case A_COLORWAVES:
        {   
            // this is the palette we will actually be modifying so we null it out
            // which causes a nice "materializing" effect to start out
            #if defined(__VR_HEADSET__)
                cw_Palette = CW_PALETTES[ cw_PaletteIndex ];
            #else
                cw_Palette = CRGBPalette16( CRGB::Black );
            #endif

            // this is the palette we will use as a target palette
            _colorPalette = CW_PALETTES[ cw_PaletteIndex ];

            // reset the time to swap palettes
            // things get weird with this because the millis is cast to a uint16_t
            cw_timeToChangePalette = ms_uint32 + CW_PALETTE_CHANGE_INTERVAL;
            cw_timeToBlendPalettes = ms_uint32 + 40;

            cwp_sPseudotime = 0;
            cwp_sLastMillis = 0;
            cwp_sHue16 = 0;

            break;
        }
        case A_PRIDE:
        case A_PRIDE_GLITTER:
        {   
            cwp_sPseudotime = 0;
            cwp_sLastMillis = 0;
            cwp_sHue16 = 0;

            break;
        }
        case A_DEVIN_ANIMATION:
        {

            cw_Palette = CRGBPalette16( CRGB::Black );
            _colorPalette = CW_PALETTES[ d_PaletteIndex ];
            cw_timeToChangePalette = ms_uint32 + DEVIN_PALETTE_CHANGE_INTERVAL;
            cw_timeToBlendPalettes = ms_uint32 + 40;

        }        
        case A_BPM:
        {
            _minBPM = NORMAL_HUE_INDEX_BPM;
            _maxBPM = NORMAL_HUE_INDEX_BPM * NUM_SPEED_LEVELS;
            break;
        }
        case A_VR_ANIMATION_01:
        {
            _minBPM = VR_HUE_INDEX_BPM;
            // _maxBPM = VR_HUE_INDEX_BPM * NUM_SPEED_LEVELS;
            _maxBPM = VR_HUE_INDEX_BPM;
            break;
        }
        case A_VR_ANIMATION_02:
        case A_VR_ANIMATION_03:
        {

            // cw_Palette = CRGBPalette16( CRGB::Black );
            cw_Palette = CW_PALETTES[ d_PaletteIndex ];
            _colorPalette = CW_PALETTES[ d_PaletteIndex ];
            cw_timeToChangePalette = ms_uint32 + DEVIN_PALETTE_CHANGE_INTERVAL;
            cw_timeToBlendPalettes = ms_uint32 + 40;

            _minBPM = VR_HUE_INDEX_BPM;
            _maxBPM = VR_HUE_INDEX_BPM * NUM_SPEED_LEVELS;
            // _maxBPM = VR_HUE_INDEX_BPM;
            break;
        }        
        default:
        {
            break;
        }
    }

    // update our _bpm variable based on all of our bpm related variables
    updateBPM();

}


// update our _bpm variable based on all of our bpm related variables
void LEDStripController::updateBPM(){

    // the Arduino map() function uses integer math
    _bpm = map(stg.speedLevel, 0, NUM_SPEED_LEVELS - 1, _minBPM, _maxBPM);

}




// the glitter function, randomly selects a pixel and sets it to white (aka glitter)
void LEDStripController::addGlitter( fract8 chanceOfGlitter, uint8_t gBrightness, uint8_t extraBrightness) {
    if( random8() < chanceOfGlitter) {
        // add white pops that are +extraBrightness greater than the gBrightness level
        _leds[ random16(_stripLength) ] += CHSV( 0, 0, qadd8(gBrightness, extraBrightness ));
    }
}


// get the next hue based on the bpm and if the strip is inverted or not
uint8_t LEDStripController::getHueIndex(uint8_t hueIndexBPM, uint8_t reverseDirecton){

    // XOR logic
    if(reverseDirecton != _invertStrip){
        return beat8(hueIndexBPM);  // leds appear to be moving reverse
    }
    else {
        return 255 - beat8(hueIndexBPM);  // leds appear to be moving forward
    }    
}





// **********************************************************
//      OTHER HELPER METHODS
// **********************************************************
void LEDStripController::loadAllSettingsFromEEPROM(Settings *settings){

    // get the address for our settings object which is our base address plus the size of our numWrites variable
    uint16_t settingsAddress = EEPROM_STORAGE_START_ADDR + sizeof(uint16_t);

    // get the data stored at the address for our settings variable
    EEPROM.get(settingsAddress, *settings);

    // make sure the data isn't out of range for any of our variables
    if(settings->animationIndex < 0 || settings->animationIndex >= ARRAY_SIZE(animationsToUse)){
        settings->animationIndex = 0;
    }
    if(settings->brightnessLevel < 0 || settings->brightnessLevel >= NUM_BRIGHTNESS_LEVELS){
        settings->brightnessLevel = 0;
    }
    if(settings->paletteIndex < 0 || settings->paletteIndex >= ARRAY_SIZE(COLOR_PALETTES)){
        settings->paletteIndex = 0;
    }
    if(settings->solidColorIndex < 0 || settings->solidColorIndex >= ARRAY_SIZE(SOLID_COLORS)){
        settings->solidColorIndex = 0;
    }
    if(settings->speedLevel < 0 || settings->speedLevel >= NUM_SPEED_LEVELS){
        settings->speedLevel = 0;
    }
    if(settings->firePaletteIndex < 0 || settings->firePaletteIndex >= ARRAY_SIZE(FIRE_PALETTES)){
        settings->firePaletteIndex = 0;


    }

}



void LEDStripController::saveSettingToEEPROM(String settingToSave){

    uint16_t address = EEPROM_STORAGE_START_ADDR;

    // update the number of writes
    uint16_t numWrites;
    EEPROM.get(address, numWrites);
    numWrites++;
    EEPROM.put(address, numWrites);

    // increment the address to the next available location after numWrites
    address = address + sizeof(numWrites);

    // save our actual setting
    if(settingToSave == "animationIndex"){
        // set the address using the builtin offsetof() function
        address = address + offsetof(Settings, animationIndex);

        // write the variable to EEPROM
        EEPROM.put(address, stg.animationIndex);
    }
    else if(settingToSave == "brightnessLevel"){
        // set the address using the builtin offsetof() function
        address = address + offsetof(Settings, brightnessLevel);

        // write the variable to EEPROM
        EEPROM.put(address, stg.brightnessLevel);
    }
    else if(settingToSave == "paletteIndex"){
        // set the address using the builtin offsetof() function
        address = address + offsetof(Settings, paletteIndex);

        // write the variable to EEPROM
        EEPROM.put(address, stg.paletteIndex);
    }
    else if(settingToSave == "solidColorIndex"){
        // set the address using the builtin offsetof() function
        address = address + offsetof(Settings, solidColorIndex);

        // write the variable to EEPROM
        EEPROM.put(address, stg.solidColorIndex);
    }
    else if(settingToSave == "speedLevel"){
        // set the address using the builtin offsetof() function
        address = address + offsetof(Settings, speedLevel);

        // write the variable to EEPROM
        EEPROM.put(address, stg.speedLevel);
    }
    else if(settingToSave == "firePaletteIndex"){
        // set the address using the builtin offsetof() function
        address = address + offsetof(Settings, firePaletteIndex);

        // write the variable to EEPROM
        EEPROM.put(address, stg.firePaletteIndex);
    }


}
