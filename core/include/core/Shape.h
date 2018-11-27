//
// Created by Rafik on 13.11.2018.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

#include <core/Mesh.h>
#include <core/Shader.h>

namespace core {

    class Shape {
    protected:
        glm::vec3 m_Position;
        glm::vec3 m_Color;
        glm::vec2 m_Velocity;
        bool m_IsSolid;
        Mesh *m_Mesh;

    protected:
        Shape(glm::vec3 position, glm::vec3 color, glm::vec2 velocity, bool isSolid)
                : m_Position(position), m_Color(color), m_Velocity(velocity), m_IsSolid(isSolid), m_Mesh(nullptr) {};
    public:
        virtual ~Shape() { delete m_Mesh; };
        virtual void Draw( Shader &shader) = 0;

        virtual void changePosition(glm::vec3 position) = 0;
        virtual void changeColor(glm::vec3 color) = 0;
        inline glm::vec2 GetVelocity() const { return m_Velocity; };
        inline glm::vec3 GetPosition() const { return m_Position; };
        inline bool GetIsSolid() const { return m_IsSolid; };
    };

}
#endif //SHAPE_H
