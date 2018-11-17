//
// Created by Rafik on 09.11.2018.
//

#include <core/Mesh.h>
#include <common/Debug.h>

Mesh::Mesh(const std::vector<VertexPC> &data, const std::vector<unsigned int>& indices)
    :  m_Texture(nullptr)
{
    m_VAO = new VertexArray();
    m_VBO = new VertexBuffer(data.size() * sizeof(VertexPC), data.data());
    m_EBO = new IndexBuffer(static_cast<unsigned int>(indices.size()), indices.data());

    VertexBufferLayout layout;
    layout.PushElement(3);
    layout.PushElement(3);

    m_VAO->BindIndexBuffer(*m_EBO);
    m_VAO->BindVertexBuffer(*m_VBO, layout);
    m_VAO->Unbind();
}

Mesh::Mesh(const std::vector<VertexPT>& data, const std::vector<unsigned int>& indices, Texture *textures)
    : m_Texture(textures)
{
    m_VAO = new VertexArray();
    m_VBO = new VertexBuffer(data.size() * sizeof(VertexPT), data.data());
    m_EBO = new IndexBuffer(static_cast<unsigned int>(indices.size()), indices.data());

    VertexBufferLayout layout;
    layout.PushElement(3);
    layout.PushElement(2);

    m_VAO->BindIndexBuffer(*m_EBO);
    m_VAO->BindVertexBuffer(*m_VBO, layout);
    m_VAO->Unbind();
}

Mesh::~Mesh()
{
    delete m_VAO;
    delete m_VBO;
    delete m_EBO;
    delete m_Texture;
}

void Mesh::Bind() const
{
    m_VAO->Bind();
    if(m_Texture)
        m_Texture->Bind();
}

void Mesh::Unbind() const
{
    m_VAO->Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}




