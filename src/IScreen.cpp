#include <U8g2lib.h>
#include "IScreen.h"

void IScreen::drawCenteredText(U8G2 *u8g2, char *text, uint16_t y)
{
    u8g2->drawButtonUTF8(u8g2->getDisplayWidth() / 2, y, U8G2_BTN_HCENTER | U8G2_BTN_BW0, u8g2->getDisplayWidth(), 0, 0, text);
    mTextHeight = u8g2->getAscent() - u8g2->getDescent() + 2;
}

void IScreen::drawTitle(U8G2 *u8g2)
{
    drawCenteredText(u8g2, mTitle, 0);
    u8g2->drawHLine(0, mTextHeight, u8g2->getDisplayWidth());
}
