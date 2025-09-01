#pragma once
#include <vector>
#include <glad/glad.h>

namespace Noctis
{

/// @brief An SSBO is used to send large amounts of data to shaders
/// @tparam T The data type it sends to the shader
template <typename T>
class SSBO
{
public:
    SSBO(GLuint bindPoint = 0, GLenum usage = GL_DYNAMIC_DRAW);

    /// @brief Upload a vector of object through this SSBO. Use `SSBO::Resize()` if the vector's size changes.
    /// @param data The vector of objects
    void UploadData(std::vector<T> data);

    /// @brief Upload a single object to this SSBO
    /// @param data The object sent through this SSBO
    void UploadData(T data);

    /// @brief Upload raw data to the SSBO
    /// @param data Pointer to the data to upload.
    /// @param dataSize Size of the data in bytes.
    void UploadRaw(const void *data, size_t dataSize);  
    
    /// @brief Bind this SSBO to a binding point to later use it in a shader
    /// @param point The binding point
    void BindToPoint(GLuint point);

    /// @brief Resize this SSBO, doesn't conserve old data. 
    /// This should only be used when the data is sent through vectors
    /// @param newSize The new size of the vector
    void Resize(size_t newSize);

private:
    GLuint m_id;
    GLuint m_bindPoint;
    GLenum m_usage;

    void Bind();
    void BindToPoint();
};

}

#include "ssbo.inl"
