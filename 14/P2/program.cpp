#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"../P1/input.txt"};
    vector<vector<char>> scheme;
    scheme.push_back(vector<char>());
    vector<pair<int,int>> rocks;

    // map of scheme states to their history of appearance
    map<vector<vector<char>>,vector<int>> cache;
    // history of loads after every iteration
    vector<int> loads;
    // placeholder for "iteration 0"
    loads.push_back(0);

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

    for (int it = 1; ; ++it) {
        // before each tilt, we need to sort the rocks so that they don't block each other
        std::sort(rocks.begin(), rocks.end(), [](pair<int,int> left, pair<int,int> right) {
            return left.first < right.first;
        });
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
        std::sort(rocks.begin(), rocks.end(), [](pair<int,int> left, pair<int,int> right) {
            return left.second < right.second;
        });
        for (bool changed = true; changed;) {
            changed = false;
            for (auto& p : rocks) {
                if (p.second > 0) {
                    if (scheme[p.first][p.second-1] == '.') {
                        scheme[p.first][p.second] = '.';
                        --p.second;
                        scheme[p.first][p.second] = 'O';
                        changed = true;
                    }
                }
            }
        }
        std::sort(rocks.begin(), rocks.end(), [](pair<int,int> left, pair<int,int> right) {
            return left.first > right.first;
        });
        for (bool changed = true; changed;) {
            changed = false;
            for (auto& p : rocks) {
                if (p.first < scheme.size()-1) {
                    if (scheme[p.first+1][p.second] == '.') {
                        scheme[p.first][p.second] = '.';
                        ++p.first;
                        scheme[p.first][p.second] = 'O';
                        changed = true;
                    }
                }
            }
        }
        std::sort(rocks.begin(), rocks.end(), [](pair<int,int> left, pair<int,int> right) {
            return left.second > right.second;
        });
        for (bool changed = true; changed;) {
            changed = false;
            for (auto& p : rocks) {
                if (p.second < scheme.back().size()-1) {
                    if (scheme[p.first][p.second+1] == '.') {
                        scheme[p.first][p.second] = '.';
                        ++p.second;
                        scheme[p.first][p.second] = 'O';
                        changed = true;
                    }
                }
            }
        }
        int load = 0;
        for (auto p : rocks) {
            load += scheme.size() - p.first;
        }
        // save history
        cache[scheme].push_back(it);
        loads.push_back(load);
        // identify a cycle
        if (cache[scheme].size() >= 2) {
            int it1 = *(cache[scheme].end()-2);
            int it2 = it; // *(cache[scheme].end()-1);
            // check within the cycle
            if (loads[it1] == loads[it2]) {
                int steps = (1'000'000'000 - it) % (it2-it1);
                cout << loads[it1+steps]; // 84328
                break;
            }
        }
    }

    return 0;
}