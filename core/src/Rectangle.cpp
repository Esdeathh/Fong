//
// Created by Rafik on 13.11.2018.
//

#include <core/Rectangle.h>
#include <glm/gtc/matrix_transform.hpp>

namespace core {


    Rectangle::Rectangle(glm::vec3 position, glm::vec2 velocity, bool isSolid, glm::vec2 size, std::string texturePath)
            : Shape(position, glm::vec3(), velocity, isSolid), m_Size(size) {

        std::vector<VertexPT> vertices = {
                {glm::vec3(size.x, size.y, 0.0f),   glm::vec2(1.0f, 1.0f)}, // Prawy górny
                {glm::vec3(size.x, -size.y, 0.0f),  glm::vec2(1.0f, 0.0f)}, // Prawy dolny
                {glm::vec3(-size.x, -size.y, 0.0f), glm::vec2(0.0f, 0.0f)}, // Lewy dolny
                {glm::vec3(-size.x, size.y, 0.0f),  glm::vec2(0.0f, 1.0f)}  // Lewy górny
        };

        std::vector<unsigned int> indices = {
                0, 1, 3,    // Pierwszy trójkąt
                1, 2, 3     // Drugi trójkąt
        };

        m_Mesh = new Mesh(vertices, indices, new Texture(texturePath, true));
    }

    Rectangle::Rectangle(glm::vec3 position, glm::vec3 color, glm::vec2 velocity, bool isSolid, glm::vec2 size)
            : Shape(position, color, velocity, isSolid), m_Size(size) {

        std::vector<VertexPC> vertices = {
                {glm::vec3(size.x, size.y, 0.0f),   color}, // Prawy górny
                {glm::vec3(size.x, -size.y, 0.0f),  color}, // Prawy dolny
                {glm::vec3(-size.x, -size.y, 0.0f), color}, // Lewy dolny
                {glm::vec3(-size.x, size.y, 0.0f),  color}  // Lewy górny
        };

        std::vector<unsigned int> indices = {
                0, 1, 3,    // Pierwszy trójkąt
                1, 2, 3     // Drugi trójkąt
        };

        m_Mesh = new Mesh(vertices, indices);
    }

    void Rectangle::Draw(Shader& shader)
    {
        //shader.Bind();
        shader.SetUniformMat4("world", glm::translate(glm::mat4(1), m_Position));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Rectangle::BindMesh() const
    {
        m_Mesh->Bind();
    }

    void Rectangle::changePosition(glm::vec3 position) {
        m_Position = position;
    }

    void Rectangle::changeColor(glm::vec3 color) {

    }

}