#ifndef Controller_h
#define Controller_h

#include "Arduino.h"

#define MAX_READ      1024
#define CENTER        512

#define DEBUG 0


static const word BUTTON_A          = 768;
static const word BUTTON_B          = 512;
static const word BUTTON_AB         = 820;

static const byte THRESHOLD_BUTTONS = 20;
static const byte THRESHOLD_JOY     = 15;

static const byte PIN_BUTTONS       = A0;
static const byte PIN_AXIS_Y        = A1;
static const byte PIN_AXIS_X        = A2;

class Controller {
  public:
    Controller(void);
    
    word x;
    word y;
    bool a;
    bool b;
    
    bool left;
    bool right;
    bool up;
    bool down;
    
    void initialize(void);
    void update(void);
    void calibrateJoystick(void);
  
  private:
    word centerX;
    word centerY;
  
    void updateButtons(void);
    void updateJoystick(void);
};

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
    x = MAX_READ - map(readValueX, centerX, MAX_READ, CENTER, MAX_READ);
  } else {
    x = MAX_READ - map(readValueX, 0, centerX, 0, CENTER);
  }
  
  if (readValueY >= centerY) {
    y = map(readValueY, centerY, MAX_READ, CENTER, MAX_READ);
  } else {
    y = map(readValueY, 0, centerY, 0, CENTER);
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


#endif
