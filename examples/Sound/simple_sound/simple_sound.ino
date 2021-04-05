#include <GamerBoy2x16.h>

#define DELAY 70

GamerBoy2x16 gb = GamerBoy2x16();

void setup() {
  gb.initialize();
  gb.sound.playTone(240, 10);
  gb.sound.playTone(540, 5);
}

void loop() {
  gb.update();
  delay(DELAY);
}
