#ifndef GamerBoy2x16_h
#define GamerBoy2x16_h

#include "Arduino.h"

#include "controller/Controller.h"
#include "data/LimitedStack.h"
#include "display/Display.h"
#include "sound/Sound.h"

#define DEBUG 0

class GamerBoy2x16 {
  public:
    GamerBoy2x16(void);
    void initialize(void);
    void update(void);
  
    Controller controller;
    Display display;
    Sound sound;
};

// ----------------------------------------------------------------------------
// Constructor

GamerBoy2x16::GamerBoy2x16(void) {
  controller = Controller();
  display = Display();
  sound = Sound();
};

// ----------------------------------------------------------------------------
// Public

void GamerBoy2x16::initialize(void) {
  controller.initialize();
  display.initialize();
  sound.initialize();
};

void GamerBoy2x16::update(void) {
  controller.update();
  display.update();
  sound.update();
};

#endif
