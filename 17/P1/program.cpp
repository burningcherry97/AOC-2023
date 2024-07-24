#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Coordinates {
    int y;
    int x;
    Coordinates operator+(const Coordinates& other) {
        Coordinates result = *this;
        result.x += other.x;
        result.y += other.y;
        return result;
    }
};

struct Node {
    Coordinates coordinates;
    Coordinates direction;
    int distance;
    int path_length;
};

int main(int argc, char** argv) {
    
    ifstream in{"input.txt"};
    vector<vector<int>> grid;
    grid.push_back(vector<int>());
    int c;
    while ((c = in.get()) != EOF) {
        if (c == '\n') {
            grid.push_back(vector<int>());
        } else {
            grid.back().push_back(c - '0');
        }
    }
    in.close();

    // Y, X, direction, path length
    vector<vector<array<array<int,4>,4>>> best(
        grid.size(),
        vector<array<array<int,4>,4>>(
            grid.front().size(),
            [] {
                array<array<int,4>,4> result;
                for (auto& direction_row : result) {
                    for (int& n : direction_row) {
                        n = INT32_MAX;
                    }
                }
                return result;
            } ()
        )
    );

    auto cmp = [](Node& n1, Node& n2) { return n1.distance > n2.distance; };
    priority_queue<Node, vector<Node>, decltype(cmp)> q(cmp);

    auto loss_at = [&](Coordinates coords) { return grid[coords.y][coords.x]; };
    auto not_out_of_bounds = [&](Coordinates coords) { return coords.x >= 0 && coords.y >= 0 && coords.x < grid.front().size() && coords.y < grid.size(); };
    auto get_left = [&](Coordinates direction) {
        if (direction.x != 0) {
            return Coordinates{-direction.x, 0};
        } else {
            return Coordinates{0, direction.y};
        }
    };
    auto get_right = [&](Coordinates direction) {
        if (direction.x != 0) {
            return Coordinates{direction.x, 0};
        } else {
            return Coordinates{0, -direction.y};
        }
    };
    auto dir_to_int = [&](Coordinates direction) {
        if (direction.x == 1)
            return 0;
        if (direction.y == 1)
            return 1;
        if (direction.x == -1)
            return 2;
        return 3;
    };

    Coordinates destination{grid.size() - 1, grid.front().size() - 1};

    auto push_if_better = [&](Node n) {
        if (n.distance < best[n.coordinates.y][n.coordinates.x][dir_to_int(n.direction)][n.path_length]) {
            best[n.coordinates.y][n.coordinates.x][dir_to_int(n.direction)][n.path_length] = n.distance;
            q.push(n);
        }
    };

    push_if_better({{0, 0}, {1, 0}, 0, 0});
    push_if_better({{0, 0}, {0, 1}, 0, 0});

    while (!q.empty()) {
        auto [pos, dir, dist, p_l] = q.top();

        if (pos.x == destination.x && pos.y == destination.y) {
            cout << dist << '\n';
            return 0;
        }

        q.pop();

        if (p_l < 3 && not_out_of_bounds(pos + dir) ) {
            push_if_better({pos + dir, dir, dist + loss_at(pos + dir), p_l + 1});
        }

        if (not_out_of_bounds(pos + get_left(dir))) {
            push_if_better({pos + get_left(dir), get_left(dir), dist + loss_at(pos + get_left(dir)), 1});
        }

        if (not_out_of_bounds(pos + get_right(dir))) {
            push_if_better({pos + get_right(dir), get_right(dir), dist + loss_at(pos + get_right(dir)), 1});
        }
    }

    return 0;
}