#include <GamerBoy2x16.h>
#include "Tone440.h"

#define DELAY 70

GamerBoy2x16 gb = GamerBoy2x16();

Note melody[4] = { Note(220, 5), Note(340, 5), Note(463, 5), Note(585, 5) };

void setup() {
  gb.initialize();
  gb.sound.playMelody(melody, 4, false);
}

void loop() {
  gb.update();
  delay(DELAY);
}
