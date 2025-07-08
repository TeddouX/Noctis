#include "window.hpp"


Window::Window(int width, int height, const std::string &title)
{
    LOG_INFO("Creating window.")

    glfwSetErrorCallback(Window::GLFWErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_glfwWindow = glfwCreateWindow(
        width, 
        height, 
        title.c_str(), 
        NULL, 
        NULL
    );

    if (this->m_glfwWindow == NULL)
	{
		LOG_ERR("Failed to create GLFW window. Exiting now...")
		glfwTerminate();
		exit(-1);
	}

    glfwSetFramebufferSizeCallback(this->m_glfwWindow, Window::GLFWWindowResizeCallback);
    glfwMakeContextCurrent(this->m_glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERR("Failed to initialize GLAD. Exiting now...")
		exit(-1);
	}

}


Window::~Window()
{   
    LOG_INFO("Destroying window.")

	glfwTerminate();
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


void Window::GLFWErrorCallback(int code, const char *desc)
{
    LOG_ERR("glfw error: " + std::string(desc))
}


void Window::GLFWWindowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
