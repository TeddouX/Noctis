#pragma once
#include <iostream>
#include <optional>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.hpp"
#include "math/math.hpp"


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

    inline bool ShouldClose() const { return glfwWindowShouldClose(this->m_glfwWindow); }
    void PollEvents() const { glfwPollEvents(); }
    void PostRender();

    const std::unordered_set<int> &GetKeysDown() const { return this->m_keysDown; } 
    const std::optional<KeyCombo> &GetLastCombo() const { return this->m_lastCombo; } 

    const Vec2 &GetMousePos() const { return this->m_mousePos; }
    const Vec2 &GetMouseDelta() const { return this->m_mouseDelta; }
    const std::unordered_set<int> &GetMouseButtonsDown() const { return this->m_mouseButtonsDown; }

    void SetCursorEnabled(bool enabled) const;
    bool IsCursorEnabled() const { return glfwGetInputMode(this->m_glfwWindow, GLFW_CURSOR) == GLFW_CURSOR_NORMAL; }

    inline GLFWwindow *GetWindow() const { return this->m_glfwWindow; };

private:
    GLFWwindow *m_glfwWindow;
    
    std::unordered_set<int> m_keysDown;
    std::optional<KeyCombo> m_lastCombo;
    
    Vec2 m_mousePos;
    Vec2 m_lastMousePos;
    Vec2 m_mouseDelta;
    std::unordered_set<int> m_mouseButtonsDown;
    
    static void GLFWErrorCallback(int code, const char *desc);
    static void GLFWWindowResizeCallback(GLFWwindow *glfwWindow, int width, int height);
    static void GLFWInputCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
    static void GLFWCursorPosCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
    static void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
};
