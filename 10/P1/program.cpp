#include <fstream>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

std::map<std::tuple<char,int>,std::tuple<int,int,int>> transitions = {
    {{'|',0},{0,-1,0}},
    {{'|',2},{0,1,2}},
    {{'-',1},{1,0,1}},
    {{'-',3},{-1,0,3}},
    {{'L',2},{1,0,1}},
    {{'L',3},{0,-1,0}},
    {{'J',2},{-1,0,3}},
    {{'J',1},{0,-1,0}},
    {{'7',1},{0,1,2}},
    {{'7',0},{-1,0,3}},
    {{'F',0},{1,0,1}},
    {{'F',3},{0,1,2}}
};

void advance(std::vector<std::vector<char>>& scheme, int& x, int& y, int& dir) {
    auto t = transitions[{scheme[y][x],dir}];
    x += std::get<0>(t);
    y += std::get<1>(t);
    dir = std::get<2>(t);
}

int main(int argc, char** argv) {
    using namespace std;

    vector<vector<char>> scheme;
    scheme.push_back(vector<char>());
    int start_x = 0, start_y = 0;

    fstream in{"input.txt"};
    while (!in.eof()) {
        char c = in.get();
        if (c == EOF) {
            break;
        } else if (c == '\n') {
            scheme.push_back(vector<char>());
        } else {
            scheme.back().push_back(c);
            if (c == 'S') {
                c = 'F';
                start_x = scheme.back().size() - 1;
                start_y = scheme.size() - 1;
                scheme.back().back() = 'F';
            }
        }
    }

    int path_1_x = start_x;
    int path_1_y = start_y;
    int path_2_x = start_x;
    int path_2_y = start_y;
    // read from the actual input; can be generalized with little effort
    int path_1_direction = 3;
    int path_2_direction = 0;
    
    for (int i = 0; ; ++i) {
        advance(scheme, path_1_x, path_1_y, path_1_direction);
        advance(scheme, path_2_x, path_2_y, path_2_direction);
        if (path_1_x == path_2_x && path_1_y == path_2_y) {
            cout << i + 1; // 6931
            break;
        }
    }

    return 0;
}