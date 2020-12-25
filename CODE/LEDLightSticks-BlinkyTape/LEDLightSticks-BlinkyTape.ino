/*  LED Light Sticks Code
      -- This is a program that uses FastLED and JC_Button to make the light sticks light up and change animations and colors
*/

// *********************************************************************************
//      INCLUDES
// *********************************************************************************
//#include <FastLED.h>
#include "HardwareDefinitions.h"
#include "LEDStripController.h"
#include "JC_Button_old.h"


// *********************************************************************************
//      GLOBAL MUTABLE VARIABLES
// *********************************************************************************
uint32_t timeToCallFastLEDShow = 0; // time of last call to FastLED.show()


// *********************************************************************************
//    GLOBAL ENUM FOR MANAGING PROGRAM STATE
// *********************************************************************************
//The possible states for the button state machine
enum ProgramState {
        ANIMATION_IS_RUNNING, 
        TRANSITION_TO_CHANGE_BRIGHTNESS, 
        CHANGE_BRIGHTNESS,
        CHANGE_SPEED,
        TRANSITION_TO_ANIMATION_IS_RUNNING
    };


const uint8_t mapToLEDStripControllerState[5] = {
                              NORMAL_OPERATION,
                              STATE_TRANSITION,
                              SHOW_BRIGHTNESS_LEVEL,
                              SHOW_SPEED_LEVEL,
                              STATE_TRANSITION
                          };



