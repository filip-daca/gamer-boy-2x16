#include <GamerBoy2x16.h>

GamerBoy2x16 gb = GamerBoy2x16();

void setup() {
  gb.initialize();
  gb.display.setCursor(0, 0);
  gb.display.write("Gamer Boy 2x16");
}

void loop() {

}
