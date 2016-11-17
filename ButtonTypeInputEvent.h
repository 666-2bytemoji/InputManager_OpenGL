#pragma once
#include <functional>
#include <vector>

class ButtonTypeInput;

class ButtonTypeInputEvent
{
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
    void AddEvent(ButtonState state, std::function<void()> buttonEvent);

private:
    const ButtonTypeInput *_button;

    Events _onButtonPressing;
    Events _onButtonDown;
    Events _onButtonUp;
};

