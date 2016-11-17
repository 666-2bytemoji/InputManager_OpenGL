#include "ButtonTypeInputEvent.h"
#include "ButtonTypeInput.h"

ButtonTypeInputEvent::ButtonTypeInputEvent(const ButtonTypeInput *button)
    : _button(button)
{
}


ButtonTypeInputEvent::~ButtonTypeInputEvent()
{
}


void ButtonTypeInputEvent::Update()
{
    if (_button->ButtonDown())
    {
        for (auto buttonDownEvent : _onButtonDown)
            buttonDownEvent();

        return;
    }

    if (_button->ButtonUp())
    {
        for (auto keyUpEvent : _onButtonUp)
            keyUpEvent();

        return;
    }

    if (_button->ButtonBeingPressed())
    {
        for (auto keyPressingEvent : _onButtonPressing)
            keyPressingEvent();

        return;
    }
}


void ButtonTypeInputEvent::ClearEventsAll()
{
    _onButtonPressing.clear();
    _onButtonPressing.resize(0);
    
    _onButtonDown.clear();
    _onButtonDown.resize(0);
    
    _onButtonUp.clear();
    _onButtonUp.resize(0);
}

void ButtonTypeInputEvent::ClearEvents(ButtonState state)
{
    switch (state)
    {
    case ButtonTypeInputEvent::Pressing:
        _onButtonPressing.clear();
        _onButtonPressing.resize(0);
        break;

    case ButtonTypeInputEvent::Down:
        _onButtonDown.clear();
        _onButtonDown.resize(0);
        break;

    case ButtonTypeInputEvent::Up:
        _onButtonUp.clear();
        _onButtonUp.resize(0);
        break;

    default:
        break;
    }
}


void ButtonTypeInputEvent::AddEvent(ButtonState state, std::function<void()> buttonEvent)
{
    switch (state)
    {
    case ButtonTypeInputEvent::Pressing:
        _onButtonPressing.push_back(buttonEvent);
        break;

    case ButtonTypeInputEvent::Down:
        _onButtonDown.push_back(buttonEvent);
        break;

    case ButtonTypeInputEvent::Up:
        _onButtonUp.push_back(buttonEvent);
        break;

    default:
        break;
    }
}