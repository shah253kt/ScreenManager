#include "BooleanMenuLine.h"

BooleanMenuLine::BooleanMenuLine(char *label, const uint8_t *font, bool *booleanValue)
    : mBooleanValue(booleanValue),
      mIndicatorType(GLYPH),
      mGlyphFont(DEFAULT_SYMBOL_FONT)
{
    mLabel = label;
    mFont = font;
    mGlyphFalse = 0x0044;
    mGlyphTrue = 0x0040;
}

BooleanMenuLine::BooleanMenuLine(const __FlashStringHelper *label, const uint8_t *font, bool *booleanValue)
    : mBooleanValue(booleanValue),
      mIndicatorType(GLYPH),
      mGlyphFont(DEFAULT_SYMBOL_FONT)
{
    mLabel = new char[MAX_MENU_LABEL_LENGTH];
    strncpy_P(mLabel, (const char *)label, MAX_MENU_LABEL_LENGTH - 1);
    mFont = font;
    mGlyphFalse = 0x0044;
    mGlyphTrue = 0x0040;
}

BooleanMenuLine::~BooleanMenuLine()
{
    delete[] mLabel;
    delete mGlyphFont;
    delete[] mTextualFalse;
    delete[] mTextualTrue;
}

void BooleanMenuLine::render(U8G2 *u8g2, u8g2_uint_t y, bool highlight)
{
    drawButton(u8g2, y, highlight);

    u8g2->setDrawColor(highlight ? 0 : 1);

    if (mIndicatorType == GLYPH)
    {
        u8g2->setFont(mGlyphFont);
        u8g2->drawGlyph(u8g2->getDisplayWidth() - 15, y, *mBooleanValue ? mGlyphTrue : mGlyphFalse);
        u8g2->setFont(mFont);
    }
    else if (mIndicatorType == TEXTUAL)
    {
        char *indicator = *mBooleanValue ? mTextualTrue : mTextualFalse;
        u8g2_uint_t indicatorWidth = u8g2->getStrWidth(indicator);
        u8g2->drawStr(u8g2->getDisplayWidth() - indicatorWidth - 5, y, indicator);
    }

    u8g2->setDrawColor(1);
}

void BooleanMenuLine::propagateAction(Action action)
{
    if (action == ACTION_ENTER)
    {
        click();
        *mBooleanValue = !*mBooleanValue;

        if (onStateChangedHandler)
        {
            onStateChangedHandler();
        }
    }
}

void BooleanMenuLine::setOnStateChangedHandler(void (*handler)(void))
{
    onStateChangedHandler = handler;
}

void BooleanMenuLine::setIndicator(uint8_t *glyphFont, uint16_t glyphFalse, uint16_t glyphTrue)
{
    mIndicatorType = GLYPH;
    mGlyphFont = glyphFont;
    mGlyphFalse = glyphFalse;
    mGlyphTrue = glyphTrue;
}

void BooleanMenuLine::setIndicator(char *textualTrue, char *textualFalse)
{
    mIndicatorType = TEXTUAL;
    mTextualFalse = textualFalse;
    mTextualTrue = textualTrue;
}
