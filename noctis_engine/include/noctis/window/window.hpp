#pragma once
#include <string>
#include <GLFW/glfw3.h>

#include "../engine.hpp"

namespace Noctis
{
    
class NOCTIS_API Window {
public:
    Window(int width, int height, const std::string &title);

    void pollEvents() const { glfwPollEvents(); }
    void swapBuffers() const { glfwSwapBuffers(glfwWindow_); }
    bool shouldClose() const { return glfwWindowShouldClose(glfwWindow_); }
    double getTime() const { return glfwGetTime(); }

private:
    GLFWwindow *glfwWindow_;

    static void GLFWErrorCallback(int code, const char *desc);
};

} // namespace Noctis
