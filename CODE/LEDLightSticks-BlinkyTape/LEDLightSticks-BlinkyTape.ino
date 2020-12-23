/*  LED Light Sticks Code
      -- This is a program that uses FastLED and JC_Button to make the light sticks light up and change animations and colors
*/

/////// INCLUDES ///////
#include "LEDLightSticks.h"
#include "LEDStripController.h"



// *********************************************************************************
//      TEST VARIABLES DELETE THESE LATER
// *********************************************************************************
//uint8_t hue = 0;
//unsigned long lastUpdateTime = 0; // time of last update of position


//bool glitter = false;
//unsigned long lastBlinkTime = 0; // time of last call to FastLED.show()



// *********************************************************************************
//      GLOBAL MUTABLE VARIABLES
// *********************************************************************************
unsigned long lastFastLEDShowTime = 0; // time of last call to FastLED.show()



// *********************************************************************************
//      BUTTON DECLARATIONS
// *********************************************************************************
Button animationButton(ANIMATION_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button paletteButton(PALETTE_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

ProgramState currentState = ANIMATION_IS_RUNNING;

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
LEDStripController leds_01_Controller(&(leds_01[0]), LEDS_01_NUM_LEDS, colorPalette, INVERT_STRIP, 0);




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

  // READ THE BUTTONS TO SEE IF ANY OPERATOR INPUT HAS OCCURED
  readButtons();

  // UPDATE THE VISUAL REPRESENTATION OF OUR STRIPS IN EACH STRIP CONTROLLER OBJECT
  leds_01_Controller.update();
  

  // PUSH OUT LATEST FRAME TO THE ACTUAL PHYSICAL LEDS
  // this physically displays the current state of leds in each strip controller object
  // we wrap it in a timer so that it only triggers at a modest frame rate
  if( (millis() - lastFastLEDShowTime) > (1000/FRAMES_PER_SECOND) ){
     FastLED.show();
     lastFastLEDShowTime = millis();
  }


}




// *********************************************************************************
//   READ BUTTONS FUNCTION
//      This function is where we read our buttons
//      and manage the state of our program based on button input
// *********************************************************************************
void readButtons(){

  //READ THE BUTTONS
  animationButton.read();
  paletteButton.read();

  //STORE THE BUTTON'S UPDATED STATES IN LOCAL VARIABLES
  uint8_t animationButtPressed = animationButton.wasReleased();
  uint8_t animationButtHeld = animationButton.pressedFor(LONG_PRESS);

  #if defined(__BLINKY_TAPE__)
    animationButton_blinkyTape.read();
    animationButtPressed = ( animationButtPressed || animationButton_blinkyTape.wasReleased() );
    animationButtHeld = ( animationButtHeld || animationButton_blinkyTape.pressedFor(LONG_PRESS) );
  #endif

  uint8_t paletteButtPressed = paletteButton.wasReleased();
  uint8_t paletteButtHeld = paletteButton.pressedFor(LONG_PRESS);


  // TAKE ACTIONS BASED ON THE CURRENT STATE OF OUR PROGRAM AND THE UPDATED STATE OF THE BUTTONS
  switch (currentState) {

    // Executes while the animation is running...
    case ANIMATION_IS_RUNNING:
      // if the animation change button is pressed, change the animation
      if (animationButtPressed){
        leds_01_Controller.nextPattern();
        //glitter = !glitter;        
      }
      // if the animation change button is held down
      // put the strip in its transition state
      else if (animationButtHeld){
        leds_01_Controller.setState(TRANSITION_STATE);
        currentState = TRANSITION_TO_CHANGE_BRIGHTNESS;
      }

      break;

    //This is a transition state where we need to wait for the operator to release the button, 
    // i.e. release the button from a long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TRANSITION_TO_CHANGE_BRIGHTNESS:      
      // if the animation change button is pressed, move to the CHANGE_BRIGHTNESS state
      if (animationButtPressed){
        leds_01_Controller.setState(SHOW_BRIGHTNESS_LEVEL);        
        currentState = CHANGE_BRIGHTNESS;
      }
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TRANSITION_TO_ANIMATION_IS_RUNNING" which is the fast-blink state.
    case CHANGE_BRIGHTNESS:

      if (animationButtPressed){
        nextBrightness();
      }
      else if (animationButtHeld){
        leds_01_Controller.setState(TRANSITION_STATE);
        currentState = TRANSITION_TO_ANIMATION_IS_RUNNING;
      }

      break;

    //This is a transition state where we just wait for the operator to release the button
    //before moving back to the ANIMATION_IS_RUNNING state.
    case TRANSITION_TO_ANIMATION_IS_RUNNING:
      if (animationButtPressed){
        leds_01_Controller.setState(RUN_ANIMATION);
        currentState = ANIMATION_IS_RUNNING;
      }
      break;
  }


  //Read the button associated with bike side strip and palette change (with long press)
  // paletteButton.read();
  
  // if (paletteButtPressed){
  //   leds_01_Controller.nextPalette();
  // }

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
