#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <U8g2lib.h>
#include "CustomScreen.h"

CustomScreen::CustomScreen()
{
    mScreenType = CUSTOM_SCREEN;
}

CustomScreen::~CustomScreen()
{
}

void CustomScreen::render(U8G2 *u8g2)
{
    preRender();

    if (mExternalRender)
    {
        mExternalRender();
    }

    postRender();
}

void CustomScreen::propagateAction(Action action)
{
    propagateActionExternally(action);
}

void CustomScreen::setRender(void (*renderFunc)(void))
{
    mExternalRender = renderFunc;
}
