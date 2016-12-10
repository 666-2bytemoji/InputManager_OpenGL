#include "MouseInput.h"
#include "Vector2D.h"
#include "Application.h"
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>

MouseInput::MouseInput()
{
    RegistRecords();
}



MouseInput::~MouseInput()
{
    Clear();
}


void MouseInput::RegistRecords()
{
    AddRecord(MouseButtonCode::MOUSE_L, GLFW_MOUSE_BUTTON_1);
    AddRecord(MouseButtonCode::MOUSE_CENTER, GLFW_MOUSE_BUTTON_2);
    AddRecord(MouseButtonCode::MOUSE_R, GLFW_MOUSE_BUTTON_3);
}


void MouseInput::AddRecord(MouseButtonCode code, int value)
{
    MouseData *data = new MouseData(code, value);
    _inputMap.insert(std::make_pair(code, data));
    _inputs.push_back(data);
}


void MouseInput::Update()
{
    //イベントを取り出す
    //glfwPollEvents();
    
    glfwGetCursorPos(_window, &_cursorPos._x, &_cursorPos._y);
    
    for (auto input : _inputs)
    {
        ButtonTypeInput &data = input->_inputData;
        data.UpdateState(glfwGetMouseButton(_window, input->_inputCode) != GLFW_RELEASE);
        _cursorPos._y *= -1;
        _cursorPos._y += WINDOW_HEIGHT;
        
        MouseTypeInputEvent &events = input->_inputEvents;
        events.Update(_cursorPos);
    }
}


void MouseInput::Clear()
{
    for (auto input : _inputs)
    {
        MouseTypeInputEvent &events = input->_inputEvents;
        events.ClearEventsAll();
    }
}