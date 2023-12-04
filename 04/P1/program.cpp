#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    
    fstream in{argv[1]};
    string line, token;
    int n;
    int res = 0;

    while (!in.eof()) {
        getline(in, line);
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
                if (prize)
                    prize *= 2;
                else
                    prize = 1;
            }
        }
        res += prize;
    }

    cout << res; // 32609

    return 0;
}