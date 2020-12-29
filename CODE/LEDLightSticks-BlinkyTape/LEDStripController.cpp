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

// **********************************************************
//      STATIC MEMBER DEFINITIONS
// **********************************************************
//******* ORDER OF ANIMATIONS ********
// this is how we set the order in which animations actually appear
const Animations LEDStripController::animationsToUse[] = {
                                                            A_RAINBOW,
                                                            A_RAINBOW_GLITTER,
                                                            A_CONFETTI,
                                                            A_SINELON,
                                                            A_SINELON_DUAL,
                                                            A_JUGGLE,
                                                            A_PALETTE,
                                                            A_PALETTE_GLITTER,
                                                            A_BPM, 
                                                            A_FIRE,
                                                            A_CYCLE_ALL,
                                                            A_SOLID_COLOR,
                                                            A_COLORWAVES
                                                        };

//******* ORDER OF COLOR PALETTES ********
const CRGBPalette16 LEDStripController::COLOR_PALETTES[] = {
                                                                //RainbowColors_p, // YES
                                                                tk_Party,
                                                                ForestColors_p,  // OK+ green
                                                                //CloudColors_p,   // not as good
                                                                //LavaColors_p,   // YES
                                                                //OceanColors_p,  // NO
                                                                PartyColors_p, // YES!!
                                                                //HeatColors_p, // fire yess
                                                                //lava_gp,
                                                                tk_Fire,
                                                                //tk_Fire_Blue
                                                                //RainbowStripeColors_p, // NOPE
                                                            };



// ORIGINAL FAVORITES
// const TProgmemRGBGradientPalettePtr LEDStripController::FAVORITE_PALETTES[] = {
//     Rainbow_gp,                 // classic FastLED
//     rainbowsherbet_gp,          // YES!    // Unicorn colors (aka yummy)
//     ib_jul01_gp,                // YES!!   // dragon colors - green and red fire orange
//     Coral_reef_gp,              // WHOA    // cool blue to warm blue
//     Sunset_Real_gp,             // NOICE   // purple, pink, and orange
//     Analogous_1_gp,             // NOICE   // retro wave - purple and pink
// }

// *************** PINK PURPLE ***************************
// FIRST ROUND -- KEEP
// const TProgmemRGBGradientPalettePtr LEDStripController::GRADIENT_PALETTES[] = {
//     BlacK_Red_Magenta_Yellow_gp, // OK+    // Tropical - fruity - yellow, red, purple
//     Sunset_Real_gp,             // NOICE    // purple, pink, and orange
//     Analogous_1_gp,             // NOICE    // retro wave - purple and pink
//     rgi_15_gp,                  // OK+dark  // magenta, and lavender with dark bands
//     es_pinksplash_07_gp,        // NOICE+bright      // magenta, lavender, and almost white
// };


// const TProgmemRGBGradientPalettePtr LEDStripController::GRADIENT_PALETTES[] = {
//     bhw1_28_gp,                 // OK blue - basic       // light blue, light purple
//     gr65_hult_gp,               // OK+blue - less basic      // bright blue, light purple, white
//     Pink_Purple_gp,              // OK sofgurPurp   // soothing purple, blue, white
//     ib15_gp,                    // OK+sofgirPink    // soft gurl Desaturated pink and blue    
// };


// PINK PURPLE -- DON'T KEEP
// const TProgmemRGBGradientPalettePtr LEDStripController::GRADIENT_PALETTES[] = {
    //Magenta_Evening_gp,         // OK+plain      // magenta and purple (no white)
    //es_pinksplash_08_gp,        // OK different      // pink, purple, white (dreamsicle) similar to below
    //Fuschia_7_gp,               // OK+balanced (boring?)      // bright purple blue pink
    //BlacK_Magenta_Red_gp,       // OK+      // magenta purple and black
// }
// *************** PINK PURPLE ***************************


// *************** BLUE ***************************
// none of these are great
// const CRGBPalette16 LEDStripController::GRADIENT_PALETTES[] = {    
//     es_ocean_breeze_036_gp,     // OK       // Sky blue, and white
//     OceanColors_p,
//     CloudColors_p
// };
// *************** BLUE ***************************






// *************** GREEN ***************************

