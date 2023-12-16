#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <array>

struct Tile {
    char type;
    bool energized[4];
};

struct Coords {
    int x;
    int y;
};

struct Beam {
    Coords coords;
    // 0  -- right
    // 1  -- down
    // 2  -- up
    // 3  -- left
    // -1 -- to disappear
    int direction;
};

void advance_all(std::vector<std::vector<Tile>>& scheme, std::vector<Beam>& beams) {
    int size = beams.size();
    for (int i = 0; i < size; ++i) {
        Beam b = beams[i];
        // advance; mark to remove if out of bounds
        switch (b.direction)
        {
        case 0:
            ++b.coords.x;
            if (b.coords.x >= scheme.front().size()) {
                b.direction = -1;
            }
            break;
        
        case 1:
            ++b.coords.y;
            if (b.coords.y >= scheme.size()) {
                b.direction = -1;
            }
            break;
        
        case 2:
            --b.coords.x;
            if (b.coords.x < 0) {
                b.direction = -1;
            }
            break;

        case 3:
            --b.coords.y;
            if (b.coords.y < 0) {
                b.direction = -1;
            }
            break;
        
        default:
            break;
        }
        // mark to remove if already been there
        if (b.direction != -1) {
            if (scheme[b.coords.y][b.coords.x].energized[b.direction]) {
                b.direction = -1;
            }
        }
        // if not marked to remove, mark "been there"
        if (b.direction != -1) {
            scheme[b.coords.y][b.coords.x].energized[b.direction] = true;
        }
        // if not marked to remove, process the tile
        if (b.direction != -1) {
            switch (scheme[b.coords.y][b.coords.x].type)
            {
            case '|':
                if (b.direction == 0 || b.direction == 2) {
                    // turn clockwise;
                    b.direction = (b.direction + 1) %4;
                    beams.push_back({{b.coords.x,b.coords.y},(b.direction+2)%4});
                }
                break;
            
            case '-':
                if (b.direction == 1 || b.direction == 3) {
                    // turn clockwise;
                    b.direction = (b.direction + 1) %4;
                    beams.push_back({{b.coords.x,b.coords.y},(b.direction+2)%4});
                }
                break;

            case '\\':
                if (b.direction == 0 || b.direction == 2) {
                    // turn clockwise;
                    b.direction = (b.direction + 1) %4;
                } else {
                    // turn counter-clockwise
                    b.direction = (b.direction + 3) %4;
                }
                break;
            
            case '/':
                if (b.direction == 0 || b.direction == 2) {
                    // turn counter-clockwise
                    b.direction = (b.direction + 3) %4;
                } else {
                    // turn clockwise;
                    b.direction = (b.direction + 1) %4;
                }
                break;
            
            default:
                break;
            }
        }
        beams[i] = b;
    }
    beams.erase(remove_if(beams.begin(), 
                          beams.end(),
                          [](Beam& b){ return b.direction == -1; }),
                beams.end());
}

void test(std::vector<std::vector<Tile>>& scheme, int start_x, int start_y, int start_dir, int& acc) {
    for (auto& v : scheme) {
        for (Tile& t : v) {
            for (int i = 0; i < 4; ++i) {
                t.energized[i] = false;
            }
        }
    }

    std::vector<Beam> beams;
    beams.push_back({{start_x,start_y},start_dir});

    while (!beams.empty()) {
        advance_all(scheme, beams);
    }

    int res = 0;
    for (auto& v : scheme) {
        for (Tile& t : v) {
            for (int i = 0; i < 4; ++i) {
                if (t.energized[i]) {
                    ++res;
                    break;
                }
            }
        }
    }
    acc = std::max(acc, res);
}

int main(int argc, char** argv) {
    using namespace std;

    vector<vector<Tile>> scheme;
    scheme.push_back(vector<Tile>());
    vector<Beam> beams;

    fstream in{"../P1/input.txt"};
    while (!in.eof()) {
        char c = in.get();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            scheme.push_back(vector<Tile>());
        } else {
            scheme.back().push_back({c, false});
        }
    }

    int X = scheme.front().size() - 1;
    int Y = scheme.size() - 1;

    int res = 0;

    for (int i = 0; i < X; ++i) {
        test(scheme, i, -1, 1, res);
        test(scheme, i, Y, 3, res);
    }
    for (int i = 0; i < Y; ++i) {
        test(scheme, -1, i, 0, res);
        test(scheme, X, i, 2, res);
    }

    cout << res; // 8246

    return 0;
}