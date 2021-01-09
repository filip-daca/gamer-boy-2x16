#include "Controller.h"

// ----------------------------------------------------------------------------
// Constructor

Controller::Controller(void) {
	
};

// ----------------------------------------------------------------------------
// Public

void Controller::initialize(void) {
	calibrateJoystick();
};

void Controller::update(void) {
	updateButtons();
	updateJoystick();
};

// ----------------------------------------------------------------------------
// Private

void Controller::updateButtons(void) {
	word readValue = analogRead(PIN_BUTTONS);
	
	a = (readValue > BUTTON_A - THRESHOLD_BUTTONS 
			&&  readValue < BUTTON_A + THRESHOLD_BUTTONS)
		|| (readValue > BUTTON_AB - THRESHOLD_BUTTONS 
			&&  readValue < BUTTON_AB + THRESHOLD_BUTTONS);
		
	b = (readValue > BUTTON_B - THRESHOLD_BUTTONS
			&&  readValue < BUTTON_B + THRESHOLD_BUTTONS)
		|| (readValue > BUTTON_AB - THRESHOLD_BUTTONS 
			&&  readValue < BUTTON_AB + THRESHOLD_BUTTONS);
};

void Controller::updateJoystick(void) {
	word readValueX = analogRead(PIN_AXIS_X);
	word readValueY = analogRead(PIN_AXIS_Y);
	
  if (readValueX >= centerX) {
    x = MAX_READ - map(readValueX, CENTER, MAX_READ, centerX, MAX_READ);
  } else {
    x = MAX_READ - map(readValueX, 0, CENTER, 0, centerX);
  }
  
  if (readValueY >= centerY) {
    y = map(readValueY, CENTER, MAX_READ, centerY, MAX_READ);
  } else {
    y = map(readValueY, 0, CENTER, 0, centerY);
  }
  
  left = x < CENTER - THRESHOLD_JOY;
  right = x > CENTER + THRESHOLD_JOY;
  up = y > CENTER + THRESHOLD_JOY;
  down = y < CENTER - THRESHOLD_JOY;
};

void Controller::calibrateJoystick(void) {
  const byte SAMPLES = 4;
  
  word readsX;
  word readsY;
  
  for (byte i = 0; i < SAMPLES; ++i) {
    readsX += analogRead(PIN_AXIS_X);
    readsY += analogRead(PIN_AXIS_Y);
    delay(200);
  }
  
  centerX = readsX / SAMPLES;
	centerY = readsY / SAMPLES;
};
