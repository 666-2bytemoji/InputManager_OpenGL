#pragma once
#include <functional>
#include <vector>
#include "Vector2D.h"

class ButtonTypeInput;

class MouseTypeInputEvent
{
    typedef std::vector<std::function<void(Vector2D)>> Events;

public:

    enum State
    {
        Pressing = 0,
        Down,
        Up
    };

    MouseTypeInputEvent(const ButtonTypeInput *button);
    ~MouseTypeInputEvent();

    void Update(Vector2D vec);
    
    void ClearEventsAll();
    void ClearEvents(State state);
    void AddEvent(State state, std::function<void(Vector2D)> buttonEvent);

private:
    const ButtonTypeInput *_button;

    Events _onButtonPressing;
    Events _onButtonDown;
    Events _onButtonUp;
};

