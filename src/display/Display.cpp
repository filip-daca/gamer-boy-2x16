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
  for (byte y = 0; y < ROWS; ++y) {
    for (byte x = 0; x < COLS; ++x) {
       memset(screen[y][x], B00000, SPRITE_LEN);
       fieldActive[y][x] = false;
    }
  }
  memset(spriteUsed, false, MAX_SPRITES);
  lcd.clear();
}

void Display::draw(byte sprite[], byte x, byte y) {
  for (byte i = 0; i < SPRITE_LEN; ++i) {
    screen[y][x][i] = (screen[y][x][i] | sprite[i]);
  }
  fieldActive[y][x] = true;
}

void Display::flush() {
  for (byte y = 0; y < ROWS; ++y) {
    for (byte x = 0; x < COLS; ++x) {
      if (fieldActive[y][x]) {
        byte spriteNumber = findOrCreateSprite(screen[y][x]);
        lcd.setCursor(x, y);
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
  
  // DEBUG
  /*
  for (byte y = 0; y < 8; ++y) {
    Serial.println(sprites[2][y], BIN);
  }
  Serial.println();
  */
  
  for (byte y = 0; y < ROWS; ++y) {
    for (byte x = 0; x < 4; ++x) {
      draw(sprites[y*4 + x], bitmapAnimation.getScreenPosition() + x, y);
    }
  }
  
  for (byte i = 0; i < 8; ++i) {
    delete[] sprites[i];
  }
  delete[] sprites;
}

void Display::drawBitmap(word bitmap[], byte col) {
  
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
