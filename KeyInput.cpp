#include "KeyInput.h"
#include "Vector2D.h"
#include "Application.h"
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>

KeyInput::KeyInput()
{
    RegistRecords();
}



KeyInput::~KeyInput()
{
    Clear();
}


void KeyInput::RegistRecords()
{
    AddRecord(KeyType::KEY_Z, 'Z');
    AddRecord(KeyType::KEY_X, 'X');
    AddRecord(KeyType::KEY_C, 'C');
    AddRecord(KeyType::KEY_V, 'V');
    AddRecord(KeyType::KEY_LSHIHT, GLFW_KEY_LEFT_SHIFT);
    AddRecord(KeyType::KEY_SPACE, GLFW_KEY_SPACE);
    AddRecord(KeyType::KEY_ARROW_LEFT, GLFW_KEY_LEFT);
    AddRecord(KeyType::KEY_ARROW_RIGHT, GLFW_KEY_RIGHT);
    AddRecord(KeyType::KEY_ARROW_UP, GLFW_KEY_UP);
    AddRecord(KeyType::KEY_ARROW_DOWN, GLFW_KEY_DOWN);
}


void KeyInput::AddRecord(KeyType type, int value)
{
    auto *data = new KeyInputData(type, value);
    _inputMap.insert(std::make_pair(type, data));
    _usingInputs.push_back(data);
}


void KeyInput::Update()
{
    //イベントを取り出す
    //glfwPollEvents();
    
    for (auto input : _usingInputs)
    {
        //押されているかどうかをもとに状態更新
        ButtonTypeInput &data = input->_inputData;
        data.UpdateState( (glfwGetKey(_window, input->_inputCode) != GLFW_RELEASE) );
        
        //状態をもとにイベントを駆動させる
        ButtonTypeInputEvent &events = input->_inputEvents;
        events.Update();
    }
}


void KeyInput::Clear()
{
    for (auto input : _usingInputs)
    {
        ButtonTypeInputEvent &events = input->_inputEvents;
        events.ClearEventsAll();
    }
}


KeyInput::KeyType KeyInput::GetInputedType() const
{
    for (auto input : _usingInputs)
    {
        if (input->_inputData.ButtonDown())
            return input->_type;
    }
    
    return KeyType::NONE;
}


int KeyInput::GetInputedCode() const
{
    for (auto input : _usingInputs)
    {
        if (input->_inputData.ButtonDown())
            return input->_inputCode;
    }
    
    return 0;
}


int KeyInput::GetCodeOfType(KeyType type) const
{
    for (auto input : _usingInputs)
    {
        if (input->_type == type)
            return input->_inputCode;
    }
    
    return 0;
}