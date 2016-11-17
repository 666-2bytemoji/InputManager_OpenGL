#pragma once
#include <unordered_map>
#include "../Utility/Singleton.h"
#include "ButtonTypeInput.h"
#include "ButtonTypeInputEvent.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "CustomInput.h"
#include <GLFW/glfw3.h>

class InputManager : public Singleton<InputManager>
{
    friend class Singleton<InputManager>;
    
public:
        
    void Clear();
    void Update();
    void SetWindow(GLFWwindow *window)
    {
        _window = window;
        MOUSE->SetWindow(window);
        KEYBOARD->SetWindow(window);
    };
    
private:
    
    InputManager();
    ~InputManager(){};
    GLFWwindow* _window;
};

#define INPUT_MGR InputManager::GetInstance()