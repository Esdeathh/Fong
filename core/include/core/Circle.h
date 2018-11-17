//
// Created by Rafik on 13.11.2018.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include <core/Shape.h>

namespace core {

    class Circle : public Shape {
    private:
        float m_Radius;
    public:
        Circle(glm::vec3 position, glm::vec2 velocity, bool isSolid, float radius, std::string texturePath);
        Circle(glm::vec3 position, glm::vec3 color, glm::vec2 velocity, bool isSolid, float radius);

        ~Circle() override = default;

        void Draw(Shader &shader) override;

        inline float GetRadius() const { return m_Radius; };
    };

}

#endif //CIRCLE_H
