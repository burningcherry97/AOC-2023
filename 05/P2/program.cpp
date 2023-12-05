// Brute force approach that took some 15 minutes -- still quicker than
// implementing a non-BF solution. A non-BF solution would probably
// have to build from the end, on every step mapping ranges to the previous 
// map on the list. However, overlapping ranges complicate this beyond my
// confidence to code this properly.


#include <fstream>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>

using namespace std;

struct Instruction {
    long long int destination_start;
    long long int source_start;
    long long int length;

    Instruction(long long int a, long long int b, long long int c) {
        destination_start = a;
        source_start = b;
        length = c;
    }

    Instruction() {}
};

int main(int argc, char** argv) {

    fstream in{"../P1/input.txt"};
    string line, token; long long int n, m;
    vector<pair<long long int, long long int>> seeds;
    vector<vector<Instruction>> almanac;

    getline(in, line);
    stringstream ss{line};
    ss >> token;
    while (!ss.eof()) {
        ss >> n >> m;
        seeds.push_back({n,m});
    }

    getline(in, line);

    for (int i = 0; i < 7; ++i) {
        almanac.push_back(vector<Instruction>());
        getline(in, line);
        while (true) {
            getline(in, line);
            if (line == "")
                break;
            stringstream ss1{line};
            long long int dest, sourc, rang;
            ss1 >> dest >> sourc >> rang;
            almanac.back().push_back(Instruction(dest, sourc, rang));
            if (in.eof())
                break;
        }
    }

    long long int res = INT64_MAX;

// long long int i = 0;

    for (pair<long long int, long long int>& seed_range : seeds) {
        for (long long int seed_orig = seed_range.first; seed_orig < seed_range.first + seed_range.second; ++seed_orig) {
            long long int seed = seed_orig;
            for (int i = 0; i < 7; ++i) {
                for (Instruction& a : almanac[i]) {
                    if (seed >= a.source_start && seed < a.source_start + a.length) {
                        seed += a.destination_start - a.source_start;
                        break;
                    }
                }
            }
            if (seed < res)
                res = seed;
            // ++i;
            // if (i%1000000 == 0)
            //     cout << i << ' ';
        }
        cout << "Range.\n";
    }

    cout << res; // 50855035
}
