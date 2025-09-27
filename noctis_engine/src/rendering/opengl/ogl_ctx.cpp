#include <rendering/opengl/ogl_ctx.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Noctis
{

OpenGLCtx::OpenGLCtx() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load OpenGL functions." << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(OpenGLDbgMessCallback, nullptr);
}

void OpenGLCtx::clearScreen() {
    glClearColor(clearScreenCol_.r, clearScreenCol_.g, clearScreenCol_.b, clearScreenCol_.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLCtx::OpenGLDbgMessCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam
) {
    if (severity == GL_DEBUG_SEVERITY_LOW)
        std::cerr << "OGL Info: " << message << std::endl;
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM)
        std::cerr << "OGL Warn: " << message << std::endl;
    else if (severity == GL_DEBUG_SEVERITY_HIGH)
        std::cerr << "OGL Error: " << message << std::endl;
}

} // namespace Noctis
