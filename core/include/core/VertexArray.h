//
// Created by Rafik on 04.11.2018.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>
#include <core/VertexBuffer.h>
#include <core/VertexBufferLayout.h>
#include <core/IndexBuffer.h>

class VertexArray
{
private:
    unsigned int m_ID;
public:
    VertexArray();
    ~VertexArray();
    void BindVertexBuffer(const VertexBuffer &VBO, const VertexBufferLayout &VBL);
    void BindIndexBuffer(const IndexBuffer &IBO);
    void Bind();
    void Unbind();
};


#endif //VERTEXARRAY_H
