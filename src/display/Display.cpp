#include "Display.h"

// ----------------------------------------------------------------------------
// Constructor

Display::Display(void) : lcd(PIN_RS, PIN_EN, PIN_D4, PIN_D5, PIN_D6, PIN_D7) {
};

// ----------------------------------------------------------------------------
// Public

void Display::initialize() {
  lcd.begin(COLS, ROWS);
  
  clear();
  for (byte i = 0; i < MAX_GLYPHS; ++i) {
    memset(customGlyphs[i], B00000, GLYPH_MAX_Y);
  }
};

void Display::update() {
};

void Display::clear() {
  for (byte row = 0; row < ROWS; ++row) {
    for (byte col = 0; col < COLS; ++col) {
       memset(screen[row][col], B00000, GLYPH_MAX_Y);
       fieldActive[row][col] = false;
    }
  }
  memset(glyphUsed, false, MAX_GLYPHS);
  lcd.clear();
}

void Display::draw(byte glyph[], byte col, byte row) {
  for (byte i = 0; i < GLYPH_MAX_Y; ++i) {
    screen[row][col][i] = (screen[row][col][i] | glyph[i]);
  }
  fieldActive[row][col] = true;
}

void Display::flush() {
  for (byte row = 0; row < ROWS; ++row) {
    for (byte col = 0; col < COLS; ++col) {
      if (fieldActive[row][col]) {
        byte glyphNumber = findOrCreateGlyph(screen[row][col]);
        lcd.setCursor(col, row);
        lcd.write(glyphNumber);
      }
    }
  }

  if (DEBUG) {
    Serial.println("SPR: " + String(getUsedGlyphCount()));
  }
}

void Display::setCursor(byte col, byte row) {
  lcd.setCursor(col, row);
}

void Display::write(const char* message) {
  lcd.write(message);
}

void Display::drawCurrentFrame(BitmapAnimation& bitmapAnimation) {
  byte** glyphs = bitmapAnimation.getGlyphsFromFrame();
  
  for (byte row = 0; row < ROWS; ++row) {
    for (byte col = 0; col < 4; ++col) {
      draw(glyphs[row*4 + col], bitmapAnimation.getScreenPosition() + col, row);
    }
  }
  
  for (byte i = 0; i < 8; ++i) {
    delete[] glyphs[i];
  }
  delete[] glyphs;
}

void Display::drawBitmap(word bitmap[], byte col) {
  
}

void Display::drawSprite(Sprite& sprite, byte x, byte y) {
  byte glyphs[4][GLYPH_MAX_Y];

  byte col = x / GLYPH_MAX_X;
  byte row = y / GLYPH_MAX_Y;

  // TODO: fill 4 glyphs using sprite
  
  draw(glyphs[0], col, row);
  draw(glyphs[1], col + 1, row);
  draw(glyphs[2], col, row + 1);
  draw(glyphs[3], col + 1, row + 1);
}

// ----------------------------------------------------------------------------
// Private

byte Display::findOrCreateGlyph(byte glyph[]) {
  for (byte i = 0; i < MAX_GLYPHS; ++i) {
    if (glyphUsed[i] && memcmp(glyph, customGlyphs[i], GLYPH_MAX_Y) == 0) {
      return i;
    }
  }
  
  byte i = 0;
  while (glyphUsed[i] && i < MAX_GLYPHS) {
    i++;
  }

  glyphUsed[i] = true;
  memcpy(customGlyphs[i], glyph, GLYPH_MAX_Y);
  lcd.createChar(i, glyph);

  return i;
}

byte Display::getUsedGlyphCount() {
  byte count = 0;
  for (byte i = 0; i < MAX_GLYPHS; ++i) {
    if (glyphUsed[i]) {
      count++;
    }
  }
  return count;
}
