#ifndef BooleanMenuLine_H_
#define BooleanMenuLine_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <U8g2lib.h>
#include "ScreenManagerConstants.h"
#include "IMenuLine.h"

#define DEFAULT_SYMBOL_FONT u8g2_font_open_iconic_check_1x_t

enum IndicatorType
{
    GLYPH,
    TEXTUAL
};

class BooleanMenuLine : public IMenuLine
{
private:
    bool *mBooleanValue;
    const uint8_t *mGlyphFont;
    uint16_t mGlyphFalse, mGlyphTrue;
    char *mTextualFalse, *mTextualTrue;
    IndicatorType mIndicatorType;

    void (*onStateChangedHandler)(void);

public:
    BooleanMenuLine(char *label, const uint8_t *font, bool *booleanValue);
    BooleanMenuLine(const __FlashStringHelper *label, const uint8_t *font, bool *booleanValue);
    virtual ~BooleanMenuLine();
    virtual void render(U8G2 *u8g2, u8g2_uint_t y, bool highlight);
    virtual void propagateAction(Action action);
    void setOnStateChangedHandler(void (*handler)(void));
    void setIndicator(uint8_t *glyphFont, uint16_t mGlyphFalse, uint16_t mGlyphTrue);
    void setIndicator(char *textualTrue, char *textualFalse);
};

#endif // BooleanMenuLine_H_