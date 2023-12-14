#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool mirrored(std::vector<int64_t>& scheme, int cutout) {
    for (int left = cutout, right = cutout + 1; left >= 0 && right < scheme.size(); --left, ++right) {
        if (scheme[left] != scheme[right]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"input.txt"};
    vector<vector<char>> scheme;
    string line;
    int res = 0;

    while (!in.eof()) {
        getline(in, line);
        if (line == "" || in.eof()) {
            vector<int64_t> columns = vector<int64_t>(scheme.front().size(),0);
            for (int i = 0; i < scheme.front().size(); ++i) {
                for (int j = 0; j < scheme.size(); ++j) {
                    columns[i] += (scheme[j][i] == '#' ? 1 : 0) * pow(2,j);
                }
            }

            for (int i = 0; i < columns.size() - 1; ++i) {
                if (mirrored(columns, i)) {
                    res += i + 1;
                }
            }

            vector<int64_t> rows = vector<int64_t>(scheme.size(),0);
            for (int i = 0; i < scheme.size(); ++i) {
                for (int j = 0; j < scheme[i].size(); ++j) {
                    rows[i] += (scheme[i][j] == '#' ? 1 : 0) * pow(2,j);
                }
            }

            for (int i = 0; i < rows.size() - 1; ++i) {
                if (mirrored(rows, i)) {
                    res += (i + 1) * 100;
                }
            }
            scheme.clear();
        } else {
            scheme.push_back(vector<char>());
            for (char c : line)
                scheme.back().push_back(c);
        }
    }

    cout << res;

    return 0;
}