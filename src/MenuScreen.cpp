#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <LinkedList.h>
#include "MenuScreen.h"
#include "IMenuLine.h"
#include "ScreenManagerConstants.h"

MenuScreen::MenuScreen(char *title)
    : mCurrentActiveMenuIndex(0)
{
    mScreenType = MENU_SCREEN;
    mTitle = title;
    mMenuLines = new LinkedList<IMenuLine *>();
}

MenuScreen::MenuScreen(const __FlashStringHelper *title)
    : mCurrentActiveMenuIndex(0)
{
    mScreenType = MENU_SCREEN;
    mTitle = new char[MAX_SCREEN_TITLE_LENGTH];
    strncpy_P(mTitle, (const char *)title, MAX_SCREEN_TITLE_LENGTH - 1);
    mMenuLines = new LinkedList<IMenuLine *>();
}

MenuScreen::~MenuScreen()
{
    delete[] mTitle;
    delete mMenuLines;
}

void MenuScreen::render(U8G2 *u8g2)
{
    preRender();
    IMenuLine *menuLine;
    drawTitle(u8g2);

    for (uint8_t i = 0; i < mMenuLines->size(); i++)
    {
        menuLine = mMenuLines->get(i);
        menuLine->render(u8g2, (i + 1) * mTextHeight, i == mCurrentActiveMenuIndex);
    }

    postRender();
}

void MenuScreen::propagateAction(Action action)
{
    if (action == ACTION_ARROW_UP)
    {
        highlightPrevMenu();
    }
    else if (action == ACTION_ARROW_DOWN)
    {
        highlightNextMenu();
    }
    else
    {
        mMenuLines->get(mCurrentActiveMenuIndex)->propagateAction(action);
    }

    propagateActionExternally(action);
}

bool MenuScreen::addMenu(IMenuLine &menuLine)
{
    return mMenuLines->add(&menuLine);
}

bool MenuScreen::highlightNextMenu()
{
    if (mCurrentActiveMenuIndex >= mMenuLines->size() - 1)
    {
        return false;
    }

    mCurrentActiveMenuIndex++;
    return true;
}

bool MenuScreen::highlightPrevMenu()
{
    if (mCurrentActiveMenuIndex == 0)
    {
        return false;
    }

    mCurrentActiveMenuIndex--;
    return true;
}
