#include <U8g2lib.h>
#include "BooleanMenuLine.h"

BooleanMenuLine::BooleanMenuLine(char *label, const uint8_t *font, bool *booleanValue)
    : mBooleanValue(booleanValue)
{
    mLabel = label;
    mFont = font;
}

BooleanMenuLine::BooleanMenuLine(const __FlashStringHelper *label, const uint8_t *font, bool *booleanValue)
    : mBooleanValue(booleanValue)
{
    mLabel = new char[MAX_MENU_LABEL_LENGTH];
    strncpy_P(mLabel, (const char *)label, MAX_MENU_LABEL_LENGTH - 1);
    mFont = font;
}

BooleanMenuLine::~BooleanMenuLine()
{
    delete[] mLabel;
}

void BooleanMenuLine::render(U8G2 *u8g2, uint8_t y, bool highlight)
{
    drawButton(u8g2, y, highlight);

    u8g2->setFont(u8g2_font_open_iconic_check_1x_t);
    u8g2->setDrawColor(highlight ? 0 : 1);
    u8g2->drawGlyph(u8g2->getDisplayWidth() - 15, y, *mBooleanValue ? 0x0040 : 0x0044);
    u8g2->setDrawColor(1);
    u8g2->setFont(mFont);
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
