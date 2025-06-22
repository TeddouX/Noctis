#include "window.hpp"


Window::Window(int width, int height, const std::string &title)
{
    glfwSetErrorCallback(Window::GLFWErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_glfwWindow = glfwCreateWindow(
        width, 
        height, 
        title.c_str(), 
        NULL, 
        NULL
    );

    glfwMakeContextCurrent(this->m_glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD. Exiting now..." << std::endl;
		exit(-1);
	}
}


bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(this->m_glfwWindow);
}


void Window::PostRender() const
{
    glfwPollEvents();
    glfwSwapBuffers(this->m_glfwWindow);
}


GLFWwindow* Window::GetWindow() const
{
    return this->m_glfwWindow;
}


void Window::GLFWErrorCallback(int code, const char *desc)
{
    std::cerr << "[ERROR]: glfw error: " + std::string(desc) << std::endl;
}
