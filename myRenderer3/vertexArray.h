#pragma once
#include "vertexBuffer.h"
#include "vertexBufferFormat.h"

class VertexArray
{
private:
    uint32_t m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(VertexBuffer const& vb, VertexBufferFormat const& layout);

    void Bind() const;
    void Unbind() const;
};

