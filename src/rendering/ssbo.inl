#include "ssbo.hpp"


template <typename T>
SSBO<T>::SSBO(GLuint bindPoint, GLenum usage)
    : m_bindPoint(bindPoint), m_usage(usage)
{
    glGenBuffers(1, &this->m_id);
}


template <typename T>
void SSBO<T>::UploadData(std::vector<T> data)
{
    this->Bind();

    glBufferData(
        GL_SHADER_STORAGE_BUFFER, 
        data.size() * sizeof(T), 
        data.data(), 
        this->m_usage
    );
}


template <typename T>
void SSBO<T>::UploadData(T data)
{
    this->Bind();

    glBufferData(
        GL_SHADER_STORAGE_BUFFER, 
        sizeof(T), 
        &data, 
        this->m_usage
    );
}


template <typename T>
void SSBO<T>::Bind()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->m_id);
}


template <typename T>
void SSBO<T>::BindToPoint(GLuint point)
{
    this->m_bindPoint = point;
    this->BindToPoint();
}


template <typename T>
void SSBO<T>::BindToPoint()
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->m_bindPoint, this->m_id);
}


template <typename T>
void SSBO<T>::Resize(size_t newSize)
{
    this->Bind();
    glBufferData(GL_SHADER_STORAGE_BUFFER, newSize, nullptr, this->m_usage);
}
