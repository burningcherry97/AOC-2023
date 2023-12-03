#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

    fstream in{"../P1/input.txt"};
    vector<vector<char>> scheme;
    vector<int> part_numbers;
    vector<vector<pair<int,int>>> adjacencies;
    scheme.resize(1);
    char c;
    int res = 0;

    while (!in.eof()) {
        c = in.get();
        if (c == '\n') {
            scheme.resize(scheme.size() + 1);
        } else {
            scheme.back().push_back(c);
        }
    }

    for (int i = 0; i < scheme.size(); ++i) {
        for (int j = 0; j < scheme[i].size(); ++j) {
            c = scheme[i][j];
            if (c >= '0' && c <= '9') {
                int start = j;
                while (j < scheme[i].size() && scheme[i][j] >= '0' && scheme[i][j] <= '9')
                    ++j;
                
                int end = j - 1;
                bool clean = true;
                for (int k = start - 1; k <= end + 1; ++k) {
                    if (k >= 0 && k < scheme[i].size()) {
                        for (int l = i - 1; l <= i + 1; ++l) {
                            if (l >= 0 && l < scheme.size() && k >= 0 && k < scheme[l].size()) {
                                if (!((l == i && k >= start && k <= end) || scheme[l][k] == '.')) {
                                    clean = false;
                                }
                            }
                        }
                    }
                }
                if (!clean) {
                    int n = 0;
                    for (int m = start; m <= end; ++m) {
                        n *= 10;
                        n += scheme[i][m] - '0';
                    }
                    part_numbers.push_back(n);
                    adjacencies.push_back(vector<pair<int,int>>());
                    for (int m = start - 1; m <= end + 1; ++m) {
                        for (int n = i - 1; n <= i + 1; ++n) {
                            if (n >= 0 && n < scheme.size() && m >= 0 && m < scheme[n].size()) {
                                adjacencies.back().push_back({n,m});
                            }
                        }
                    }
                    // res += n;
                }
            }
        }
    }

    for (int i = 0; i < scheme.size(); ++i) {
        for (int j = 0; j < scheme[i].size(); ++j) {
            if (scheme[i][j] == '*') {
                vector<int> adj;
                for (int k = 0; k < adjacencies.size(); ++k) {
                    if (any_of(adjacencies[k].begin(), adjacencies[k].end(), [&](pair<int,int> x){ return x.first == i && x.second == j; })) {
                        adj.push_back(part_numbers[k]);
                    }
                }
                if (adj.size() == 2)
                    res += adj[0] * adj[1];
            }
        }
    }

    cout << res; // 87263515

    return 0;
}