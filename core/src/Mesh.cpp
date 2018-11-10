//
// Created by Rafik on 09.11.2018.
//

#include <core/Mesh.h>

Mesh::Mesh(const std::vector<Vertex>& data, const std::vector<unsigned int>& indices, std::vector<Texture *>& textures)
    : m_Textures(textures)
{
    m_VAO = new VertexArray();
    m_VBO = new VertexBuffer(data.size() * sizeof(Vertex), data.data());
    m_EBO = new IndexBuffer(static_cast<unsigned int>(indices.size()), indices.data());

    VertexBufferLayout layout;
    layout.PushElement(3);
    layout.PushElement(3);
    layout.PushElement(2);

    m_VAO->BindIndexBuffer(*m_EBO);
    m_VAO->BindVertexBuffer(*m_VBO, layout);
}

Mesh::~Mesh()
{
    delete m_VAO;
    delete m_VBO;
    delete m_EBO;
    //Czy usuwać textury?
}

void Mesh::Bind() const
{
    m_VAO->Bind();
    for(int i = 0; i < m_Textures.size(); i++)
        m_Textures[i]->Bind(i);
}

void Mesh::Unbind() const
{
    m_VAO->Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}
