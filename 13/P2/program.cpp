#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool likely_almost_mirrored(std::vector<int64_t>& scheme, int cutout) {
    std::vector<int64_t> diffs;
    for (int left = cutout, right = cutout + 1; left >= 0 && right < scheme.size(); --left, ++right) {
        diffs.push_back(std::abs(scheme[left] - scheme[right]));
    }
    if (std::count_if(diffs.begin(), diffs.end(), [](int64_t i){ return i != 0; }) == 1) {
        int64_t n = *(std::find_if(diffs.begin(), diffs.end(), [](int64_t i){ return i != 0; }));
        double nd = n;
        double nlogd = std::log2(nd);
        if (nlogd == (int) nlogd) {
            return true;
        }
    }
    return false;
}

bool almost_mirrored_columnwise(std::vector<std::vector<char>>& scheme, int cutout) {
    int almost_same_columns = 0;
    for (int left = cutout, right = cutout + 1; left >= 0 && right < scheme.front().size(); --left, ++right) {
        int different_characters = 0;
        for (int i = 0; i < scheme.size(); ++i) {
            if (scheme[i][left] != scheme[i][right]) {
                ++different_characters;
            }
        }
        if (different_characters == 1) {
            ++almost_same_columns;
        }
    }
    return almost_same_columns == 1;
}

bool almost_mirrored_rowwise(std::vector<std::vector<char>>& scheme, int cutout) {
    int almost_same_rows = 0;
    for (int left = cutout, right = cutout + 1; left >= 0 && right < scheme.size(); --left, ++right) {
        int different_characters = 0;
        for (int i = 0; i < scheme.front().size(); ++i) {
            if (scheme[left][i] != scheme[right][i]) {
                ++different_characters;
            }
        }
        if (different_characters == 1) {
            ++almost_same_rows;
        }
    }
    return almost_same_rows == 1;
}

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"../P1/input.txt"};
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
                if (likely_almost_mirrored(columns, i)) {
                    if (almost_mirrored_columnwise(scheme, i))
                        res += (i + 1);
                }
            }

            vector<int64_t> rows = vector<int64_t>(scheme.size(),0);
            for (int i = 0; i < scheme.size(); ++i) {
                for (int j = 0; j < scheme[i].size(); ++j) {
                    rows[i] += (scheme[i][j] == '#' ? 1 : 0) * pow(2,j);
                }
            }

            for (int i = 0; i < rows.size() - 1; ++i) {
                if (likely_almost_mirrored(rows, i)) {
                    if (almost_mirrored_rowwise(scheme, i))
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