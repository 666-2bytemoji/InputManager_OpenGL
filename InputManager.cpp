#include "InputManager.h"
#include "Vector2D.h"
#include "Application.h"
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>

InputManager::InputManager()
{
}


void InputManager::Update()
{
    //イベントを取り出す
    glfwPollEvents();

    KEYBOARD->Update();
    MOUSE->Update();
}


void InputManager::Clear()
{
    KEYBOARD->Clear();
    MOUSE->Clear();
    CUSTOM_INPUT->Clear();
}