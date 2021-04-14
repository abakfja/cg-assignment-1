//
// Created by captain on 3/30/21.
//

#ifndef CG_ASSIGNMENT_GAME_H
#define CG_ASSIGNMENT_GAME_H

#include <player.h>
#include <board.h>
#include <item.h>
#include <vector>
#include <set>
#include <iostream>

/**
 * The maze and board would be spawned at 0, 0 to width, height
 * and impostor and player would also be spawned to that coordinate
 */
class game {
public:
    player p;
    impostor im;
    board b;
    maze m;
    task im_die_task;
    task release_task;


    bool is_dark = true;
    bool impostor_active = true;

    int score = 0;

    static constexpr int row = 10, col = 10;
    static constexpr float w = 6, h = 6;

    std::vector<std::pair<int,int>> adj[row][col];
    std::vector<wall> walls[row][col];
    std::vector<obstacle> obs[row][col];
    std::vector<powerup> pup[row][col];

    std::pair<int, int> player_b() const {
        return std::make_pair(std::floor(p.position.x / w), std::floor(p.position.y / h));
    };

    std::pair<int, int> impostor_b() const {
        return std::make_pair(std::floor(im.position.x / w), std::floor(im.position.y / h));
    };

    bool collides(wall wawa) {
        int t = 0;

        if (wawa.end.x == wawa.start.x) {
            auto a = std::max(wawa.end.y, wawa.start.y);
            auto aa = std::min(wawa.end.y, wawa.start.y);
            return p.left() <= wawa.end.x and p.right() >= wawa.end.x and p.top() >= aa and p.bottom() <= a;
        }
        auto a = std::max(wawa.end.x, wawa.start.x);
        auto aa = std::min(wawa.end.x, wawa.start.x);
        return p.top() >= wawa.end.y and p.bottom() <= wawa.end.y and p.right() >= aa and p.left() <= a;
    }

    bool collides(item it) {
        if (p.left() <= it.right() &&
                p.right() >= it.left() &&
                p.top() >= it.bottom() &&
                p.bottom() <= it.top()) {
            return true;
        }
        return false;
    }

    game() = default;

    void init();

    void gen_maze();

    void gen_items();

    void gen_tasks();

    void draw(glm::mat4 VP) const;

    void get_input(const int *keys);
};


#endif //CG_ASSIGNMENT_GAME_H
