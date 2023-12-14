#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"input.txt"};
    vector<vector<char>> scheme;
    scheme.push_back(vector<char>());
    vector<pair<int,int>> rocks;
    int res = 0;

    while(!in.eof()) {
        char c = in.get();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            scheme.push_back(vector<char>());
        } else {
            scheme.back().push_back(c);
            if (c == 'O') {
                rocks.push_back({scheme.size()-1, scheme.back().size()-1});
            }
        }
    }

    for (bool changed = true; changed;) {
        changed = false;
        for (auto& p : rocks) {
            if (p.first > 0) {
                if (scheme[p.first-1][p.second] == '.') {
                    scheme[p.first][p.second] = '.';
                    --p.first;
                    scheme[p.first][p.second] = 'O';
                    changed = true;
                }
            }
        }
    }

    for (auto p : rocks) {
        res += scheme.size() - p.first;
    }

    cout << res; // 108641

    return 0;
}