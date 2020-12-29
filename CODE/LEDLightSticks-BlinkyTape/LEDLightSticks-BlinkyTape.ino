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
enum ProgramStates {
        ANIMATION_IS_RUNNING, 
        TRANSITION_TO_CHANGE_BRIGHTNESS, 
        CHANGE_BRIGHTNESS,
        CHANGE_SPEED,
        TRANSITION_TO_ANIMATION_IS_RUNNING
    };


const StripControllerStates mapProgramToStripControllerStates[5] =  {
                                                                      NORMAL_OPERATION,
                                                                      STATE_TRANSITION,
                                                                      SHOW_BRIGHTNESS_LEVEL,
                                                                      SHOW_SPEED_LEVEL,
                                                                      STATE_TRANSITION
                                                                    };



// *********************************************************************************
//      BUTTON DECLARATIONS
// *********************************************************************************
Button primaryButton(PRIMARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button secondaryButton(SECONDARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

#if defined(__BLINKY_TAPE__)
  Button primaryButton_blinkyTape(PRIMARY_BUTTON_PIN_BLINKYTAPE, PULLUP, INVERT, DEBOUNCE_MS);
#endif

ProgramStates programState = ANIMATION_IS_RUNNING;

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
// CRGB leds_02[LEDS_02_NUM_LEDS];

// Controller for each led strip (to manage each led array's state without blocking main thread)
LEDStripController stripController_01sA(leds_01, LEDS_01_NUM_LEDS, DEFAULT_PALETTE, INVERT_STRIP, 0);
//LEDStripController stripController_01sB(leds_02, LEDS_02_NUM_LEDS, DEFAULT_PALETTE, INVERT_STRIP, 0);

// LEDStripController stripController_01sA(aLEDs, floor(ALEN * 1.0/3.0));
// LEDStripController stripController_01sB(aLEDs, ceil(ALEN * 1.0/3.0), DEFAULT_PALETTE, !INVERT_STRIP, floor(ALEN * 1.0/3.0));
// LEDStripController stripController_01sC(aLEDs, ceil(ALEN * 1.0/3.0), DEFAULT_PALETTE, INVERT_STRIP, floor(ALEN * 2.0/3.0));
//LEDStripController stripController_01s2(leds_01, LEDS_01_NUM_LEDS-15, colorPalette, !INVERT_STRIP, 15);

// Array of pointers to our LEDStripController objects.
// Makes updating them all at once more efficient
LEDStripController *stripControllerArray[] = {  
                                                &stripController_01sA//,
                                                //&stripController_01sB
                                              };

const uint8_t NUM_STRIP_CONTROLLERS = ARRAY_SIZE(stripControllerArray);


// *********************************************************************************
//      SETUP FUNCTION
// *********************************************************************************
void setup() {

  // Serial.begin(9600);

  // Serial.print("Num Strip Controllers: ");
  // Serial.println(NUM_STRIP_CONTROLLERS);
  // Serial.println("***********************");

  // Serial.print("Num Color Palettes: ");
  // Serial.println(ARRAY_SIZE(COLOR_PALETTES));
  // Serial.println("***********************");

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
  primaryButton.read();
  secondaryButton.read();

  //STORE THE BUTTON'S UPDATED STATES IN LOCAL VARIABLES
  uint8_t primaryButtPressed = primaryButton.wasReleased();
  uint8_t primaryButtHeld = primaryButton.pressedFor(LONG_PRESS);

  #if defined(__BLINKY_TAPE__)
    primaryButton_blinkyTape.read();
    primaryButtPressed = ( primaryButtPressed || primaryButton_blinkyTape.wasReleased() );
    primaryButtHeld = ( primaryButtHeld || primaryButton_blinkyTape.pressedFor(LONG_PRESS) );
  #endif

  uint8_t secondaryButtPressed = secondaryButton.wasReleased();
  uint8_t secondaryButtHeld = secondaryButton.pressedFor(LONG_PRESS);


  // TAKE ACTIONS BASED ON THE CURRENT STATE OF OUR PROGRAM AND THE UPDATED STATE OF THE BUTTONS
  switch (programState) {

    // Executes while the animation is running...
    case ANIMATION_IS_RUNNING:
      
      if (primaryButtPressed){
        nextStripControllerAnimation();    
      }
      else if (secondaryButtPressed){
        nextStripControllerPalette();
      }      
      else if (primaryButtHeld){
        updateProgramState(TRANSITION_TO_CHANGE_BRIGHTNESS);
      }

      break;

    // This is a transition state where we need to wait for the operator to release the button, 
    // i.e. release the button from a long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TRANSITION_TO_CHANGE_BRIGHTNESS:      
      // if the primary button is released (which appears as a press), move to the CHANGE_BRIGHTNESS state
      if (primaryButtPressed){
        updateProgramState(CHANGE_BRIGHTNESS);
      }
      break;

    //Watch for button presses or another long press
    case CHANGE_SPEED:
    case CHANGE_BRIGHTNESS:

      if (primaryButtPressed){
        (programState == CHANGE_BRIGHTNESS) ? nextStripControllerBrightness() : updateProgramState(CHANGE_BRIGHTNESS);
      }
      else if (secondaryButtPressed){
        (programState == CHANGE_BRIGHTNESS) ? updateProgramState(CHANGE_SPEED) : nextStripControllerSpeed();
      }
      else if (primaryButtHeld){
        updateProgramState(TRANSITION_TO_ANIMATION_IS_RUNNING);
      }

      break;

    //This is a transition state where we just wait for the operator to release the button
    //before moving back to the ANIMATION_IS_RUNNING state.
    case TRANSITION_TO_ANIMATION_IS_RUNNING:
      if (primaryButtPressed){
        updateProgramState(ANIMATION_IS_RUNNING);
      }
      break;
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
void updateProgramState(ProgramStates newState){
  programState = newState;
  setStripControllerStates(newState);
}



// *********************************************************************************
//      BUTTON -> LED STRIP CONTROLLER HELPER FUNCTIONS
// *********************************************************************************
void setStripControllerStates(ProgramStates newState){

  // this is where we convert the newState (which is a ProgramStates type)
  // to the StripControllerStates type using our map we built at the top of the program
  StripControllerStates newStripControllerState = mapProgramToStripControllerStates[newState];

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
