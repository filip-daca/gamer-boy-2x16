#include "GamerBoy2x16.h"
#include "controller/Controller.h"


// ----------------------------------------------------------------------------
// Constructor

GamerBoy2x16::GamerBoy2x16(void) {
	controller = Controller();
};

// ----------------------------------------------------------------------------
// Public

void GamerBoy2x16::initialize(void) {
	controller.initialize();
};

void GamerBoy2x16::update(void) {
	controller.update();
};
