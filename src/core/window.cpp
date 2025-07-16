#include "window.hpp"


bool KeyCombo::Is(int key, std::initializer_list<int> modifiers)
{
    int mods = 0;
    for (int i : modifiers)
        mods |= i;

    return key == this->m_key 
        && mods == this->m_modifiers;
}



Window::Window(int width, int height, const std::string &title)
{
    LOG_INFO("Creating window.")

    glfwSetErrorCallback(Window::GLFWErrorCallback);
    glfwInit();
    // Opengl 4.3
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
    glfwSetKeyCallback(this->m_glfwWindow, Window::GLFWInputCallback);
    // Make this window usable in static callback functions
    glfwSetWindowUserPointer(this->m_glfwWindow, this);
    glfwMakeContextCurrent(this->m_glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERR("Failed to initialize GLAD. Exiting now...")
        glfwTerminate();
		exit(-1);
	}

    glEnable(GL_DEPTH_TEST);
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


void Window::PollEvents() const
{
    glfwPollEvents();
}


void Window::PostRender()
{
    glfwSwapBuffers(this->m_glfwWindow);

    // Clear last combo
    this->m_lastCombo.reset();
}


void Window::GLFWErrorCallback(int code, const char *desc)
{
    LOG_ERR("glfw error: " + std::string(desc))
}


void Window::GLFWWindowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void Window::GLFWInputCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
    Window *window = (Window *)glfwGetWindowUserPointer(glfwWindow);

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        window->m_keysDown.insert(key);
        
        if (mods)
        {
            window->m_lastCombo = { key, mods };
        }
    }
    else if (action == GLFW_RELEASE)
        window->m_keysDown.erase(key);
}
