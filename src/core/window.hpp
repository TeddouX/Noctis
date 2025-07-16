#pragma once
#include <iostream>
#include <optional>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.hpp"


/// @brief Used to describe key combos like Ctrl+S
class KeyCombo
{
public:
    KeyCombo(int key, int modifiers) : m_key(key), m_modifiers(modifiers) {};

    bool Is(int key, std::initializer_list<int> modifiers);

private:
    int m_key;
    int m_modifiers;
};


class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    bool ShouldClose() const;
    void PollEvents() const;
    void PostRender();

    const std::unordered_set<int> &GetKeysDown() const { return this->m_keysDown; } 
    const std::optional<KeyCombo> &GetLastCombo() const { return this->m_lastCombo; } 

    inline GLFWwindow *GetWindow() const { return this->m_glfwWindow; };

protected:
    std::unordered_set<int> m_keysDown;
    std::optional<KeyCombo> m_lastCombo;
    
private:
    GLFWwindow *m_glfwWindow;

    static void GLFWErrorCallback(int code, const char *desc);
    static void GLFWWindowResizeCallback(GLFWwindow *window, int width, int height);
    static void GLFWInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
