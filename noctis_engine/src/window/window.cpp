#include <window/window.hpp>
#include <iostream>

namespace Noctis
{
   
Window::Window(int width, int height, const std::string &title) {
    glfwSetErrorCallback(Window::GLFWErrorCallback);
    glfwInit();
    // Opengl 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindow_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!glfwWindow_) {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwSetWindowUserPointer(glfwWindow_, this);
    glfwMakeContextCurrent(glfwWindow_);
}

void Window::GLFWErrorCallback(int code, const char *desc)
{
    std::cerr << "glfw error: " << desc << std::endl;
}

} // namespace Noctis
