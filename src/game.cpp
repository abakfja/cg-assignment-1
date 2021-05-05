//
// Created by captain on 3/30/21.
//

#include "game.h"
#include <functional>
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>


std::random_device rd;
std::mt19937 gen(rd());


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
    p = player{glm::vec2{w / 2, h / 2}, 0.2f};
    im = impostor{glm::vec2{(1.5) * w, (0.5) * h}, 0.1f};
    im_die_task = task(glm::vec2{(static_cast<float>(rand() % row) + 0.5f) * w,
                                 (static_cast<float>(rand() % col) + 0.5f) * h}, {255, 0, 0});
    release_task = task(glm::vec2{(static_cast<float>(rand() % row) + 0.5f) * w,
                                  (static_cast<float>(rand() % col) + 0.5f) * h}, {0, 0, 202});
}


void game::draw(glm::mat4 VP) const {
    b.draw(VP);
    m.draw(VP);
    if (im_die_task.active) {
        im_die_task.draw(VP);
    }
    if (release_task.active) {
        release_task.draw(VP);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (auto &x : obs[i][j]) {
                if (x.active) x.draw(VP);
            }
            for (auto &x: pup[i][j]) {
                if (x.active) x.draw(VP);
            }
        }
    }
    if (impostor_active) {
        im.draw(VP);
    }
    p.draw(VP);
}

void game::get_input(const int *keys) {
    if (keys[0]) { // left
        p.position.x -= p.speed;
        for (auto &x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                p.position.x += p.speed;
            }
        }
        p.orientation = false;
    }
    if (keys[1]) { // right
        p.position.x += p.speed;
        for (auto &x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                p.position.x -= p.speed;
            }
        }
        p.orientation = true;
    }
    if (keys[2]) { // up
        p.position.y += p.speed;
        for (auto &x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                p.position.y -= p.speed;
            }
        }
    }
    if (keys[3]) { // down
        p.position.y -= p.speed;
        for (auto &x: walls[player_b().first][player_b().second]) {
            if (collides(x)) {
                p.position.y += p.speed;
            }
        }
    }
    if (keys[4]) { // is_dark
        is_dark = !is_dark;
    }
    for (auto &x: obs[player_b().first][player_b().second]) {
        if (x.active && collides(x)) {
            score += x.score;
            x.active = false;
            std::cout << score << std::endl;
        }
    }
    for (auto &x: pup[player_b().first][player_b().second]) {
        if (x.active && collides(x)) {
            score += x.score;
            x.active = false;
            std::cout << score << std::endl;
        }
    }
    if (im_die_task.active && collides(im_die_task)) {
        im_die_task.active = false;
        impostor_active = false;
    }
    if (release_task.active && collides(release_task)) {
        release_task.active = false;
        gen_items();
    }
    if (impostor_active) {
        move_impostor();
    }
    if (!is_dark) {
        score -= 0.05;
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
        std::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
        vis[x][y] = 1;
        for (auto i:v) {
            if (in(x + dx[i], y + dy[i]) && !vis[x + dx[i]][y + dy[i]]) {
                adj[x][y].emplace_back(x + dx[i], y + dy[i]);
                adj[x + dx[i]][y + dy[i]].emplace_back(x, y);
                dfs(x + dx[i], y + dy[i], x, y);
            } else if (!in(px, py) or x + dx[i] != px or y + dy[i] != py) {
                int d;
                if (dx[i] == 0) {
                    d = dy[i] == 1 ? 1 : 0;
                    walls[x][y].emplace_back(glm::vec2{w * x, h * (y + d)},
                                             glm::vec2{w * (x + 1), h * (y + d)});
                } else {
                    d = dx[i] == 1 ? 1 : 0;
                    walls[x][y].emplace_back(glm::vec2{w * (x + d), h * (y)},
                                             glm::vec2{w * (x + d), h * (y + 1)});
                }
                if (in(x + dx[i], y + dy[i])) {
                    if (dx[i] == 0) {
                        walls[x][y + dy[i]].emplace_back(glm::vec2{w * x, h * (y + d)},
                                                         glm::vec2{w * (x + 1), h * (y + d)});

                    } else {
                        walls[x + dx[i]][y].emplace_back(glm::vec2{w * (x + d), h * (y)},
                                                         glm::vec2{w * (x + d), h * (y + 1)});
                    }
                }
            }
        }
    };
    dfs(0, 0, -1, -1);
}

std::pair<int,int> game::get_next() {
    auto [rr, cc] = impostor_b();
    for (auto [r, c]: adj[rr][cc]) {
        std::vector<std::vector<int>> vis(row, std::vector<int>(col, false));
        std::function<bool(int,int)> dfs = [&](int x, int y) {
           vis[x][y] = true;
           bool res = std::make_pair(x,y) == player_b();
           for (auto [ur, uc]: adj[x][y]) {
               if (!vis[ur][uc]) {
                   res |= dfs(ur, uc);
               }
           }
           return res;
        };
        vis[rr][cc] = true;
        if (dfs(r,c)) {
            std::cout << r << " " << c << std::endl;
            return std::make_pair(r,c);
        }
    }
    assert(false);
}

void game::move_impostor() {
    if (player_b() == impostor_b()) {
//        std::cout << "here" << std::endl;
        impostor_highway = false;
        auto diff = p.position - im.position;
        if (std::abs(diff.x) < 0.02f && std::abs(diff.y) < 0.02f) {
            lost = true;
            return;
        }
        im.position += im.speed * (glm::normalize(diff));
        auto pos = impostor_b();
        auto center = glm::vec2((pos.first + 0.5) * w, (pos.second + 0.5)* h);
        diff = im.position - center;
        if (std::abs(diff.x) < 0.02f && std::abs(diff.y) < 0.02f) {
            impostor_highway = true;
        }
    } else {
//        std::cout << "now here" << std::endl;
        auto pos = impostor_b();
        auto center = glm::vec2((pos.first + 0.5) * w, (pos.second + 0.5)* h);
        auto diff = im.position - center;
        if (std::abs(diff.x) < 0.02f && std::abs(diff.y) < 0.02f) {
            impostor_highway = true;
        }
        if (impostor_highway) {
            auto nxt = get_next();
            center = glm::vec2((nxt.first + 0.5) * w, (nxt.second + 0.5)* h);
            diff = center - im.position;
            im.position += im.speed * glm::normalize(diff);
        } else {
            im.position -= 0.1f * (diff);
        }
    }
}

void game::gen_items() {
    std::uniform_real_distribution<GLfloat> dist(0.7f, 5.0f);
    std::uniform_int_distribution<unsigned> rrow(0, row - 1);
    std::uniform_int_distribution<unsigned> ccol(0, col - 1);
    for (int i = 0; i < 20; i++) {
        int x = rrow(gen), y = ccol(gen);
        auto pos = glm::vec2{(static_cast<float>(x)) * w + dist(gen),
                             (static_cast<float>(y)) * h + dist(gen)};
        obs[x][y].emplace_back(pos);
    }
    for (int i = 0; i < 20; i++) {
        int x = rrow(gen), y = ccol(gen);
        auto pos = glm::vec2{(static_cast<float>(x)) * w + dist(gen),
                             (static_cast<float>(y)) * h + dist(gen)};
        pup[x][y].emplace_back(pos);
    }
}
