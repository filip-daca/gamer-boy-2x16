#include <GamerBoy2x16.h>
#include "Tone440.h"

#define DELAY 70

GamerBoy2x16 gb = GamerBoy2x16();

Note song[24] = { 
  Note(NOTE_FS5, 8), Note(NOTE_FS5, 8), Note(NOTE_D5, 8), Note(NOTE_B4, 4), Note(NOTE_B4, 4), Note(NOTE_E5, 4), 
  Note(NOTE_E5, 4), Note(NOTE_E5, 8), Note(NOTE_GS5, 8), Note(NOTE_GS5, 8), Note(NOTE_A5, 8), Note(NOTE_B5, 8), 
  Note(NOTE_A5, 8), Note(NOTE_A5, 8), Note(NOTE_A5, 8), Note(NOTE_E5, 4), Note(NOTE_D5, 4), Note(NOTE_FS5, 4), 
  Note(NOTE_FS5, 4), Note(NOTE_FS5, 8), Note(NOTE_E5, 8), Note(NOTE_E5, 8), Note(NOTE_FS5, 8), Note(NOTE_E5, 8)
};

void setup() {
  gb.initialize();
  gb.sound.playMelody(song, 24, true);
}

void loop() {
  gb.update();
  delay(DELAY);
}
