// EXTREMELY unoptimized (need to implement a priority_queue solution instead of a set) but it yields correct solutions

#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

enum Direction { RIGHT, DOWN, LEFT, UP };

Direction get_left(Direction d) {
    switch (d)
    {
    case RIGHT:
        return UP;
    case DOWN:
        return RIGHT;
    case LEFT:
        return DOWN;
    case UP:
        return LEFT;
    }
    throw "bad direction: get_left";
}

Direction get_right(Direction d) {
    switch (d)
    {
    case RIGHT:
        return DOWN;
    case DOWN:
        return LEFT;
    case LEFT:
        return UP;
    case UP:
        return RIGHT;
    }
    throw "bad direction: get_right";
}

struct Cell_state {
    int cost;
    int distance;
    int direction;
    int path_length;
    Cell_state* left;
    Cell_state* forward;
    Cell_state* right;

    Cell_state(int c) {
        cost = c;
    }
};

Cell_state* get_left(vector<vector<vector<vector<Cell_state>>>>& grid, int y, int x, int direction) {
    if (direction == 0) {
        if (y > 0) {
            return &grid[y-1][x][3][0];
        } else return nullptr;
    }
    if (direction == 1) {
        if (x < grid.front().size() - 1) {
            return &grid[y][x+1][0][0];
        } else return nullptr;
    }
    if (direction == 2) {
        if (y < grid.size() - 1) {
            return &grid[y+1][x][1][0];
        } else return nullptr;
    }
    if (direction == 3) {
        if (x > 0) {
            return &grid[y][x-1][2][0];
        } else return nullptr;
    }
    return nullptr;
}

Cell_state* get_forward(vector<vector<vector<vector<Cell_state>>>>& grid, int y, int x, int direction, int path_length) {
    if (path_length == 2) {
        return nullptr;
    }
    if (direction == 3) {
        if (y > 0) {
            return &grid[y-1][x][3][path_length + 1];
        } else return nullptr;
    }
    if (direction == 0) {
        if (x < grid.front().size() - 1) {
            return &grid[y][x+1][0][path_length + 1];
        } else return nullptr;
    }
    if (direction == 1) {
        if (y < grid.size() - 1) {
            return &grid[y+1][x][1][path_length + 1];
        } else return nullptr;
    }
    if (direction == 2) {
        if (x > 0) {
            return &grid[y][x-1][2][path_length + 1];
        } else return nullptr;
    }
    return nullptr;
}

Cell_state* get_right(vector<vector<vector<vector<Cell_state>>>>& grid, int y, int x, int direction) {
    if (direction == 2) {
        if (y > 0) {
            return &grid[y-1][x][3][0];
        } else return nullptr;
    }
    if (direction == 3) {
        if (x < grid.front().size() - 1) {
            return &grid[y][x+1][0][0];
        } else return nullptr;
    }
    if (direction == 0) {
        if (y < grid.size() - 1) {
            return &grid[y+1][x][1][0];
        } else return nullptr;
    }
    if (direction == 1) {
        if (x > 0) {
            return &grid[y][x-1][2][0];
        } else return nullptr;
    }
    return nullptr;
}

int main(int argc, char** argv) {
    // cout << "Hello!";

    ifstream in{"input.txt"};
    char c;
    vector<vector<vector<vector<Cell_state>>>> grid; // Y, X, direction, path length
    grid.push_back(vector<vector<vector<Cell_state>>>());
    while ((c = in.get()) != EOF) {
        if (c == '\n') {
            grid.push_back(vector<vector<vector<Cell_state>>>());
        } else {
            grid.back().push_back(vector<vector<Cell_state>>());
            for (int i = 0; i < 4; ++i) {
                grid.back().back().push_back(vector<Cell_state>());
                for (int j = 0; j < 3; ++j) {
                    grid.back().back().back().push_back(Cell_state(c - '0'));
                }
            }
        }
    }
    in.close();

    const int SIZE_X = grid.front().size();
    const int SIZE_Y = grid.size();
    
    set<Cell_state*> Q;

    for (int y = 0; y < SIZE_Y; ++y) {
        for (int x = 0; x < SIZE_X; ++x) {
            for (int direction = 0; direction < 4; ++direction) {
                for (int path_length = 0; path_length < 3; ++path_length) {
                    Cell_state* cs = &grid[y][x][direction][path_length];
                    cs->distance = INT32_MAX / 2;
                    cs->direction = direction;
                    cs->path_length = path_length;
                    cs->left = get_left(grid, y, x, direction);
                    cs->forward = get_forward(grid, y, x, direction, path_length);
                    cs->right = get_right(grid, y, x, direction);
                    Q.insert(cs);
                }
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[0][0][i][j].distance = 0;
        }
    }

    while (!Q.empty()) {
        if (Q.size() % 1000 == 0) cout << Q.size() << endl;
        Cell_state* u = *Q.begin();
        for (Cell_state* i : Q) {
            if (i->distance < u->distance) {
                u = i;
            }
        }
        Q.erase(u);

        if (u->left != nullptr) {
            int alt = u->distance + u->left->cost;
            if (alt < u->left->distance) {
                u->left->distance = alt;
            }
        }

        if (u->forward != nullptr) {
            int alt = u->distance + u->forward->cost;
            if (alt < u->forward->distance) {
                u->forward->distance = alt;
            }
        }

        if (u->right != nullptr) {
            int alt = u->distance + u->right->cost;
            if (alt < u->right->distance) {
                u->right->distance = alt;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << grid.back().back()[i][j].distance << endl;
        }
    }

    return 0;
}