// *********************************************************************************
//      BUTTON DECLARATIONS
// *********************************************************************************
Button animationButton(ANIMATION_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button paletteButton(PALETTE_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

#if defined(__BLINKY_TAPE__)
  Button animationButton_blinkyTape(ANIMATION_BUTTON_PIN_BLINKYTAPE, PULLUP, INVERT, DEBOUNCE_MS);
#endif

ProgramState programState = ANIMATION_IS_RUNNING;

// *********************************************************************************
//      LED STRIP CONTROLLER AND COLOR PALETTE DECLARATIONS
//        This sets up the virtual representation of our LED Strips
//        Best Color Palette Options:
//            CRGBPalette16 colorPalette(LavaColors_p);
//            CRGBPalette16 colorPalette(CloudColors_p);
//            CRGBPalette16 colorPalette(PartyColors_p); //AKA Instagram colors
// *********************************************************************************
//CRGBPalette16 colorPalette(HeatColors_p);

// CRGB Array for each strip.
CRGB leds_01[LEDS_01_NUM_LEDS];
CRGB leds_02[LEDS_02_NUM_LEDS];

// Controller for each led strip (to manage each led array's state without blocking main thread)
LEDStripController stripController_01sA(leds_01, LEDS_01_NUM_LEDS, DEFAULT_PALETTE, INVERT_STRIP, 0);
LEDStripController stripController_01sB(leds_02, LEDS_02_NUM_LEDS, DEFAULT_PALETTE, INVERT_STRIP, 0);

// LEDStripController stripController_01sA(aLEDs, floor(ALEN * 1.0/3.0));
// LEDStripController stripController_01sB(aLEDs, ceil(ALEN * 1.0/3.0), DEFAULT_PALETTE, !INVERT_STRIP, floor(ALEN * 1.0/3.0));
// LEDStripController stripController_01sC(aLEDs, ceil(ALEN * 1.0/3.0), DEFAULT_PALETTE, INVERT_STRIP, floor(ALEN * 2.0/3.0));
//LEDStripController stripController_01s2(leds_01, LEDS_01_NUM_LEDS-15, colorPalette, !INVERT_STRIP, 15);

// Array of pointers to our LEDStripController objects.
// Makes updating them all at once more efficient
LEDStripController *stripControllerArray[] = {  
                                                &stripController_01sA,
                                                &stripController_01sB
                                              };

const uint8_t NUM_STRIP_CONTROLLERS = ARRAY_SIZE(stripControllerArray);


// *********************************************************************************
//      SETUP FUNCTION
// *********************************************************************************
void setup() {

  Serial.begin(9600);

  Serial.print("Num Strip Controllers: ");
  Serial.println(NUM_STRIP_CONTROLLERS);
  Serial.println("***********************");

  Serial.print("Num Color Palettes: ");
  Serial.println(NUM_COLOR_PALETTES);
  Serial.println("***********************");

  // THIS STEP SETS UP THE PHYSICAL REPRESENTATION OF OUR LED STRIPS
  FastLED.addLeds<LED_TYPE, LEDS_01_PIN>(leds_01, LEDS_01_NUM_LEDS);
  //FastLED.setCorrection(UncorrectedColor);
  //FastLED.setCorrection(TypicalPixelString);

  // set master brightness control from our global variable
  //FastLED.setBrightness(FAST_LED_MAX_BRIGHTNESS);
  // FastLED.setBrightness(INITIAL_BRIGHTNESS);

  delay(300);
}




// *********************************************************************************
//      MAIN LOOP FUNCTION
// *********************************************************************************
void loop() {

  static uint32_t ms;
  ms = millis();

  // Add entropy to random number generator; we use a lot of it for the FIRE ANIMATION
  random16_add_entropy( random());

  // READ THE BUTTONS TO SEE IF ANY OPERATOR INPUT HAS OCCURED
  readAndRespondToButtonInput(ms);

  // UPDATE THE VISUAL REPRESENTATION OF OUR STRIPS IN EACH STRIP CONTROLLER OBJECT 
  updateStripControllers(ms);

  // PUSH OUT LATEST FRAME TO THE ACTUAL PHYSICAL LEDS
  // this physically displays the current state of leds in each strip controller object
  // we wrap it in a timer so that it only triggers at a modest frame rate
  if( ms > timeToCallFastLEDShow ){
     FastLED.show();
     timeToCallFastLEDShow = ms + (1000/FRAMES_PER_SECOND);
  }


}



// *********************************************************************************
//   READ AND RESPOND TO BUTTON INPUT
//      This function is where we read our buttons
//      and manage/update the state of our program
//      and strip controllers based on button input
// *********************************************************************************
void readAndRespondToButtonInput(uint32_t ms){

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
  switch (programState) {

    // Executes while the animation is running...
    case ANIMATION_IS_RUNNING:
      // if the animation change button is pressed, change the animation
      if (animationButtPressed){
        nextStripControllerAnimation();    
      }
      // if the animation change button is held down
      // put the strip in its transition state
      else if (animationButtHeld){
        updateProgramState(TRANSITION_TO_CHANGE_BRIGHTNESS);
        //programState = TRANSITION_TO_CHANGE_BRIGHTNESS;
        //setStripControllerStates(programState);
      }

      break;

    //This is a transition state where we need to wait for the operator to release the button, 
    // i.e. release the button from a long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TRANSITION_TO_CHANGE_BRIGHTNESS:      
      // if the animation change button is pressed, move to the CHANGE_BRIGHTNESS state
      if (animationButtPressed){
        updateProgramState(CHANGE_BRIGHTNESS);
      }
      break;

    //Watch for another long press which will cause us to
    //put the strip into "TRANSITION_TO_ANIMATION_IS_RUNNING" which is the fast-blink state.
    case CHANGE_SPEED:
    case CHANGE_BRIGHTNESS:

      if (animationButtPressed){
        (programState == CHANGE_BRIGHTNESS) ? nextStripControllerBrightness() : nextStripControllerSpeed();
      }
      else if (paletteButtPressed){
        (programState == CHANGE_BRIGHTNESS) ? updateProgramState(CHANGE_SPEED) : updateProgramState(CHANGE_BRIGHTNESS);
      }      
      else if (animationButtHeld){
        updateProgramState(TRANSITION_TO_ANIMATION_IS_RUNNING);
      }

      break;

    //This is a transition state where we just wait for the operator to release the button
    //before moving back to the ANIMATION_IS_RUNNING state.
    case TRANSITION_TO_ANIMATION_IS_RUNNING:
      if (animationButtPressed){
        updateProgramState(ANIMATION_IS_RUNNING);
      }
      break;
  }


  //respond to the paletteButton state  
  if (paletteButtPressed){
    nextStripControllerPalette();
  }

}


// *********************************************************************************
//   UPDATE STRIP CONTROLLERS
//      This function is where we update each Strip Controller
//      So that it can update the state of the LEDs to be displayed
// *********************************************************************************
void updateStripControllers(uint32_t ms){
  for(uint8_t i = 0; i < NUM_STRIP_CONTROLLERS; i++){
    stripControllerArray[i]->update(ms);
  }
}





// *********************************************************************************
//      BUTTON HELPER FUNCTIONS
// *********************************************************************************
void updateProgramState(ProgramState newState){
  programState = newState;
  setStripControllerStates(newState);
}



// *********************************************************************************
//      BUTTON -> LED STRIP CONTROLLER HELPER FUNCTIONS
// *********************************************************************************
void setStripControllerStates(ProgramState newState){

  // uint8_t stripControllerState = mapToLEDStripControllerState[newState];
  LEDStripControllerState newStripControllerState = mapToLEDStripControllerState[newState];

  for(uint8_t i = 0; i < NUM_STRIP_CONTROLLERS; i++){
    stripControllerArray[i]->setOperationState(newStripControllerState);
  }
}


void nextStripControllerAnimation(){
  for(uint8_t i = 0; i < NUM_STRIP_CONTROLLERS; i++){
    stripControllerArray[i]->nextAnimation();
  }
}


void nextStripControllerPalette(){
  for(uint8_t i = 0; i < NUM_STRIP_CONTROLLERS; i++){
    stripControllerArray[i]->nextPalette();
  }
}


void nextStripControllerBrightness() {
  for(uint8_t i = 0; i < NUM_STRIP_CONTROLLERS; i++){
    stripControllerArray[i]->nextBrightness();
  }
}

void nextStripControllerSpeed() {
  for(uint8_t i = 0; i < NUM_STRIP_CONTROLLERS; i++){
    stripControllerArray[i]->nextSpeed();
  }
}
