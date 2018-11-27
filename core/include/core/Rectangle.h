//
// Created by Rafik on 13.11.2018.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <core/Shape.h>

namespace core {

    class Rectangle : public Shape
    {
    private:
        glm::vec2 m_Size;
    public:
        Rectangle(glm::vec3 position, glm::vec2 velocity, bool isSolid, glm::vec2 size, std::string texturePath);
        Rectangle(glm::vec3 position, glm::vec3 color, glm::vec2 velocity, bool isSolid, glm::vec2 size);
        ~Rectangle() override = default;

        void changePosition(glm::vec3 position) override;
        void changeColor(glm::vec3 color) override;
        void Draw(Shader& shader) override;
        void BindMesh() const;

        inline glm::vec2 GetSize() const { return m_Size; };
    };

}

#endif //RECTANGLE_H
