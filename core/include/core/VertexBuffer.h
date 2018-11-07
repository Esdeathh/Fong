//
// Created by Rafik on 04.11.2018.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/glad.h>

class VertexBuffer
{
private:
    unsigned int m_ID;
public:
    VertexBuffer(unsigned int size, const void* data, GLenum usage = GL_STATIC_DRAW);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
};


#endif //VERTEXBUFFER_H
