//
// Created by Rafik on 09.11.2018.
//

#ifndef MESH_H
#define MESH_H

#include <core/VertexArray.h>
#include <core/Texture.h>

#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
    glm::vec3 m_Position;
    glm::vec3 m_Color;
    glm::vec2 m_TexCoord;
};

class Mesh
{
private:
    VertexArray *m_VAO;
    IndexBuffer *m_EBO;
    VertexBuffer *m_VBO;
    std::vector<Texture *> m_Textures;
public:
    Mesh(const std::vector<Vertex>& data, const std::vector<unsigned int>& indices, std::vector<Texture *>& textures);
    ~Mesh();

    void Bind() const;
    void Unbind() const;
};

#endif //MESH_H
