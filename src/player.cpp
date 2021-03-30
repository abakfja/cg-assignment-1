//
// Created by captain on 3/30/21.
//

#include <player.h>

player::player(glm::vec2 _position, float _speed) : bean(_position, _speed, "../res/blue.txt") {
    init();
}

impostor::impostor(glm::vec2 _position, float _speed) : bean(_position, _speed, "../res/red.txt") {
    init();
}