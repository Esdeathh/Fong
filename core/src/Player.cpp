//
// Created by Esdeath on 26/11/2018.
//

#include <Player.h>
#include <core/Player.h>


Player::Player(glm::vec3 position, glm::vec3 color, glm::vec2 velocity, bool isSolid, glm::vec2 size):
    color(color), rectangle(position, color, velocity, isSolid, size) {
    //placeholder
}

void Player::Draw(Shader &shader) {
    rectangle.Draw(shader);
}

const glm::vec3 &Player::getColor() const {
    return color;
}

void Player::BindMesh() const {
    rectangle.BindMesh();
}

void Player::changePosition(glm::vec3 position) {
    rectangle.changePosition(position);
}


