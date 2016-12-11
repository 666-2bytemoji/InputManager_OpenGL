#ifndef KeyInput_h
#define KeyInput_h

#include <unordered_map>
#include "../Utility/Singleton.h"
#include "ButtonInputData.h"
#include <GLFW/glfw3.h>

class KeyInput : public Singleton<KeyInput>
{
    friend class Singleton<KeyInput>;
    friend class InputManager;
    
public:
    
    enum class KeyType
    {
        KEY_Z = 0,
        KEY_X,
        KEY_C,
        KEY_V,
        KEY_LSHIHT,
        KEY_SPACE,
        KEY_ARROW_LEFT ,
        KEY_ARROW_RIGHT,
        KEY_ARROW_UP,
        KEY_ARROW_DOWN,
        
        NONE
    };
    
    bool ButtonUp(KeyType key) const { return _inputMap.at(key)->_inputData.ButtonUp(); };
    bool ButtonDown(KeyType key) const { return _inputMap.at(key)->_inputData.ButtonDown(); };
    bool ButtonBeingPressed(KeyType key) const { return _inputMap.at(key)->_inputData.ButtonBeingPressed(); };
    
    ButtonTypeInput *GetKey(KeyType key) { return &_inputMap.at(key)->_inputData; }
    ButtonTypeInputEvent *GetEvent(KeyType key) { return &_inputMap.at(key)->_inputEvents; }

    std::function<void()>* AddEvent(KeyType key, ButtonTypeInputEvent::ButtonState state, std::function<void()> eve)
    {
        return GetEvent(key)->AddEvent(state, eve);
    }
    void RemoveEvent(KeyType key, ButtonTypeInputEvent::ButtonState state, std::function<void()>* eve)
    {
        GetEvent(key)->RemoveEvent(state, eve);
    }
    
    //押されたキーを検出する
    KeyType GetInputedType() const;
    //押されたキーのAPI上のキー番号を取得する
    int GetInputedCode() const;
    //API上のキー番号からキーを取得する
    int GetCodeOfType(KeyType type) const;

    ButtonInputData* GetButtonInputData(KeyType key) { return _inputMap.at(key); };
    
private:
    
    KeyInput();
    ~KeyInput();
    
    void RegistRecords();
    void Update();
    void Clear();
    void SetWindow(GLFWwindow *window) { _window = window; };
    
    class KeyInputData : public ButtonInputData
    {
    public:
        KeyInputData(KeyType type, int value)
        : ButtonInputData(value)
        , _type(type)
        {
        }
        
        //ライブラリで用意したキー入力識別の列挙型
        KeyType _type;
    };
    
    void AddRecord(KeyType type, int value);
    std::unordered_map<KeyType, KeyInputData *> _inputMap;
    std::vector<KeyInputData *> _usingInputs;
    GLFWwindow* _window;
};

#define KEYBOARD KeyInput::GetInstance()

#endif /* KeyInput_h */
