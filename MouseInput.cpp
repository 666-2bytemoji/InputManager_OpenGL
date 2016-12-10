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
    
    Vector2D cursorPos;
    glfwGetCursorPos(_window, &cursorPos._x, &cursorPos._y);
    
    for (auto input : _inputs)
    {
        ButtonTypeInput &data = input->_inputData;
        data.UpdateState(glfwGetMouseButton(_window, input->_inputCode) != GLFW_RELEASE);
        cursorPos._y *= -1;
        cursorPos._y += WINDOW_HEIGHT;
        
        MouseTypeInputEvent &events = input->_inputEvents;
        events.Update(cursorPos);
    }
    
    UpdateDoubleClickStaet();
}


void MouseInput::UpdateDoubleClickStaet()
{
    _hasDoubleClicked = false;
    
    //ダブルクリック検出
    if (_hasClicked)
        _countFromFirst++;
    
    if (ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
    {
        //初回クリック見検出なら
        if (!_hasClicked)
        {
            _hasClicked = true;
            _countFromFirst = 0;
        }
        //規定フレーム内にクリックを検出してるなら
        else if (_countFromFirst < 30)
        {
            _hasDoubleClicked = true;
            
            //カウントリセット
            _hasClicked = false;
            _countFromFirst = 0;
            return;
        }
    }
    
    //カウントリセット
    if (_countFromFirst == 30)
    {
        _hasClicked = false;
        _countFromFirst = 0;
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