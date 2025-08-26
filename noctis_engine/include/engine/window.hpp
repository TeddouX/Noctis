#pragma once
#include <iostream>
#include <optional>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.hpp"
#include "engine.hpp"
#include "math/math.hpp"


#define OPENGL_DBG_LOW_ENABLE 1

namespace Noctis
{

/// @brief Used to describe key combos like Ctrl+S
class NOCTIS_API  KeyCombo
{
public:
    KeyCombo(int key, int modifiers) : m_key(key), m_modifiers(modifiers) {};

    bool Is(int key, std::initializer_list<int> modifiers);

private:
    int m_key;
    int m_modifiers;
};


class NOCTIS_API Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    bool ShouldClose() const { return glfwWindowShouldClose(this->m_glfwWindow); }
    void PostRender();

    void SetViewportSize(int w, int h);

    double GetDeltaTime() const { return this->m_deltaTime; }

    void SetResizable(bool val) { glfwSetWindowAttrib(this->m_glfwWindow, GLFW_RESIZABLE, val); }

    int GetWidth() const { return this->m_width; }
    int GetHeight() const { return this->m_height; }

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
    
    // Input handling could be moved to some kind of input system
    // but that's for later.
    std::unordered_set<int> m_keysDown;
    std::optional<KeyCombo> m_lastCombo;
    
    Vec2 m_mousePos;
    Vec2 m_lastMousePos;
    Vec2 m_mouseDelta;
    std::unordered_set<int> m_mouseButtonsDown;

    double m_deltaTime;
    double m_lastFrameTime;
    
    int m_width;
    int m_height;
    
    static void OpenGLDbgMessCallback(
        GLenum source, 
        GLenum type, 
        GLuint id, 
        GLenum severity,
        GLsizei length, 
        const GLchar* message, 
        const void* userParam
    );

    static void GLFWErrorCallback(int code, const char *desc);
    static void GLFWWindowResizeCallback(GLFWwindow *glfwWindow, int width, int height);
    static void GLFWInputCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
    static void GLFWCursorPosCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
    static void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
};

}
