#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, char** argv) {
    using namespace std;

    vector<vector<char>> scheme;
    vector<pair<int,int>> galaxies;
    long long int res = 0;

    fstream in{"../P1/input.txt"};
    string line;
    while (!in.eof()) {
        getline(in, line);
        scheme.push_back(vector<char>());
        for (char c : line) {
            scheme.back().push_back(c);
            if (c == '#') {
                galaxies.push_back({scheme.back().size()-1,scheme.size()-1});
            }
        }
    }

    vector<int> empty_columns;
    for (int i = 0; i < scheme.front().size(); ++i) {
        if (all_of(scheme.begin(), scheme.end(), [=](vector<char>& line){ return line[i] == '.'; })) {
            empty_columns.push_back(i);
        }
    }
    vector<int> empty_rows;
    for (int i = 0; i < scheme.size(); ++i) {
        if (all_of(scheme[i].begin(), scheme[i].end(), [](char c){ return c == '.'; })) {
            empty_rows.push_back(i);
        }
    }

    for (int i = 0; i < galaxies.size() - 1; ++i) {
        for (int j = i; j < galaxies.size(); ++j) {
            auto galaxy_1 = galaxies[i];
            auto galaxy_2 = galaxies[j];
            int x1 = min(galaxy_1.first, galaxy_2.first);
            int x2 = max(galaxy_1.first, galaxy_2.first);
            int y1 = min(galaxy_1.second, galaxy_2.second);
            int y2 = max(galaxy_1.second, galaxy_2.second);
            int x = x2 - x1;
            int y = y2 - y1;
            for (int k : empty_columns) {
                if (k > x1 && k < x2)
                    x += 999999;
            }
            for (int k : empty_rows) {
                if (k > y1 && k < y2)
                    y += 999999;
            }
            res += x + y;
        }
    }

    cout << res; // 648458253817

    return 0;
}