//
// Created by captain on 3/30/21.
//

#include "game.h"
#include <functional>
#include <random>
#include <algorithm>
#include <iostream>


void game::init() {
    // create the maze before init it

    b = board{static_cast<float>(row) * w, static_cast<float>(col) * h};

    m = maze(2.0f);
    gen_maze();
    for (auto &wallz : walls) {
        for (auto &j : wallz) {
            for (auto &x : j) {
                m.add_wall(x);
            }
        }
    }
    m.init();
    p = player{glm::vec2{1, 1}, 0.1f};
    im = impostor{glm::vec2{0, 0}, 0.1f};

}


void game::draw(glm::mat4 VP) const {
    b.draw(VP);
    m.draw(VP);
    if (impostor_active) {
        im.draw(VP);
    }
    p.draw(VP);
}

void game::get_input(const int *keys) {

    if (keys[0]) { // left
        p.position.x -= p.speed;
        for (auto& x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                std::cout << x.start.x << " " << x.start.y << std::endl;
                std::cout << x.end.x << " " << x.end.y << std::endl;
                std::cout << std::endl;
                p.position.x += p.speed;
            }
        }
        p.orientation = false;
    }
    if (keys[1]) { // right
        p.position.x += p.speed;
        for (auto& x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                std::cout << x.start.x << " " << x.start.y << std::endl;
                std::cout << x.end.x << " " << x.end.y << std::endl;
                std::cout << std::endl;
                p.position.x -= p.speed;
            }
        }
        p.orientation = true;
    }
    if (keys[2]) { // up
        p.position.y += p.speed;
        for (auto& x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                std::cout << x.start.x << " " << x.start.y << std::endl;
                std::cout << x.end.x << " " << x.end.y << std::endl;
                std::cout << std::endl;
                p.position.y -= p.speed;
            }
        }
    }
    if (keys[3]) { // down
        p.position.y -= p.speed;
        for (auto& x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                std::cout << x.start.x << " " << x.start.y << std::endl;
                std::cout << x.end.x << " " << x.end.y << std::endl;
                std::cout << std::endl;

                p.position.y += p.speed;
            }
        }
    }
}


void game::gen_maze() {
    using namespace std;
    vector<vector<int>> vis(row, vector<int>(col, 0));
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    auto in = [&](int x, int y) {
        return x >= 0 && x < row && y >= 0 && y < col;
    };
    function<void(int, int, int, int)> dfs = [&](int x, int y, int px, int py) {
        vector<int> v{0, 1, 2, 3};
        std::cout << x << " " << y << std::endl;
        std::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
        vis[x][y] = 1;
        for (auto i:v) {
            if (in(x + dx[i], y + dy[i]) && !vis[x + dx[i]][y + dy[i]]) {
                dfs(x + dx[i], y + dy[i], x, y);
            } else if (!in(px, py) or x + dx[i] != px or y + dy[i] != py) {
                if (dx[i] == 0) {
                    auto d = dy[i] == 1 ? 1 : 0;
                    walls[x][y].emplace_back(glm::vec2{w * x, h * (y + d)},
                                             glm::vec2{w * (x + 1), h * (y + d)});
                } else {
                    auto d = dx[i] == 1 ? 1 : 0;
                    walls[x][y].emplace_back(glm::vec2{w * (x + d), h * (y)},
                                             glm::vec2{w * (x + d), h * (y + 1)});
                }
                if (in(x + dx[i], y + dy[i])) {
                    if (dx[i] == 0) {
                        auto d = dy[i] == 1 ? 1 : 0;
                        walls[x][y + dy[i]].emplace_back(glm::vec2{w * x, h * (y + d)},
                                                         glm::vec2{w * (x + 1), h * (y + d)});

                    } else {
                        auto d = dx[i] == 1 ? 1 : 0;
                        walls[x + dx[i]][y].emplace_back(glm::vec2{w * (x + d), h * (y)},
                                                         glm::vec2{w * (x + d), h * (y + 1)});
                    }
                }
            }
        }
    };
    dfs(0, 0, -1, -1);
}

void game::gen_items() {

}

void game::gen_tasks() {

}
