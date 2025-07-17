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

    // All the glfw callbacks
    glfwSetFramebufferSizeCallback(this->m_glfwWindow, Window::GLFWWindowResizeCallback);
    glfwSetKeyCallback(this->m_glfwWindow, Window::GLFWInputCallback);
    glfwSetCursorPosCallback(this->m_glfwWindow, Window::GLFWCursorPosCallback);
    glfwSetMouseButtonCallback(this->m_glfwWindow, Window::GLFWMouseButtonCallback);

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
    // glEnable(GL_CULL_FACE);
}


Window::~Window()
{   
    LOG_INFO("Destroying window.")

	glfwTerminate();
}


void Window::PostRender()
{
    glfwSwapBuffers(this->m_glfwWindow);

    // Clear last combo
    this->m_lastCombo.reset();
    this->m_mouseDelta = Vec2(0);

    // Upate delta time
    double currentFrameTime = glfwGetTime();
	this->m_deltaTime = currentFrameTime - this->m_lastFrameTime;
	this->m_lastFrameTime = currentFrameTime;
}


void Window::SetCursorEnabled(bool enabled) const
{
    if (enabled)
        glfwSetInputMode(this->m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(this->m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Window::GLFWErrorCallback(int code, const char *desc)
{
    LOG_ERR("glfw error: " + std::string(desc))
}


void Window::GLFWWindowResizeCallback(GLFWwindow* glfwWindow, int width, int height)
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


void Window::GLFWCursorPosCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
{
    Window *window = (Window *)glfwGetWindowUserPointer(glfwWindow);
    
    Vec2 mousePos = Vec2((float)xpos, (float)ypos);
    window->m_mousePos = mousePos;
    window->m_mouseDelta = window->m_mousePos - window->m_lastMousePos;

    window->m_lastMousePos = mousePos; 
}


void Window::GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
{
    Window *window = (Window *)glfwGetWindowUserPointer(glfwWindow);
    
    if (action == GLFW_PRESS)
        window->m_mouseButtonsDown.insert(button);
    else if (action == GLFW_RELEASE)
        window->m_mouseButtonsDown.erase(button);
}
