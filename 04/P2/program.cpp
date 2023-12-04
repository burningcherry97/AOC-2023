#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    
    fstream in{argv[1]};
    string line, token;
    int n;
    int res = 0;
    vector<int> copies(220,1);
    int card = 0;

    while (!in.eof()) {
        getline(in, line);
        card++;
        stringstream ss{line};
        ss >> token >> token;
        set<int> winning;
        while (true) {
            ss >> token;
            if (token == "|")
                break;
            else
                winning.insert(stoi(token));
        }
        int prize = 0;
        while (!ss.eof()) {
            ss >> n;
            if (winning.find(n) != winning.end()) {
                ++prize;
            }
        }
        for (int i = card + 1; i <= card + prize && i < copies.size(); ++i) {
            copies[i] += copies[card];
        }
    }

    for (int i : copies) {
        res += i;
    }

    cout << res - 1; // 14624680

    return 0;
}