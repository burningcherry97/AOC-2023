#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"input.txt"};
    vector<vector<int>> readings;
    string line;
    int res = 0;
    while (!in.eof()) {
        readings.clear();
        readings.push_back(vector<int>());
        getline(in, line);
        stringstream ss{line};
        int n;
        while (!ss.eof()) {
            ss >> n;
            readings.front().push_back(n);
        }
        while (!all_of(readings.back().begin(), readings.back().end(), [](int n){ return n == 0; })) {
            int r_size = readings.size() - 1, size = readings.back().size();
            readings.push_back(vector<int>());
            for (int i = 0; i < size - 1; ++i) {
                readings.back().push_back(readings[r_size][i+1] - readings[r_size][i]);
            }
        }
        readings.back().push_back(0);
        for (int i = readings.size() - 2; i >=0; --i) {
            readings[i].push_back(readings[i+1].back() + readings[i].back());
        }
        res += readings.front().back();
    }
    in.close();

    cout << res; // 1992273652

    return 0;
}