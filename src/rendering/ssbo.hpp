#pragma once
#include <vector>
#include <glad/glad.h>


template <typename T>
class SSBO
{
public:
    SSBO(GLuint bindPoint = 0, GLenum usage = GL_DYNAMIC_DRAW);

    // Upload data to this SSBO
    void UploadData(std::vector<T> data);
    // Upload data to this SSBO
    void UploadData(const T& data);

    // Bind this SSBO
    void Bind();
    // Bind this SSBO to a point
    void BindToPoint(GLuint point);

    // Resize this SSBO, this doesn't conserve old data
    void Resize(size_t newSize);

private:
    GLuint m_id;
    GLuint m_bindPoint;
    GLenum m_usage;

    void BindToPoint();
};

#include "ssbo.inl"
