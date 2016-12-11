#pragma once
#include <functional>
#include <vector>

class ButtonTypeInput;

class ButtonTypeInputEvent
{
    typedef std::function<void()> Event;
    typedef std::vector<std::function<void()>> Events;

public:

    enum ButtonState
    {
        Pressing = 0,
        Down,
        Up
    };

    ButtonTypeInputEvent(const ButtonTypeInput *button);
    ~ButtonTypeInputEvent();

    void Update();

    void ClearEventsAll();
    void ClearEvents(ButtonState state);
    
    Event* AddEvent(ButtonState state, Event buttonEvent);
    void RemoveEvent(ButtonState state, Event* buttonEventPtr);

private:
    const ButtonTypeInput *_button;

    Events _onButtonPressing;
    Events _onButtonDown;
    Events _onButtonUp;
};

