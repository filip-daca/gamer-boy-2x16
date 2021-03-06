#include <GamerBoy2x16.h>

#define DELAY 1500

GamerBoy2x16 gb = GamerBoy2x16();

byte glyphs[13][GLYPH_MAX_Y] = {
  { 0x00, 0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00 },
  { 0x00, 0x00, 0x0A, 0x00, 0x00, 0x0E, 0x11, 0x00 },
  { 0x00, 0x00, 0x0A, 0x00, 0x00, 0x0E, 0x00, 0x00 },
  { 0x0E, 0x11, 0x1B, 0x11, 0x11, 0x0E, 0x0A, 0x00 },
  { 0x00, 0x0E, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x0E },
  { 0x00, 0x1F, 0x1B, 0x15, 0x11, 0x1F, 0x00, 0x00 },
  { 0x0E, 0x0A, 0x0E, 0x04, 0x04, 0x06, 0x04, 0x06 },
  { 0x00, 0x04, 0x05, 0x07, 0x14, 0x1C, 0x04, 0x04 },
  { 0x00, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04 },
  { 0x00, 0x0E, 0x11, 0x11, 0x1F, 0x1B, 0x1B, 0x1F },
  { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 },
  { 0x00, 0x04, 0x0E, 0x0A, 0x0A, 0x0A, 0x1F, 0x04 },
  { 0x00, 0x00, 0x0E, 0x11, 0x1F, 0x15, 0x0E, 0x00 }
};

void setup() {
  gb.initialize();
}

void loop() {
  gb.update();
  gb.display.clear();

  gb.display.setCursor(0, 0);
  gb.display.write("Dynamic glyphs");

  drawRandomGlyph(1, 1);
  drawRandomGlyph(3, 1);
  drawRandomGlyph(5, 1);
  drawRandomGlyph(7, 1);
  drawRandomGlyph(9, 1);
  drawRandomGlyph(11, 1);
  drawRandomGlyph(13, 1);
  drawRandomGlyph(15, 1);

  gb.display.flush();
  
  delay(DELAY);
}

void drawRandomGlyph(byte x, byte y) {
  byte glyphIndex = random(0, 13);
  gb.display.draw(glyphs[glyphIndex], x, y);
}