//const TProgmemRGBGradientPalettePtr LEDStripController::GRADIENT_PALETTES[] = {
//    Colorfull_gp,               // OK    // desaturated green, purple blue white
//    es_landscape_64_gp,         // MEH    // green, blue, white
//     es_emerald_dragon_08_gp,    // OK    // Alien lime green
//     es_rivendell_15_gp,         // MEH      // grey green, and white
//}

// *************** GREEN ***************************






// const TProgmemRGBGradientPalettePtr LEDStripController::GRADIENT_PALETTES[] = {
const CRGBPalette16 LEDStripController::GRADIENT_PALETTES[] = {    
    tk_Party,
    // lava_gp,
    //ForestColors_p,
    // HeatColors_p,
    PartyColors_p,
    tk_Fire_Blue
};




// *************** ALL OPTIONS ***************************
// const TProgmemRGBGradientPalettePtr LEDStripController::GRADIENT_PALETTES[] = {
//     rainbowsherbet_gp,          // YES!    // Unicorn colors (aka yummy)
//     ib_jul01_gp,                // YES!!   // dragon colors - green and red fire orange
//     Coral_reef_gp,              // WHOA    // cool blue to warm blue
//     Sunset_Real_gp,             // NOICE   // purple, pink, and orange
//     Analogous_1_gp,             // NOICE   // retro wave - purple and pink
//     BlacK_Red_Magenta_Yellow_gp,// OK+    // Tropical - fruity - yellow, red, purple
//     Blue_Cyan_Yellow_gp         // OK+    // Tropical - carribean - beach
//     es_autumn_19_gp,            // OK+    // interesting redish orange yellow - fall colors
//     rgi_15_gp,                  // OK+      // magenta, and lavender
//     es_pinksplash_07_gp,        // OK+    // magenta, lavender, and almost white
//     gr65_hult_gp,               // OK+    // bright blue, light purple, white
//     ib15_gp,                    // OK+    // soft gurl Desaturated pink and blue
//     Fuschia_7_gp,               // OK+    // bright purple blue pink
//     BlacK_Magenta_Red_gp,       // OK+    // magenta purple and black
//     bhw1_28_gp,                 // OK       // light blue, light purple
//     es_ocean_breeze_036_gp,     // OK       // Sky blue, and white
//     es_emerald_dragon_08_gp,    // OK    // Alien lime green
//     lava_gp,                    // OK    // (test to see if it's the same as our other one)
//     Colorfull_gp,               // OK    // desaturated green, purple blue white
//     Pink_Purple_gp,             // OK    // soothing purple, blue, white
//     BlacK_Blue_Magenta_White_gp,// OK    // like a desaturated american flag - not pleasing to cache
//     Magenta_Evening_gp,         // OK+    // magenta and purple (no white)
//     es_pinksplash_08_gp,        // OK      // pink, purple, white (dreamsicle) similar to below
//     es_landscape_33_gp,         // OK    // blue and gold (I think piss)
//     fire_gp,                    // OK-ish    // Candy corn colors
//     gr64_hult_gp,               // MEH    // similar to above
//     es_rivendell_15_gp,         // MEH      // grey green, and white
//     es_landscape_64_gp,         // MEH    // green, blue, white
//     // departure_gp,               // EW    // green with white and weird color
//     //GMT_drywet_gp,              // MEH    // blue, yellowish
//     // es_vintage_57_gp,           // NOPE    // Unhealthy piss (bloody piss)
//     //es_ocean_breeze_068_gp,     // OK       // same as above but with white
//     //retro2_16_gp,               // NOPE     // piss colors
//     //es_vintage_01_gp,           // EWEWEW  // piss colors (chaplin)
// };
// *************** ALL OPTIONS ***************************









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
    _timeToCycleAnimations = 0;

    // **********************************************************
    //      PIXEL STATE VARIABLES
    // **********************************************************
    _hue = 0;
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
    _forward = true;
    _heat = new byte[stripLength];
    _activeCycleAnimation = animationsToUse[0];

    // a failsafe in case someone puts the A_CYCLE_ALL animation in position 0
    if(_activeCycleAnimation == A_CYCLE_ALL){
        _activeCycleAnimation = animationsToUse[1];
    }

    // LOAD THE AnimationFunction ARRAY WITH THE ENTIRE SET OF AVAILABLE Animations
    // !!!!! NOTE !!!!!
    // THIS ARRAY IS NOT IN ANY SPECIFIC ORDER. 
    // THE ORDER THE ANIMATIONS WILL APPEAR IS DEFINED BY THE "animationsToUse[]"" ARRAY
    // which is a globally defined variable
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


    // LOAD OUR SETTINGS SAVED IN EEPROM
    Settings settings;
    loadSettingsFromEEPROM(&settings);

    // THIS IS ANOTHER WAY TO DO THE ABOVE
    // requires a function that returns a Settings struct
    // Settings settings{ loadSettingsFromEEPROM() };

    // IMPORTANT: don't change these lines!!!
    // this is where we use the settings to initialize our program 
    _activeAnimation = animationsToUse[ settings.animationIndex ];    
    _brightnessLevel = settings.brightnessLevel;
    _brightness = map(_brightnessLevel, 0, NUM_BRIGHTNESS_LEVELS - 1, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    _colorPalette = COLOR_PALETTES[ settings.paletteIndex ];
    _solidColor = SOLID_COLORS[ settings.solidColorIndex ];
    _speedLevel = settings.speedLevel;    

    _gradientPaletteIndex = 0;
    _gradientPalette = GRADIENT_PALETTES[ _gradientPaletteIndex ];

    // this function initializes all the animation specific parameters
    // _bpm
    // _minBPM
    // _maxBPM 
    initializeAnimation(_activeAnimation);

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
                setStripCHSV(  CHSV( 180, FULL_SAT, _brightness)  );
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
// the technique used here means we don't need to save an _animationIndex variable
// and the reason we don't want to do that is....because I just didn't want one more freaking variable!!
void LEDStripController::nextAnimation(){

    // cycle through the array of animationsToUse.
    // figure out which index matches our current _activeAnimation
    // increment the index and modulo with the size of the array
    // use that incremented index as the new index into our animationsToUse array
    // set that as our new _activeAnimation
    for(uint8_t i = 0; i < ARRAY_SIZE(animationsToUse); i++){
        
        if(animationsToUse[i] == _activeAnimation){
            _activeAnimation = animationsToUse[ (i + 1) % ARRAY_SIZE(animationsToUse) ];

            saveSettingsToEEPROM((i + 1) % ARRAY_SIZE(animationsToUse), EEPROM_ADDR_ANIMATION_INDEX);
            break; 
        }
    }
    
    initializeAnimation(_activeAnimation);

    return;

}

// the technique used here means we don't need to save a _paletteIndex variable
// and the reason we don't want to do that is....because I just didn't want one more freaking variable!!
void LEDStripController::nextPalette(){

    if(_activeAnimation == A_SOLID_COLOR){
        for(uint8_t i = 0; i < ARRAY_SIZE(SOLID_COLORS); i++){
            
            if(SOLID_COLORS[i] == _solidColor){
                _solidColor = SOLID_COLORS[(i + 1) % ARRAY_SIZE(SOLID_COLORS)];
                saveSettingsToEEPROM((i + 1) % ARRAY_SIZE(SOLID_COLORS), EEPROM_ADDR_SOLID_COLOR_INDEX);
                return;
            }
        }
    }
    else if(_activeAnimation == A_COLORWAVES){
        _gradientPaletteIndex = addmod8( _gradientPaletteIndex, 1, ARRAY_SIZE(GRADIENT_PALETTES));
        _gradientPalette = GRADIENT_PALETTES[ _gradientPaletteIndex ];
    }

    // cycle through the array of available palettes.
    // figure out which index matches our current palette
    // increment the index and modulo with the size of the array
    // use that incremented index as the new index into our pallettes array
    for(uint8_t i = 0; i < ARRAY_SIZE(COLOR_PALETTES); i++){
        
        if(COLOR_PALETTES[i] == _colorPalette){
            _colorPalette = COLOR_PALETTES[(i + 1) % ARRAY_SIZE(COLOR_PALETTES)];
            saveSettingsToEEPROM((i + 1) % ARRAY_SIZE(COLOR_PALETTES), EEPROM_ADDR_PALETTE_INDEX);
            return;
        }
    }

}



void LEDStripController::nextBrightness(){

    _brightnessLevel = (_brightnessLevel + 1) % NUM_BRIGHTNESS_LEVELS;    

    _brightness = map(_brightnessLevel, 0, NUM_BRIGHTNESS_LEVELS - 1, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

    saveSettingsToEEPROM(_brightnessLevel, EEPROM_ADDR_BRIGHTNESS_INDEX);

}


void LEDStripController::nextSpeed(){
    
    _speedLevel = (_speedLevel + 1) % NUM_SPEED_LEVELS;

    updateBPM();

    saveSettingsToEEPROM(_speedLevel, EEPROM_ADDR_SPEED_INDEX);

}




void LEDStripController::setBrightness(uint8_t brightness){
    _brightness = brightness;
}




void LEDStripController::setOperationState(StripControllerStates newState){

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
            break;
        }
        case SHOW_SPEED_LEVEL:
        {
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
    static uint8_t blinkBPM = 60;
    uint8_t sin60bpm = beatsin8(blinkBPM, 0, 255, _bsTimebase, 256 / 2 - 1);
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

    fill_palette( _leds, _stripLength, getHueIndex(_bpm, _invertStrip), (256 / _stripLength) + 1, RainbowColors_p, _brightness, LINEARBLEND);
}


void LEDStripController::palette(){

    fill_palette( _leds, _stripLength, getHueIndex(_bpm, _invertStrip), 3, _colorPalette, _brightness, LINEARBLEND);
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
        CHSV newColor = rgb2hsv_approximate( ColorFromPalette( _colorPalette, getHueIndex() + random8(32), qadd8(_brightness, 40 )) );// MAGIC NUMBER ALERT!!!
        // drop the saturation
        newColor.saturation = 200; // MAGIC NUMBER ALERT!!!
        // add to the mix
        _leds[pos] += newColor;
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


void LEDStripController::juggle() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy( _leds, _stripLength, 20);

    byte dothue = 0;

    for( uint16_t i = 0; i < 8; i++) {

        CHSV newColor = rgb2hsv_approximate( ColorFromPalette( _colorPalette, dothue, qadd8(_brightness, 40 )) );// MAGIC NUMBER ALERT!!!
        newColor.saturation = 200;
        _leds[beatsin16( i+_bpm, 0, _stripLength - 1 )] |= newColor;
        
        //_leds[beatsin16( i+7, 0, _stripLength - 1 )] |= CHSV(dothue, 200, qadd8(_brightness, 40 ));
        
        dothue += 32;
    }
}


void LEDStripController::bpm(){
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    // uint8_t beatsPerMinute = 62;
    uint8_t beatsPerMinute = _bpm + 50;

    uint8_t beat = beatsin8( beatsPerMinute, 64, 255);
    // uint8_t hue = getHueIndex();
    uint8_t hue = getHueIndex(_bpm);
    

    for( uint16_t i = 0; i < _stripLength; i++) { //9948
        _leds[i] = ColorFromPalette( _colorPalette, hue+(i*2), scale8_video(beat-hue+(i*10), _brightness) );
    }
}



void LEDStripController::fire2012WithPalette() {
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
        _heat[i] = qsub8( _heat[i],  random8(0, ((COOLING * 10) / _stripLength) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( uint16_t k= _stripLength - 1; k >= 2; k--) {
        _heat[k] = (_heat[k - 1] + _heat[k - 2] + _heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
        uint16_t y = random8(7);
        _heat[y] = qadd8( _heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( uint16_t j = 0; j < _stripLength; j++) {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        byte colorindex = scale8( _heat[j], 240);
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


    (this->*(_animationFunctions[_activeCycleAnimation]))();


    // every 10 seconds we switch the animation
    if( millis() >= _timeToCycleAnimations ){

        for(uint8_t i = 0; i < ARRAY_SIZE(animationsToUse); i++){
            
            if(animationsToUse[i] == _activeCycleAnimation){
                _activeCycleAnimation = animationsToUse[(i + 1) % ARRAY_SIZE(animationsToUse)];   

                // if the next _activeCycleAnimation is the cycle animation this will break the program
                // so we want to skip it. We also want to skip solidColor because it's not doing anything
                // so that's why we have two if statements here. In case the two are right after eachother.
                if(_activeCycleAnimation == A_CYCLE_ALL || _activeCycleAnimation == A_SOLID_COLOR){
                    _activeCycleAnimation = animationsToUse[(i + 2) % ARRAY_SIZE(animationsToUse)];
                }
                if(_activeCycleAnimation == A_CYCLE_ALL || _activeCycleAnimation == A_SOLID_COLOR){
                    _activeCycleAnimation = animationsToUse[(i + 3) % ARRAY_SIZE(animationsToUse)];
                }
                break;
            }
        }    

        initializeAnimation(_activeCycleAnimation);

        _timeToCycleAnimations = millis() + ANIMATION_CYCLE_INTERVAL;
    }
}


void LEDStripController::solidColor() {

    if(_solidColor == 255){
        setStripCHSV(  CHSV( _solidColor, 0, scale8(_brightness, 210) ) );
    }
    else{
        setStripCHSV(  CHSV( _solidColor, FULL_SAT, _brightness)  );
    }

    // turn off the strip in a "mysterious" way
    //fadeToBlackBy( _leds, _stripLength, 10);
}


// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void LEDStripController::colorwavesFinal() {
// void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette) {

    static CRGBPalette16 gCurrentPalette( CRGB::Black);
    static CRGBPalette16 gTargetPalette( COLOR_PALETTES[0] );
    static uint8_t gCurrentPaletteNumber = 0;


    static uint16_t sPseudotime = 0;
    static uint16_t sLastMillis = 0;
    static uint16_t sHue16 = 0;

    uint8_t sat8 = beatsin88( 87, 220, 250);
    uint8_t brightdepth = beatsin88( 341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 300, 1500);

    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis ;
    sLastMillis  = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88( 400, 5,9);
    uint16_t brightnesstheta16 = sPseudotime;

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

        //CRGB newcolor = ColorFromPalette( _palette, index, bri8);
        CRGB newcolor = ColorFromPalette( gCurrentPalette, index, bri8);

        // uint16_t pixelnumber = i;
        // pixelnumber = (numleds-1) - pixelnumber;
        
        uint16_t pixelIndex;

        if( _invertStrip ) {
            pixelIndex = i;
        } else {
            pixelIndex = (_stripLength-1) - i;
        }

        nblend( _leds[pixelIndex], newcolor, 128);
    }


    
    // ***** ADDITIONAL TIMING - PALETTE UPDATES **********
    static uint32_t timeToSwitchPalettes = 0;
    if( ms >= timeToSwitchPalettes ){
        // EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
        //     gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
        //     gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
        // }
        
        gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, ARRAY_SIZE(COLOR_PALETTES));
        gTargetPalette = COLOR_PALETTES[ gCurrentPaletteNumber ];

        timeToSwitchPalettes = ms + 20000; // add 20 seconds in ms
    }

    static uint32_t timeToBlendPalettes = 0;
    if( ms >= timeToBlendPalettes ){
        // EVERY_N_MILLISECONDS(40) {
        //    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
        // }
        nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);

        timeToBlendPalettes = ms + 40; // add 40 ms
    }

}



// Alternate rendering function just scrolls the current palette 
// across the defined LED strip.
// void LEDStripController::palettetest(){
void LEDStripController::colorwaves(){
//   static uint8_t startindex = 0;
//   startindex--;

    fill_palette( _leds, _stripLength, getHueIndex(_bpm), pixelSpread, _gradientPalette, 255, LINEARBLEND);
    //fill_palette( _leds, _stripLength, getHueIndex(_bpm), (256 / _stripLength) + 1, _gradientPalette, 255, LINEARBLEND);
}






// **********************************************************
//      ANIMATION HELPER METHODS
// **********************************************************

// _bpm, _minBPM, _maxBPM are all initialized here
void LEDStripController::initializeAnimation(Animations animationToInitialize){

    _updateInterval = DEFAULT_UPDATE_INTERVAL;
    
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
            //_colorPalette = HeatColors_p;
            _updateInterval = FIRE_UPDATE_INTERVAL;

            for( uint16_t i = 0; i < _stripLength; i++) {
                _heat[i] = 0;
            }
        }
        case A_CYCLE_ALL:
        {
            _timeToCycleAnimations = millis() + ANIMATION_CYCLE_INTERVAL;
        }
        case A_BPM:        
        case A_SOLID_COLOR:
        case A_COLORWAVES:
        default:
        {
            _minBPM = NORMAL_HUE_INDEX_BPM;
            _maxBPM = NORMAL_HUE_INDEX_BPM * NUM_SPEED_LEVELS;
            break;
        }
    }

    // update our _bpm variable based on all of our bpm related variables
    updateBPM();

}


// update our _bpm variable based on all of our bpm related variables
void LEDStripController::updateBPM(){

    // the Arduino map() function uses integer math
    _bpm = map(_speedLevel, 0, NUM_SPEED_LEVELS - 1, _minBPM, _maxBPM);

    // doing it manually but using floating points
    // uint8_t _myBpm = _minBPM + (uint8_t)((_speedLevel / (float)(NUM_SPEED_LEVELS - 1)) * (_maxBPM - _minBPM));

}




// the glitter function, randomly selects a pixel and sets it to white (aka glitter)
void LEDStripController::addGlitter( fract8 chanceOfGlitter ) {
    if( random8() < chanceOfGlitter) {
        // add white pops that are +40 greater than the current brightness level
        _leds[ random16(_stripLength) ] += CHSV( 0, 0, qadd8(_brightness, 100 ));
        //_leds[ random16(_stripLength) ] += CRGB::White;
        //_leds[ random16(_stripLength) ] = CHSV( 0, 0, _brightness);
    }
}


// get the next hue based on the bpm and if the strip is inverted or not
uint8_t LEDStripController::getHueIndex(uint8_t hueIndexBPM, uint8_t direction){

    if(direction == NORMAL_HUE_INDEX_DIRECTION){
        return beat8(hueIndexBPM);
    }
    else {
        return 255 - beat8(hueIndexBPM);
    }    
}





// **********************************************************
//      OTHER HELPER METHODS
// **********************************************************
void LEDStripController::loadSettingsFromEEPROM(Settings *settings){

    settings->animationIndex  = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_ANIMATION_INDEX);
    settings->brightnessLevel = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_BRIGHTNESS_INDEX);
    settings->paletteIndex    = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_PALETTE_INDEX);
    settings->solidColorIndex = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_SOLID_COLOR_INDEX);
    settings->speedLevel      = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_SPEED_INDEX);


    if(settings->animationIndex < 0 || settings->animationIndex > ARRAY_SIZE(animationsToUse) - 1){
        settings->animationIndex = 0;
    }
    if(settings->brightnessLevel < 0 || settings->brightnessLevel > NUM_BRIGHTNESS_LEVELS - 1){
        settings->brightnessLevel = 0;
    }
    if(settings->paletteIndex < 0 || settings->paletteIndex > ARRAY_SIZE(COLOR_PALETTES) - 1){
        settings->paletteIndex = 0;
    }
    if(settings->solidColorIndex < 0 || settings->solidColorIndex > ARRAY_SIZE(SOLID_COLORS) - 1){
        settings->solidColorIndex = 0;
    }
    if(settings->speedLevel < 0 || settings->speedLevel > NUM_SPEED_LEVELS - 1){
        settings->speedLevel = 0;
    }

}

