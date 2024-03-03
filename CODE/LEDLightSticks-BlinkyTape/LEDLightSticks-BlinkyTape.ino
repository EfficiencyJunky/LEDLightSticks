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

// ******* Timekeeping variable for managing when we should call FastLED.show() *******
uint32_t timeToCallFastLEDShow = 0;


// ******* ENUM for managing Program State *******
//The possible states for the button state machine
enum ProgramStates {
        ANIMATION_IS_RUNNING, 
        TRANSITION_TO_CHANGE_BRIGHTNESS, 
        TRANSITION_TO_VIEW_PALETTES,
        CHANGE_BRIGHTNESS,
        CHANGE_SPEED,
        VIEW_PALETTES,
        TRANSITION_TO_ANIMATION_IS_RUNNING_PRIMARY,
        TRANSITION_TO_ANIMATION_IS_RUNNING_SECONDARY,
        TURN_STRIP_OFF_WAIT_FOR_INPUT,
        TOTAL_NUM_POSSIBLE_STRIP_CONTROLLER_STATES,
        BOTH_BUTTONS_PRESSED
    };


// ******* "Lookup Table" for mapping ProgramStates to LEDStripController States *******
const StripControllerStates mapProgramToStripControllerStates[TOTAL_NUM_POSSIBLE_STRIP_CONTROLLER_STATES] =  {
                                                                      NORMAL_OPERATION,
                                                                      STATE_TRANSITION,
                                                                      STATE_TRANSITION,
                                                                      SHOW_BRIGHTNESS_LEVEL,
                                                                      SHOW_SPEED_LEVEL,
                                                                      SHOW_PALETTE,
                                                                      STATE_TRANSITION,
                                                                      STATE_TRANSITION,
                                                                      STRIP_OFF
                                                                    };


