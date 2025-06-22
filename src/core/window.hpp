#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window
{
public:
    Window(int width, int height, const std::string &title);

    bool ShouldClose() const;

    void PostRender() const;

    GLFWwindow* GetWindow() const;

private:
    GLFWwindow* m_glfwWindow;

    static void GLFWErrorCallback(int code, const char *desc);
};
