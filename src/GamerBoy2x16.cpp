#include "GamerBoy2x16.h"

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
