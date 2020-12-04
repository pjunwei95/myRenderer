#pragma once
#include "array.h"

struct VertexBufferElement
{
    GLuint shaderProgram;
    const char* attribute;
    uint32_t type;
    uint32_t count;
    bool normalized;
    static uint32_t GetSizeOfType(uint32_t type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        }
        return 0;
    }
};

class VertexBufferFormat
{
private:
    Array<VertexBufferElement> m_Elements;
    uint32_t m_Stride;
public:
    VertexBufferFormat()
        :m_Stride{ 0 }
    {}

    //template<typename T>
    //void Push(uint32_t count)
    //{
    //    assert(false);
    //}

    void Push(GLuint shaderProgram, const char* attributeName, uint32_t count)
    {
        m_Elements.pushBack({ shaderProgram, attributeName, GL_FLOAT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    //template<>
    //void Push<float>(uint32_t count)
    //{
    //    m_Elements.pushBack({ GL_FLOAT, count, GL_FALSE });
    //    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    //}


    //template<typename T>
    //void Push(uint32_t count)
    //{
    //    m_Elements.pushBack({GL_FLOAT, count, GL_FALSE});
    //    //m_Stride += count * sizeof(GL_FLOAT);
    //    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    //}

    Array<VertexBufferElement> const& GetElements() const { return m_Elements; }
    inline uint32_t GetStride() const { return m_Stride; }

};
