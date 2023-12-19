#include <fstream>
#include <iostream>
#include <vector>

enum Direction { NORTH, EAST, SOUTH, WEST };

struct Node {
    std::vector<std::vector<int>> distance;

    Node() {
        for (int i = 0; i < 4; ++i) {
            distance.push_back(std::vector<int>());
            for (int j = 0; j < 3; ++j) {
                distance.back().push_back(2147483647);
            }
        }
    }
};

std::vector<std::vector<int>> scheme;
std::vector<std::vector<Node>> pathweb;
int X; int Y;

int get_x_forward(int x, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return x;
        break;

    case Direction::EAST:
        return x + 1;
        break;
    
    case Direction::SOUTH:
        return x;
        break;
    
    case Direction::WEST:
        return x - 1;
        break;
    
    default:
        return -1;
        break;
    }
}

int get_y_forward(int y, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return y - 1;
        break;

    case Direction::EAST:
        return y;
        break;
    
    case Direction::SOUTH:
        return y + 1;
        break;
    
    case Direction::WEST:
        return y;
        break;
    
    default:
        return -1;
        break;
    }
}

int get_x_right(int x, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return x + 1;
        break;

    case Direction::EAST:
        return x;
        break;
    
    case Direction::SOUTH:
        return x - 1;
        break;
    
    case Direction::WEST:
        return x;
        break;
    
    default:
        return -1;
        break;
    }
}

int get_y_right(int y, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return y;
        break;

    case Direction::EAST:
        return y + 1;
        break;
    
    case Direction::SOUTH:
        return y;
        break;
    
    case Direction::WEST:
        return y - 1;
        break;
    
    default:
        return -1;
        break;
    }
}

int get_x_left(int x, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return x - 1;
        break;

    case Direction::EAST:
        return x;
        break;
    
    case Direction::SOUTH:
        return x + 1;
        break;
    
    case Direction::WEST:
        return x;
        break;
    
    default:
        return -1;
        break;
    }
}

int get_y_left(int y, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return y;
        break;

    case Direction::EAST:
        return y - 1;
        break;
    
    case Direction::SOUTH:
        return y;
        break;
    
    case Direction::WEST:
        return y + 1;
        break;
    
    default:
        return -1;
        break;
    }
}

bool can_move_forward(int y, int x, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return y > 0;
        break;

    case Direction::EAST:
        return x < X - 1;
        break;
    
    case Direction::SOUTH:
        return y < Y - 1;
        break;
    
    case Direction::WEST:
        return x > 0;
        break;
    
    default:
        return false;
        break;
    }
}

bool can_move_right(int y, int x, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return x < X - 1;
        break;

    case Direction::EAST:
        return y < Y - 1;
        break;
    
    case Direction::SOUTH:
        return x > 0;
        break;
    
    case Direction::WEST:
        return y > 0;
        break;
    
    default:
        return false;
        break;
    }
}

bool can_move_left(int y, int x, Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return x > 0;
        break;

    case Direction::EAST:
        return y > 0;
        break;
    
    case Direction::SOUTH:
        return x < X - 1;
        break;
    
    case Direction::WEST:
        return y < Y - 1;
        break;
    
    default:
        return false;
        break;
    }
}

Direction get_right(Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return Direction::EAST;
        break;

    case Direction::EAST:
        return Direction::SOUTH;
        break;
    
    case Direction::SOUTH:
        return Direction::WEST;
        break;
    
    case Direction::WEST:
        return Direction::NORTH;
        break;
    
    default:
        return Direction::EAST;
        break;
    }
}

Direction get_left(Direction direction) {
    switch (direction)
    {
    case Direction::NORTH:
        return Direction::WEST;
        break;

    case Direction::EAST:
        return Direction::NORTH;
        break;
    
    case Direction::SOUTH:
        return Direction::EAST;
        break;
    
    case Direction::WEST:
        return Direction::SOUTH;
        break;
    
    default:
        return Direction::EAST;
        break;
    }
}

void step(int y, int x, Direction direction, int part_distance, int total_distance) {
    // mark as better distance on paths that are just as or more restrictive
    bool improved = false;
    for (int i = 0; i <= 3 - part_distance; ++i) {
        if (total_distance < pathweb[y][x].distance[direction][i]) {
            pathweb[y][x].distance[direction][i] = total_distance;
            improved = true;
        }
    }
    if (!improved) {
        return;
    }
    if (can_move_forward(y, x, direction)) {
        if (part_distance < 3) {
            step(get_y_forward(y, direction), get_x_forward(x, direction), 
                 direction, part_distance + 1, total_distance + scheme[y][x]);
        }
    }
    if (can_move_right(y, x, direction)) {
        step(get_y_right(y, direction), get_x_right(x, direction), 
                 get_right(direction), 1, total_distance + scheme[y][x]);
    }
    if (can_move_left(y, x, direction)) {
        step(get_y_left(y, direction), get_x_left(x, direction), 
                 get_left(direction), 1, total_distance + scheme[y][x]);
    }
}

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"input.txt"};
    // vector<vector<int>> scheme;
    scheme.push_back(vector<int>());

    while (!in.eof()) {
        char c = in.get();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            scheme.push_back(vector<int>());
        } else {
            scheme.back().push_back(c - '0');
        }
    }
    X = scheme.front().size();
    Y = scheme.size();

    // vector<vector<Node>> pathweb;
    for (int i = 0; i < Y; ++i) {
        pathweb.push_back(vector<Node>(X));
    }

    step(0, 1, Direction::EAST, 1, 0);
    // step(1, 0, Direction::SOUTH, 1, 0);

    int res = 2147483647;
    for (int i = 0; i < 4; ++i) {
        res = min(res, pathweb.back().back().distance[i][0]);
    }

    res += scheme.back().back();

    cout << res;

    return 0;
}