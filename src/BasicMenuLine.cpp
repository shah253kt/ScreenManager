#include "BasicMenuLine.h"

BasicMenuLine::BasicMenuLine(char *label, const uint8_t *font)
{
    mLabel = label;
    mFont = font;
}

BasicMenuLine::BasicMenuLine(const __FlashStringHelper* label, const uint8_t *font)
{
    mLabel = new char[MAX_MENU_LABEL_LENGTH];
    strncpy_P(mLabel, (const char *)label, MAX_MENU_LABEL_LENGTH - 1);
    mFont = font;
}

BasicMenuLine::~BasicMenuLine()
{
    delete[] mLabel;
}

void BasicMenuLine::render(U8G2 *u8g2, u8g2_uint_t y, bool highlight)
{
    drawButton(u8g2, y, highlight);
}

void BasicMenuLine::propagateAction(Action action)
{
    if (action == ACTION_ENTER)
    {
        click();
    }
}
