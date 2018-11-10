//
// Created by Rafik on 04.11.2018.
//

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <glad/glad.h>

class IndexBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_Count;
public:
    IndexBuffer(unsigned int count, const void *data, GLenum usage = GL_STATIC_DRAW);
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const;
};


#endif //INDEXBUFFER_H
