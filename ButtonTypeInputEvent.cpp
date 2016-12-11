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


ButtonTypeInputEvent::Event* ButtonTypeInputEvent::AddEvent(ButtonState state,
                                                            ButtonTypeInputEvent::Event buttonEvent)
{
    Event* ptr = nullptr;
    
    switch (state)
    {
    case ButtonTypeInputEvent::Pressing:
            _onButtonPressing.push_back(buttonEvent);
            ptr = &_onButtonPressing[_onButtonPressing.size() - 1];
            break;

    case ButtonTypeInputEvent::Down:
            _onButtonDown.push_back(buttonEvent);
            ptr = &_onButtonDown[_onButtonDown.size() - 1];
            break;

    case ButtonTypeInputEvent::Up:
            _onButtonUp.push_back(buttonEvent);
            ptr = &_onButtonUp[_onButtonUp.size() - 1];
            break;
    }
    
    return ptr;
}


void ButtonTypeInputEvent::RemoveEvent(ButtonState state, Event* buttonEventPtr)
{
    Events* events = nullptr;
    
    switch (state)
    {
        case ButtonTypeInputEvent::Pressing:
            events = &_onButtonPressing;
            break;
            
        case ButtonTypeInputEvent::Down:
            events = &_onButtonDown;
            break;
            
        case ButtonTypeInputEvent::Up:
            events = &_onButtonUp;
            break;
    }
    
    if (events == nullptr)
        return;
    
    auto it = events->begin();
    for (size_t i=0; i<events->size() ; ++i)
    {
        if (&(*events)[i] == buttonEventPtr)
        {
            events->erase(it);
            break;
        }
        
        it++;
    }
}