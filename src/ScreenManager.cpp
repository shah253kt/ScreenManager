#include <U8g2lib.h>
#include <LinkedList.h>
#include "IScreen.h"
#include "ScreenManager.h"

ScreenManager::ScreenManager(U8G2 &u8g2)
    : mRenderer(&u8g2)
{
    screenStack = new LinkedList<IScreen *>();
}

ScreenManager::~ScreenManager()
{
    delete mRenderer;
    delete screenStack;
}

void ScreenManager::update()
{
    if (screenStack->size() > 0)
    {
        render(screenStack->get(0));
    }
}

void ScreenManager::render(IScreen *screen)
{
    mRenderer->clearBuffer();
    screen->render(mRenderer);
    mRenderer->sendBuffer();
}

bool ScreenManager::gotoScreen(IScreen &screen)
{
    if (screenStack->unshift(&screen))
    {
        update();
        return true;
    }

    return false;
}

bool ScreenManager::gotoPrevScreen()
{
    if (screenStack->size() > 1 && screenStack->shift())
    {
        update();
        return true;
    }

    return false;
}

void ScreenManager::propagateAction(Action action)
{
    if (screenStack->size() > 0)
    {
        IScreen *screen = screenStack->get(0);

        if (action == ACTION_BACK && screen->getType() != SPLASH_SCREEN && screen->getType() != CUSTOM_SCREEN)
        {
            gotoPrevScreen();
        }
        else
        {
            screen->propagateAction(action);
            update();
        }
    }
}
