#include "vertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    //glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer const& vb, VertexBufferFormat const& layout)
{
    Bind();
    vb.Bind();
    Array<VertexBufferElement> const&  elements = layout.GetElements();
    uint64_t offset = 0;
    for (uint32_t i = 0; i < elements.size(); ++i)
    {
        VertexBufferElement const& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, 
            element.normalized, layout.GetStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
