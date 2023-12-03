#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

    fstream in{"input.txt"};
    vector<vector<char>> scheme;
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
                    res += n;
                }
            }
        }
    }

    cout << res; // 554003

    return 0;
}