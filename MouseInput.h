#ifndef MouseInput_h
#define MouseInput_h

#include <unordered_map>
#include "Singleton.h"
#include "ButtonTypeInput.h"
#include "MouseTypeInputEvent.h"
#include <GLFW/glfw3.h>

class MouseInput : public Singleton<MouseInput>
{
    friend class Singleton<MouseInput>;
    friend class InputManager;
    
public:
    
    enum class MouseButtonCode
    {
        MOUSE_L = 0,
        MOUSE_R,
        MOUSE_CENTER
    };
    
    bool ButtonUp(MouseButtonCode key) const { return _inputMap.at(key)->_inputData.ButtonUp(); };
    bool ButtonDown(MouseButtonCode key) const { return _inputMap.at(key)->_inputData.ButtonDown(); };
    bool ButtonBeingPressed(MouseButtonCode key) const { return _inputMap.at(key)->_inputData.ButtonBeingPressed(); };
    
    ButtonTypeInput *GetButton(MouseButtonCode button) { return &_inputMap.at(button)->_inputData; }
    MouseTypeInputEvent *GetEvent(MouseButtonCode key) { return &_inputMap.at(key)->_inputEvents; }
    
    Vector2D GetCursorPos() const { return _cursorPos; };
    
private:
    
    MouseInput();
    ~MouseInput();
    
    void RegistRecords();
    void Update();
    void Clear();
    void SetWindow(GLFWwindow *window) { _window = window; };
    
    struct MouseData
    {
        MouseData(MouseButtonCode code, int value)
        : _code(code)
        , _inputCode(value)
        , _inputEvents(&_inputData)
        {
        }
        
        //ライブラリで用意したキー入力識別の列挙型
        MouseButtonCode _code;
        //APIに用意されてるキー入力の値
        int _inputCode;
        //ボタンの入力状態
        ButtonTypeInput _inputData;
        //入力状態に基づいたイベント
        MouseTypeInputEvent _inputEvents;
    };
    
    void AddRecord(MouseButtonCode code, int value);
    std::unordered_map<MouseButtonCode, MouseData *> _inputMap;
    std::vector<MouseData *> _inputs;
    GLFWwindow* _window;
    
    Vector2D _cursorPos;
};

#define MOUSE MouseInput::GetInstance()

#endif /* MouseInput_h */
