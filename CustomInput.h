#ifndef CustomInpur_h
#define CustomInpur_h
#include <unordered_map>
#include "../Utility/Singleton.h"
#include "ButtonInputData.h"
#include "KeyInput.h"
#include "ButtonTypeInput.h"
#include "ButtonTypeInputEvent.h"
#include <GLFW/glfw3.h>


class CustomInput : public Singleton<CustomInput>
{
    friend class Singleton<CustomInput>;
    friend class InputManager;
    
public:
    
    enum class CustomInputType
    {
        BUTTON0 = 0,
        BUTTON1,
        BUTTON2,
        BUTTON3,
        BUTTON4,
        BUTTON5,
        BUTTON6,
        BUTTON7,
        BUTTON8,
        BUTTON9
    };
    
    bool ButtonUp(CustomInputType key) const { return _inputMap.at(key)->_origin->_inputData.ButtonUp(); };
    bool ButtonDown(CustomInputType key) const { return _inputMap.at(key)->_origin->_inputData.ButtonDown(); };
    bool ButtonBeingPressed(CustomInputType key) const { return _inputMap.at(key)->_origin->_inputData.ButtonBeingPressed(); };
    
    ButtonTypeInput *GetCustomButtob(CustomInputType key) { return &_inputMap.at(key)->_origin->_inputData; }
    ButtonTypeInputEvent *GetEvent(CustomInputType key) { return &_inputMap.at(key)->_origin->_inputEvents; }
    
    void ReplaceButtonCode(CustomInputType input, KeyInput::KeyType key);
    
private:
    
    CustomInput();
    ~CustomInput();
    
    void RegistRecords();
    void Clear();
    
    class CustomInputData
    {
    public:
        CustomInputData(CustomInputType type, ButtonInputData *data)
        : _origin(data)
        , _type(type)
        {
        }
        
        //ライブラリで用意したキー入力識別の列挙型
        CustomInputType _type;
        //
        ButtonInputData *_origin;
    };
    
    void AddRecord(CustomInputType type, ButtonInputData* data);
    std::unordered_map<CustomInputType, CustomInputData *> _inputMap;
    std::vector<CustomInputData *> _usingInputs;
};

#define CUSTOM_INPUT CustomInput::GetInstance()

#endif /* CustomInpur_h */
