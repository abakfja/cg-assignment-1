//
// Created by captain on 3/30/21.
//

#ifndef CG_ASSIGNMENT_PLAYER_H
#define CG_ASSIGNMENT_PLAYER_H

#include <bean.h>

struct player : public bean {
    player() = default;

    player(glm::vec2 _position, float _speed);
};

struct impostor : public bean {

    impostor() = default;

    impostor(glm::vec2 _position, float _speed);
};


#endif //CG_ASSIGNMENT_PLAYER_H
