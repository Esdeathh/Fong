//
// Created by Rafik on 13.11.2018.
//

#include <core/Circle.h>
#include <glm/gtc/matrix_transform.hpp>

namespace core {

    Circle::Circle(glm::vec3 position, glm::vec2 velocity, bool isSolid, float radius, std::string texturePath)
            : Shape(position, glm::vec3(), velocity, isSolid), m_Radius(radius)
    {
        std::vector<VertexPT> vertices = {
                {glm::vec3(radius, radius, 0.0f),   glm::vec2(1.0f, 1.0f)}, // Prawy górny
                {glm::vec3(radius, -radius, 0.0f),  glm::vec2(1.0f, 0.0f)}, // Prawy dolny
                {glm::vec3(-radius, -radius, 0.0f), glm::vec2(0.0f, 0.0f)}, // Lewy dolny
                {glm::vec3(-radius, radius, 0.0f),  glm::vec2(0.0f, 1.0f)}  // Lewy górny
        };

        std::vector<unsigned int> indices = {
                0, 1, 3,    // Pierwszy trójkąt
                1, 2, 3     // Drugi trójkąt
        };

        m_Mesh = new Mesh(vertices, indices, new Texture(texturePath, true));
    }

    Circle::Circle(glm::vec3 position, glm::vec3 color, glm::vec2 velocity, bool isSolid, float radius)
            : Shape(position, color, velocity, isSolid), m_Radius(radius)
    {
        std::vector<VertexPC> vertices = {
                {glm::vec3(radius, radius, 0.0f),   m_Color}, // Prawy górny
                {glm::vec3(radius, -radius, 0.0f),  m_Color}, // Prawy dolny
                {glm::vec3(-radius, -radius, 0.0f), m_Color}, // Lewy dolny
                {glm::vec3(-radius, radius, 0.0f),  m_Color}  // Lewy górny
        };

        std::vector<unsigned int> indices = {
                0, 1, 3,    // Pierwszy trójkąt
                1, 2, 3     // Drugi trójkąt
        };

        m_Mesh = new Mesh(vertices, indices);
    }

    void Circle::Draw(Shader &shader)
    {
        shader.Bind();
        m_Mesh->Bind();
        shader.SetUniformMat4("world", glm::translate(glm::mat4(1), m_Position));
        shader.SetUniform3f("center", m_Position.x, m_Position.y, m_Position.z);
        shader.SetUniform1f("radius", m_Radius);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Circle::changeColor(glm::vec3 color) {

    }

    void Circle::changePosition(glm::vec3 position) {

    }

}
