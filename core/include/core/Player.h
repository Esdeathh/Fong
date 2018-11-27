//
// Created by Esdeath on 26/11/2018.
//

#ifndef FONG_PLAYER_H
#define FONG_PLAYER_H

#include <core/Rectangle.h>

class Player {
public:
    Player(glm::vec3 position, glm::vec3 color, glm::vec2 velocity, bool isSolid, glm::vec2 size);
    void Draw(Shader& shader);
    const glm::vec3 &getColor() const;
    void BindMesh() const;
    void changePosition(glm::vec3 position);
private:
    glm::vec3 color;
    core::Rectangle rectangle;
};


#endif //FONG_PLAYER_H
