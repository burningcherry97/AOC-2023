#include <fstream>
#include <iostream>
#include <map>
#include <set>
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

struct Node {
    bool enclosed;
    bool inspected;

    Node(bool encl, bool insp) {
        enclosed = encl;
        inspected = insp;
    }

    Node() {
        enclosed = true;
        inspected = false;
    }
};

void fill(std::vector<std::vector<Node>>& graph, int x, int y) {
    graph[y][x] = {false, true};
    if (x > 0) {
        if (!graph[y][x-1].inspected)
            fill(graph,x-1,y);
    }
    if (x < graph[y].size() - 1) {
        if (!graph[y][x+1].inspected)
            fill(graph,x+1,y);
    }
    if (y > 0) {
        if (!graph[y-1][x].inspected)
            fill(graph,x,y-1);
    }
    if (y < graph.size() - 1) {
        if (!graph[y+1][x].inspected)
            fill(graph,x,y+1);
    }
}

int main(int argc, char** argv) {
    using namespace std;

    vector<vector<char>> scheme;
    scheme.push_back(vector<char>());
    int start_x = 0, start_y = 0;

    fstream in{"../P1/input.txt"};
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

    vector<pair<int,int>> path1;
    vector<pair<int,int>> path2;
    int path_1_x = start_x;
    int path_1_y = start_y;
    path1.push_back({path_1_x, path_1_y});
    int path_2_x = start_x;
    int path_2_y = start_y;
    path2.push_back({path_2_x, path_2_y});
    // read from the actual input; can be generalized with little effort
    int path_1_direction = 3;
    int path_2_direction = 0;
    
    for (int i = 0; ; ++i) {

        advance(scheme, path_1_x, path_1_y, path_1_direction);
        advance(scheme, path_2_x, path_2_y, path_2_direction);
        path1.push_back({path_1_x, path_1_y});
        path2.push_back({path_2_x, path_2_y});
        if (path_1_x == path_2_x && path_1_y == path_2_y) {
            // cout << i + 1;
            break;
        }
    }

    int X = scheme.front().size();
    int Y = scheme.size();

    // double density graph, representing both spots on the map 
    // and the middle points between them, allowing the 
    // "sticking" between pipes
    auto graph = vector<vector<Node>>(Y*2+1,vector<Node>(X*2+1));

    graph[start_y*2+1][start_x*2+1] = {false, true};
    for (int i = 1; i < path1.size(); ++i) {
        graph[path1[i].second*2+1][path1[i].first*2+1] = {false, true};
        graph[path2[i].second*2+1][path2[i].first*2+1] = {false, true};
        graph[path1[i].second+path1[i-1].second+1][path1[i].first+path1[i-1].first+1] = {false, true};
        graph[path2[i].second+path2[i-1].second+1][path2[i].first+path2[i-1].first+1] = {false, true};
    }

    graph[0][0] = {false, true};

    fill(graph,0,0);

    int res = 0;
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            // search only through the nodes that represent spots on the original map
            if (graph[i*2+1][j*2+1].enclosed) {
                ++res;
            }
        }
    }

    cout << res; // 357

    return 0;
}