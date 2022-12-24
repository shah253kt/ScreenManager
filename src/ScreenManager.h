#ifndef ScreenManager_H_
#define ScreenManager_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ScreenManagerConstants.h"

// Forward declarations
class U8G2;
class IScreen;

template <class T>
class LinkedList;

class ScreenManager
{
private:
    U8G2 *mRenderer;
    LinkedList<IScreen *> *screenStack;

public:
    ScreenManager(U8G2 &u8g2);
    ~ScreenManager();

    void update();
    void render(IScreen *screen);
    bool gotoScreen(IScreen &screen);
    bool gotoPrevScreen();
    void propagateAction(Action action);
};

#endif // ScreenManager_H_
