#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "BitmapAnimation.h"
#include "Sprite.h"

#define MAX_X         5*16
#define MAX_Y         8*2
#define COLS          16
#define ROWS          2

#define MAX_GLYPHS    8
#define GLYPH_MAX_X   5
#define GLYPH_MAX_Y   8

#define DEBUG 0


static const byte PIN_RS = 2;
static const byte PIN_EN = 3;
static const byte PIN_D4 = 4;
static const byte PIN_D5 = 5;
static const byte PIN_D6 = 6;
static const byte PIN_D7 = 7;

class Display {
  public:
    Display(void);
    
    void initialize();
    void update();
    void clear();
    void draw(byte glyph[], byte col, byte row);
    void flush();
    void setCursor(byte col, byte row);
    void write(const char* message);
    void drawCurrentFrame(BitmapAnimation& bitmapAnimation);
    void drawBitmap(word bitmap[], byte col);
    void drawSprite(Sprite& sprite, byte x, byte y);
    
  private:
    LiquidCrystal lcd;
    byte screen[ROWS][COLS][GLYPH_MAX_Y];
    byte customGlyphs[MAX_GLYPHS][GLYPH_MAX_Y];
    bool glyphUsed[MAX_GLYPHS];
    bool fieldActive[ROWS][COLS];
    
    byte findOrCreateGlyph(byte glyph[]);
    byte getUsedGlyphCount();
};

#endif
