/*  LED Light Sticks Code
      -- This is a program that uses FastLED and JC_Button to make the light sticks light up and change patterns and colors
*/

/////// INCLUDES ///////
#include "LEDLightSticks.h"
#include "LEDStripController.h"

// *********************************************************************************
//      GLOBAL MUTABLE VARIABLES
// *********************************************************************************
unsigned long lastFastLEDShowTime = 0; // time of last call to FastLED.show()



uint8_t hue = 0;
unsigned long lastUpdateTime = 0; // time of last update of position
uint16_t updateInterval = DEFAULT_UPDATE_INTERVAL;   // milliseconds between updates. Likely needs to be 5




// *********************************************************************************
//      BUTTON DECLARATIONS
// *********************************************************************************
Button animationButton(ANIMATION_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button paletteButton(PALETTE_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

uint8_t STATE = SHOW_PATTERN;

#if defined(__BLINKY_TAPE__)
  Button animationButton_blinkyTape(ANIMATION_BUTTON_PIN_BLINKYTAPE, PULLUP, INVERT, DEBOUNCE_MS);
#endif



// *********************************************************************************
//      LED STRIP CONTROLLER AND COLOR PALETTE DECLARATIONS
// *********************************************************************************
// mutable color palette initialization
CRGBPalette16 colorPalette(HeatColors_p);
//CRGBPalette16 colorPalette(LavaColors_p);
//CRGBPalette16 colorPalette(CloudColors_p);
//CRGBPalette16 colorPalette(PartyColors_p); //AKA Instagram colors

// ****** SETUP THE VIRTUAL REPRESENTATION OF OUR LED STRIPS ******
// CRGB Array for each strip.
CRGB leds_01[LEDS_01_NUM_LEDS];

// Controller for each led strip (to manage each led array's state without blocking main thread)
//LedStripController leds_01_Controller(&(leds_01[0]), colorPalette, 0, LEDS_01_NUM_LEDS, INVERT_STRIP);




// *********************************************************************************
//      SETUP
// *********************************************************************************
//setup runs once at startup:
void setup() {

  // THIS STEP SETS UP THE PHYSICAL REPRESENTATION OF OUR LED STRIPS
  FastLED.addLeds<LED_TYPE, LEDS_01_PIN>(leds_01, LEDS_01_NUM_LEDS).setCorrection(TypicalLEDStrip);;


  // set master brightness control from our global variable
  FastLED.setBrightness(INITIAL_BRIGHTNESS);

}




// *********************************************************************************
//      MAIN LOOP
// *********************************************************************************
void loop() {

  // Add entropy to random number generator; we use a lot of it for the FIRE ANIMATION
  random16_add_entropy( random());

  // READ THE BUTTONS TO SEE IF ANY USER INPUT HAS OCCURED
  readButtons();

  // UPDATE THE VISUAL REPRESENTATION OF OUR STRIPS IN EACH STRIP CONTROLLER OBJECT
  //leds_01_Controller.Update();
  

  // PUSH OUT LATEST FRAME TO THE ACTUAL PHYSICAL LEDS
  // this physically displays the current state of leds in each strip controller object
  // we wrap it in a timer so that it only triggers at a modest frame rate
  if( (millis() - lastFastLEDShowTime) > (1000/FRAMES_PER_SECOND) ){
     FastLED.show();
     lastFastLEDShowTime = millis();
  }


}




// *********************************************************************************
//      HELPER FUNCTIONS
// *********************************************************************************
void readButtons(){

  //Read the button associated with bike center strip and brightness change (with long press)
  animationButton.read();

  switch (STATE) {

    //This state watches for short and long presses, switches the pattern for
    //short presses, and moves to the TO_CHANGE_BRIGHTNESS state for long presses.
    case SHOW_PATTERN:
      if (animationButton.wasReleased()){
        //leds_01_Controller.nextPattern();
        fill_solid( leds_01, LEDS_01_NUM_LEDS, CHSV( random8(), 255, 255) ); 
      }
      else if (animationButton.pressedFor(LONG_PRESS)){
        //leds_01_Controller.setStripState(TO_CHANGE_BRIGHTNESS);
        STATE = TO_CHANGE_BRIGHTNESS;
      }
      break;
      
    //This is a transition state where we start the fast blink as feedback to the user,
    //but we also need to wait for the user to release the button, i.e. end the
    //long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TO_CHANGE_BRIGHTNESS:
      if (animationButton.wasReleased()){
        STATE = CHANGE_BRIGHTNESS;
        //leds_01_Controller.setStripState(CHANGE_BRIGHTNESS);
      }

      runAnimation(1);
      
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TO_SHOW_PATTERN" which is the fast-blink state.
    case CHANGE_BRIGHTNESS:
      if (animationButton.pressedFor(LONG_PRESS)){
        //leds_01_Controller.setStripState(TO_SHOW_PATTERN);
        STATE = TO_SHOW_PATTERN;
      }
      else if (animationButton.wasReleased()){
        nextBrightness();
      }
      
      runAnimation(2);

      break;

    //This is a transition state where we just wait for the user to release the button
    //before moving back to the SHOW_PATTERN state.
    case TO_SHOW_PATTERN:
      if (animationButton.wasReleased()){
        //leds_01_Controller.setStripState(SHOW_PATTERN);
        STATE = SHOW_PATTERN;
      }

      runAnimation(1);

      break;
  }  


  //Read the button associated with bike side strip and palette change (with long press)
  // paletteButton.read();
  
  // if (paletteButton.wasReleased()){
  //   leds_01_Controller.nextPalette();
  // }

}



void runAnimation(uint8_t animationType){


      if( (millis() - lastUpdateTime) > updateInterval ){
        // mimmick led strip animation with rainbow + glitter
        hue++;
        fill_rainbow( leds_01, LEDS_01_NUM_LEDS, hue, 7);

        if( random8() < 80 && animationType == 2) {
          leds_01[ random16(LEDS_01_NUM_LEDS) ] += CRGB::White;
        }

        lastUpdateTime = millis();
      }

}









void nextBrightness() {
  uint8_t currentBrightness = FastLED.getBrightness();
  currentBrightness += BRIGHTNESS_INCREMENT;

  if(currentBrightness < BRIGHTNESS_MAX_MODULO){
    currentBrightness = currentBrightness % BRIGHTNESS_MAX_MODULO;
  }
  else if(currentBrightness >= BRIGHTNESS_MAX_MODULO){
    currentBrightness = BRIGHTNESS_INCREMENT;
  }

  FastLED.setBrightness(currentBrightness);
}





