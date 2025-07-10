#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.hpp"


class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    bool ShouldClose() const;
    void PostRender() const;

    inline GLFWwindow* GetWindow() const { return this->m_glfwWindow; };

private:
    GLFWwindow* m_glfwWindow;

    static void GLFWErrorCallback(int code, const char *desc);
    static void GLFWWindowResizeCallback(GLFWwindow* window, int width, int height);
};
