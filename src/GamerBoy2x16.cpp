#include "GamerBoy2x16.h"
#include "controller/Controller.h"


GamerBoy2x16::GamerBoy2x16(void)
{
	controller = Controller();
};

void GamerBoy2x16::initialize(void) {
	controller.initialize();
};