// *********************************************************************************
//      BUTTON DECLARATIONS
// *********************************************************************************
#if defined(__BLINKY_TAPE_TWO_BUTTON__)
  Button primaryButton(EXT_PRIMARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
  Button secondaryButton(EXT_SECONDARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
  Button primaryButton_2(ONBOARD_PRIMARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

#elif defined(__BLINKY_TAPE_ONE_BUTTON__)
  Button primaryButton(EXT_PRIMARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
  Button secondaryButton(ONBOARD_SECONDARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

#elif defined(__TEENSY__)
  Button primaryButton(PRIMARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
  Button secondaryButton(SECONDARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);

#elif defined(__TRINKET_PRO_ONE_BUTTON__)
  Button primaryButton(PRIMARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
  Button secondaryButton(SECONDARY_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
#endif



// *********************************************************************************
//      LED DECLARATIONS -- CRGB ARRAYS AND STRIP CONTROLLERS
// *********************************************************************************

#if defined(__TRINKET_PRO_ONE_BUTTON__) || defined(__BLINKY_TAPE_ONE_BUTTON__)
  // CRGB Array for each strip.
  CRGB leds_01[LEDS_01_NUM_LEDS];
  // CRGB leds_02[LEDS_02_NUM_LEDS];

  // Controller for each led strip (to manage each led array's state without blocking main thread)
  LEDStripController stripController_01sA(leds_01, 0, LEDS_01_NUM_LEDS, !INVERT_STRIP, SOURCE);
  // LEDStripController stripController_01sB(leds_02, 0, LEDS_02_NUM_LEDS, !INVERT_STRIP, REPLICA);

  // Array of pointers to our LEDStripController objects.
  // Makes updating them all at once more efficient
  LEDStripController *stripControllerArray[] = {  
                                                  &stripController_01sA
                                                };
#else
  // CRGB Array for each strip.
  CRGB leds_01[LEDS_01_NUM_LEDS];
  CRGB leds_02[LEDS_02_NUM_LEDS];

  // Controller for each led strip (to manage each led array's state without blocking main thread)
  // NOTE: ALL ARGUMENTS ARE REQUIRED!
  // If you don't want to invert the strip then send "!INVERT_STRIP" as the 4th argument
  // Always need to declare a single "source" strip first
  // all other strips must have the "IS_REPLICA" argument passed in
  // this is necessary for animation functions that use static variables
  LEDStripController stripController_01sA(leds_01, 0, LEDS_01_NUM_LEDS, INVERT_STRIP, SOURCE);
  LEDStripController stripController_01sB(leds_02, 0, LEDS_02_NUM_LEDS, INVERT_STRIP, REPLICA);

  // LEDStripController stripController_01sA( aLEDs,                     0, floor(ALEN * 1.0/3.0) );
  // LEDStripController stripController_01sB( aLEDs, floor(ALEN * 1.0/3.0),  ceil(ALEN * 1.0/3.0), !INVERT_STRIP);
  // LEDStripController stripController_01sC( aLEDs, floor(ALEN * 2.0/3.0),  ceil(ALEN * 1.0/3.0),  INVERT_STRIP );
  // LEDStripController stripController_01s2( leds_01,                  15, LEDS_01_NUM_LEDS - 15, !INVERT_STRIP );

  // Array of pointers to our LEDStripController objects.
  // Makes updating them all at once more efficient
  LEDStripController *stripControllerArray[] = {  
                                                  &stripController_01sA,
                                                  &stripController_01sB
                                                };
#endif

const uint8_t NUM_STRIP_CONTROLLERS = ARRAY_SIZE(stripControllerArray);


// *********************************************************************************
//      INITIAL PROGRAM STATE DECLARATIONS
// *********************************************************************************
ProgramStates programState = ANIMATION_IS_RUNNING;



// *********************************************************************************
//      SETUP FUNCTION
// *********************************************************************************
void setup() {

  // Serial.begin(9600);

  // generate random seed value to use for random math functions by reading analogPin a few times
  uint16_t randomSeedVal = 0;

  randomSeedVal = randomSeedVal + analogRead(ANALOG_PIN);
  delay(100);
  randomSeedVal = randomSeedVal + analogRead(ANALOG_PIN);
  delay(50);
  randomSeedVal = randomSeedVal + analogRead(ANALOG_PIN);
  delay(75);
  randomSeedVal = randomSeedVal + analogRead(ANALOG_PIN);
  
  // tell the Arduino random function to use this number as a randomSeed
  randomSeed(randomSeedVal);
  
  // tell the strip controllers to initialize any parameters that rely on random numbers
//  initializeStripControllerRandomParameters();

  // delay(200);

  // THIS STEP SETS UP THE PHYSICAL REPRESENTATION OF OUR LED STRIPS
#if defined(__TRINKET_PRO_ONE_BUTTON__) || defined(__BLINKY_TAPE_ONE_BUTTON__)
  FastLED.addLeds<LED_TYPE, LEDS_01_PIN>(leds_01, LEDS_01_NUM_LEDS);
#else
  FastLED.addLeds<LED_TYPE, LEDS_01_PIN>(leds_01, LEDS_01_NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LEDS_02_PIN>(leds_02, LEDS_02_NUM_LEDS);
#endif

  // if we just want to 100% replicate the first strip do this
//  FastLED.addLeds<LED_TYPE, LEDS_02_PIN>(leds_01, LEDS_01_NUM_LEDS);
  
  // this is where we can set other global parameters for the FastLED library
  //FastLED.setCorrection(UncorrectedColor);
  //FastLED.setCorrection(TypicalPixelString);
  
  //FastLED.setDither(FAST_LED_MAX_BRIGHTNESS < 255);
  //FastLED.setBrightness(FAST_LED_MAX_BRIGHTNESS);  
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
  uint8_t primaryButtTapped = primaryButton.wasReleased();
  uint8_t primaryButtHeld = primaryButton.pressedFor(LONG_PRESS);
  uint8_t primaryButtIsPressed = primaryButton.isPressed();

  #if defined(__BLINKY_TAPE_TWO_BUTTON__)
    primaryButton_2.read();
    primaryButtTapped = ( primaryButtTapped || primaryButton_2.wasReleased() );
    primaryButtHeld = ( primaryButtHeld || primaryButton_2.pressedFor(LONG_PRESS) );
  #endif

  uint8_t secondaryButtTapped = secondaryButton.wasReleased();
  uint8_t secondaryButtHeld = secondaryButton.pressedFor(LONG_PRESS);
  uint8_t secondaryButtIsPressed = secondaryButton.isPressed();


  // TAKE ACTIONS BASED ON THE CURRENT STATE OF OUR PROGRAM AND THE UPDATED STATE OF THE BUTTONS
  switch (programState) {

    // Executes while the animation is running...
    case ANIMATION_IS_RUNNING:
    {
      if (primaryButtTapped){
        nextStripControllerAnimation();    
      }
      else if (secondaryButtTapped){
        nextStripControllerPalette();
      }      
      else if (primaryButtHeld){
        updateProgramState(TRANSITION_TO_CHANGE_BRIGHTNESS);
      }
      else if (secondaryButtHeld){
        updateProgramState(TRANSITION_TO_VIEW_PALETTES);
      }

      break;
    }
    // This is a transition state where we need to wait for the operator to release the button, 
    // i.e. release the button from a long press, before moving to the CHANGE_BRIGHTNESS state.    
    case TRANSITION_TO_CHANGE_BRIGHTNESS:
    {
      // if the primary button is released (which appears as a press), move to the CHANGE_BRIGHTNESS state
      if (primaryButtTapped){
        updateProgramState(CHANGE_BRIGHTNESS);
      }
      break;
    }
    case TRANSITION_TO_VIEW_PALETTES:
    {
      // if the primary button is released (which appears as a press), move to the CHANGE_BRIGHTNESS state
      if (secondaryButtTapped){
        updateProgramState(VIEW_PALETTES);
      }
      break;
    }
    //Watch for button presses or another long press
    case CHANGE_SPEED:
    case CHANGE_BRIGHTNESS:
    {
      if (primaryButtTapped){
        (programState == CHANGE_BRIGHTNESS) ? nextStripControllerBrightness() : updateProgramState(CHANGE_BRIGHTNESS);
      }
      else if (secondaryButtTapped){
        (programState == CHANGE_BRIGHTNESS) ? updateProgramState(CHANGE_SPEED) : nextStripControllerSpeed();
      }
      else if (primaryButtHeld){
        updateProgramState(TRANSITION_TO_ANIMATION_IS_RUNNING_PRIMARY);
      }

      break;
    }
    case VIEW_PALETTES:
    {
      if (secondaryButtTapped){
        nextStripControllerPalette();
      }
      // else if (primaryButtTapped){
      //   // do something here;
      // }
      else if (secondaryButtHeld){
        updateProgramState(TRANSITION_TO_ANIMATION_IS_RUNNING_SECONDARY);
      }

      break;
    }
    //This is a transition state where we just wait for the operator to release the button
    //before moving back to the ANIMATION_IS_RUNNING state.
    case TRANSITION_TO_ANIMATION_IS_RUNNING_PRIMARY:
    {    
      if (primaryButtTapped){
        updateProgramState(ANIMATION_IS_RUNNING);
      }
      break;
    }      
    case TRANSITION_TO_ANIMATION_IS_RUNNING_SECONDARY:
    {    
      if (secondaryButtTapped){
        updateProgramState(ANIMATION_IS_RUNNING);
      }
      break;
    }      
  }


  // THIS CODE COULD BE BETTER BUT SINCE IT'S ONLY FOR LEGACY VERSIONS WITHOUT AN ON/OFF SWITCH, WE SHOULDN'T WORRY TO MUCH
  if(!HAS_ON_OFF_SWITCH){
    // FAILSAFE METHOD FOR SETUPS WITHOUT OFF BUTTON
    // Need to be able to press and hold to turn off the strip
    // first we identify if both buttons are pressed at the same time and don't update the strip controller states
    if(programState != BOTH_BUTTONS_PRESSED && primaryButtIsPressed && secondaryButtIsPressed){
      updateProgramState(BOTH_BUTTONS_PRESSED);
    }
    // then we identify if they are both HELD and turn off the strip and await next input
    else if(programState == BOTH_BUTTONS_PRESSED && primaryButtHeld && secondaryButtHeld){
      updateProgramState(TURN_STRIP_OFF_WAIT_FOR_INPUT);
      delay(500);
      // perform one read operation, which causes our program to skip this one read (otherwise when buttons are released from long press they will register the release as a press)
      primaryButton.read();
      secondaryButton.read();
    }
    // then if any button is pressed go back to normal animation
    else if(programState == TURN_STRIP_OFF_WAIT_FOR_INPUT){
      
      if(primaryButtTapped || secondaryButtTapped){
        updateProgramState(ANIMATION_IS_RUNNING);
      }
    }
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

  if(newState != BOTH_BUTTONS_PRESSED){
    setStripControllerStates(newState);
  }
  
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



void initializeStripControllerRandomParameters() {
  for(uint8_t i = 0; i < NUM_STRIP_CONTROLLERS; i++){
    stripControllerArray[i]->initRandomParams();
  }
}
