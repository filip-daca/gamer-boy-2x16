#include <GamerBoy2x16.h>

#define DELAY 200

GamerBoy2x16 gb = GamerBoy2x16();

byte glyph[GLYPH_MAX_Y] = { 0x00, 0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00 };
Sprite sprite = Sprite(glyph);

byte x = 0;
byte y = 0;

void setup() {
  gb.initialize();
}

void loop() {
  gb.update();
  gb.display.clear();

  gb.display.drawSprite(sprite, x, y);

  x += 1;
  if (x > MAX_X) {
    x = 0;
  }

  y += 1;
  if (y > MAX_Y) {
    y = 0;
  }

  gb.display.flush();
  
  delay(DELAY);
}
