//
// Created by Rafik on 09.11.2018.
//

#ifndef MESH_H
#define MESH_H

#include <core/VertexArray.h>
#include <core/Texture.h>

#include <glm/glm.hpp>

#include <vector>

struct VertexPC
{
    glm::vec3 m_Position;
    glm::vec3 m_Color;
};

struct VertexPT
{
    glm::vec3 m_Position;
    glm::vec2 m_TexCoord;
};

class Mesh
{
private:
    VertexArray *m_VAO;
    IndexBuffer *m_EBO;
    VertexBuffer *m_VBO;
    Texture *m_Texture;
public:
    Mesh(const std::vector<VertexPC>& data, const std::vector<unsigned int>& indices);
    Mesh(const std::vector<VertexPT>& data, const std::vector<unsigned int>& indices, Texture *texture);
    ~Mesh();

    void Bind() const;
    void Unbind() const;
};

#endif //MESH_H
