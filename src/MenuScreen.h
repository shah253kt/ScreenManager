#ifndef MenuScreen_H_
#define MenuScreen_H_

#include "IScreen.h"
#include "ScreenManagerConstants.h"

class U8G2;
class IMenuLine;

template <class T>
class LinkedList;

class MenuScreen : public IScreen
{
private:
    LinkedList<IMenuLine *> *mMenuLines;
    uint8_t mCurrentActiveMenuIndex;

public:
    MenuScreen(char *title);
    MenuScreen(const __FlashStringHelper* title);
    ~MenuScreen();
    virtual void render(U8G2 *u8g2);
    virtual void propagateAction(Action action);
    bool addMenu(IMenuLine &menuLine);
    bool highlightNextMenu();
    bool highlightPrevMenu();
};

#endif // MenuScreen_H_
