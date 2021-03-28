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
  for (byte i = 0; i < MAX_SPRITES; ++i) {
    memset(customSprites[i], B00000, SPRITE_LEN);
  }
};

void Display::update() {
};

void Display::clear() {
  for (byte row = 0; row < ROWS; ++row) {
    for (byte col = 0; col < COLS; ++col) {
       memset(screen[row][col], B00000, SPRITE_LEN);
       fieldActive[row][col] = false;
    }
  }
  memset(spriteUsed, false, MAX_SPRITES);
  lcd.clear();
}

void Display::draw(byte sprite[], byte col, byte row) {
  for (byte i = 0; i < SPRITE_LEN; ++i) {
    screen[row][col][i] = (screen[row][col][i] | sprite[i]);
  }
  fieldActive[row][col] = true;
}

void Display::flush() {
  for (byte row = 0; row < ROWS; ++row) {
    for (byte col = 0; col < COLS; ++col) {
      if (fieldActive[row][col]) {
        byte spriteNumber = findOrCreateSprite(screen[row][col]);
        lcd.setCursor(col, row);
        lcd.write(spriteNumber);
      }
    }
  }

  if (DEBUG) {
    Serial.println("SPR: " + String(getUsedSpriteCount()));
  }
}

void Display::setCursor(byte col, byte row) {
  lcd.setCursor(col, row);
}

void Display::write(const char* message) {
  lcd.write(message);
}

void Display::drawCurrentFrame(BitmapAnimation& bitmapAnimation) {
  byte** sprites = bitmapAnimation.getSpritesFromFrame();
  
  for (byte row = 0; row < ROWS; ++row) {
    for (byte col = 0; col < 4; ++col) {
      draw(sprites[row*4 + col], bitmapAnimation.getScreenPosition() + col, row);
    }
  }
  
  for (byte i = 0; i < 8; ++i) {
    delete[] sprites[i];
  }
  delete[] sprites;
}

void Display::drawBitmap(word bitmap[], byte col) {
  
}

void Display::drawSprite(Sprite& sprite, byte x, byte y) {
  byte glyphs[4][SPRITE_LEN];

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

byte Display::findOrCreateSprite(byte sprite[]) {
  for (byte i = 0; i < MAX_SPRITES; ++i) {
    if (spriteUsed[i] && memcmp(sprite, customSprites[i], SPRITE_LEN) == 0) {
      return i;
    }
  }
  
  byte i = 0;
  while (spriteUsed[i] && i < MAX_SPRITES) {
    i++;
  }

  spriteUsed[i] = true;
  memcpy(customSprites[i], sprite, SPRITE_LEN);
  lcd.createChar(i, sprite);

  return i;
}

byte Display::getUsedSpriteCount() {
  byte count = 0;
  for (byte i = 0; i < MAX_SPRITES; ++i) {
    if (spriteUsed[i]) {
      count++;
    }
  }
  return count;
}