// // THIS IS ANOTHER WAY TO DO THE ABOVE
// LEDStripController::Settings LEDStripController::loadSettingsFromEEPROM(){

//     Settings settings;

//     settings.animationIndex  = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_ANIMATION_INDEX);
//     settings.brightnessLevel = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_BRIGHTNESS_INDEX);
//     settings.paletteIndex    = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_PALETTE_INDEX);
//     settings.solidColorIndex = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_SOLID_COLOR_INDEX);
//     settings.speedLevel      = EEPROM.read(EEPROM_ADDR_BASE + sizeof(uint16_t) + EEPROM_ADDR_SPEED_INDEX);


//     if(settings.animationIndex < 0 || settings.animationIndex > ARRAY_SIZE(animationsToUse) - 1){
//         settings.animationIndex = 0;
//     }
//     if(settings.brightnessLevel < 0 || settings.brightnessLevel > NUM_BRIGHTNESS_LEVELS - 1){
//         settings.brightnessLevel = 0;
//     }
//     if(settings.paletteIndex < 0 || settings.paletteIndex > ARRAY_SIZE(COLOR_PALETTES) - 1){
//         settings.paletteIndex = 0;
//     }
//     if(settings.solidColorIndex < 0 || settings.solidColorIndex > ARRAY_SIZE(SOLID_COLORS) - 1){
//         settings.solidColorIndex = 0;
//     }
//     if(settings.speedLevel < 0 || settings.speedLevel > NUM_SPEED_LEVELS - 1){
//         settings.speedLevel = 0;
//     }

//     return settings;
// }



void LEDStripController::saveSettingsToEEPROM(uint8_t value, uint8_t addrIndex){

    uint16_t numWrites = EEPROM.read(EEPROM_ADDR_BASE);
    
    EEPROM.write(EEPROM_ADDR_BASE, numWrites + 1 );

    EEPROM.write(EEPROM_ADDR_BASE + sizeof(uint16_t) + addrIndex, value);
}
