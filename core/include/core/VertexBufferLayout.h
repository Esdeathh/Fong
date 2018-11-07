//
// Created by Rafik on 04.11.2018.
//

#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <glad/glad.h>
#include <vector>

struct VertexBufferElement
{
    unsigned int size;
    unsigned int type;
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Attributes;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) {};
    ~VertexBufferLayout() = default;

    void PushElement(unsigned int count)
    {
        m_Attributes.push_back( {count, GL_FLOAT} );
        m_Stride += count * sizeof(float);
    }

    inline const std::vector<VertexBufferElement> GetAttributes() const& { return m_Attributes; };
    inline unsigned int GetStride() const { return m_Stride; };
};

#endif //VERTEXBUFFERLAYOUT_H
