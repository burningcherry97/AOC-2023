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

    fstream in{"input.txt"};
    string line, token; long long int n;
    vector<long long int> seeds;
    vector<vector<Instruction>> almanac;

    getline(in, line);
    stringstream ss{line};
    ss >> token;
    while (!ss.eof()) {
        ss >> n;
        seeds.push_back(n);
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

    for (long long int seed : seeds) {
        cout << seed << ' ';
        for (int i = 0; i < 7; ++i) {
            for (Instruction& a : almanac[i]) {
                if (seed >= a.source_start && seed < a.source_start + a.length) {
                    seed += a.destination_start - a.source_start;
                    break;
                }
            }
            cout << seed << ' ';
        }
        if (seed < res)
            res = seed;
        cout << endl;
    }

    cout << res; // 157211394
}
