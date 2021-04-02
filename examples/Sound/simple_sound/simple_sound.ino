#include <GamerBoy2x16.h>

#define DELAY 70

GamerBoy2x16 gb = GamerBoy2x16();

void setup() {
  gb.initialize();
  gb.sound.playTone(240, 10);
}

void loop() {
  gb.update();
  delay(DELAY);
}
