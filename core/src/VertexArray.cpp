//
// Created by Rafik on 04.11.2018.
//

#include <core/VertexArray.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::BindVertexBuffer(const VertexBuffer &VBO, const VertexBufferLayout &VBL)
{
    Bind();
    VBO.Bind();
    auto elements = VBL.GetAttributes();
    unsigned int m = 0;
    for(int i = 0; i < elements.size(); i++)
    {
        glVertexAttribPointer(i, elements[i].size, GL_FLOAT, GL_FALSE, VBL.GetStride(), (const void *)(m * sizeof(float)));
        glEnableVertexAttribArray(i);
        m += elements[i].size;
    }
}

void VertexArray::BindIndexBuffer(const IndexBuffer &IBO)
{
    Bind();
    IBO.Bind();
}

void VertexArray::Bind()
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}


