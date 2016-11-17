#include "MouseTypeInputEvent.h"
#include "ButtonTypeInput.h"


MouseTypeInputEvent::MouseTypeInputEvent(const ButtonTypeInput *button)
    : _button(button)
{
}


MouseTypeInputEvent::~MouseTypeInputEvent()
{
}


void MouseTypeInputEvent::Update(Vector2D vec)
{

    if (_button->ButtonDown())
    {
        for (auto buttonDownEvent : _onButtonDown)
            buttonDownEvent(vec);

        return;
    }

    if (_button->ButtonUp())
    {
        for (auto keyUpEvent : _onButtonUp)
            keyUpEvent(vec);

        return;
    }

    if (_button->ButtonBeingPressed())
    {
        for (auto keyPressingEvent : _onButtonPressing)
            keyPressingEvent(vec);

        return;
    }
}


void MouseTypeInputEvent::ClearEventsAll()
{
    _onButtonPressing.clear();
    _onButtonPressing.resize(0);
    
    _onButtonDown.clear();
    _onButtonDown.resize(0);
    
    _onButtonUp.clear();
    _onButtonUp.resize(0);
}


void MouseTypeInputEvent::ClearEvents(State state)
{
    switch (state)
    {
    case MouseTypeInputEvent::Pressing:
        _onButtonPressing.clear();
        _onButtonPressing.resize(0);
        break;

    case MouseTypeInputEvent::Down:
        _onButtonDown.clear();
        _onButtonDown.resize(0);
        break;

    case MouseTypeInputEvent::Up:
        _onButtonUp.clear();
        _onButtonUp.resize(0);
        break;

    default:
        break;
    }
}


void MouseTypeInputEvent::AddEvent(State state, std::function<void(Vector2D)> buttonEvent)
{
    switch (state)
    {
    case MouseTypeInputEvent::Pressing:
        _onButtonPressing.push_back(buttonEvent);
        break;

    case MouseTypeInputEvent::Down:
        _onButtonDown.push_back(buttonEvent);
        break;

    case MouseTypeInputEvent::Up:
        _onButtonUp.push_back(buttonEvent);
        break;

    default:
        break;
    }

}