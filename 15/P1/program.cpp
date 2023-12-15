#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int aoc_hash(std::string s) {
    unsigned char curr_val = 0;
    for (char c : s) {
        curr_val += c;
        curr_val *= 17;
    }
    return curr_val;
}

int main(int argc, char** argv) {
    using namespace std;

    // cout << aoc_hash("HASH");
    fstream in{"input.txt"};
    vector<string> instructions;
    instructions.push_back("");
    int res = 0;

    while (!in.eof()) {
        char c = in.get();
        if (c == EOF) {
            break;
        }
        if (c == ',') {
            instructions.push_back("");
        } else {
            instructions.back() += c;
        }
    }

    for (string& s : instructions) {
        res += aoc_hash(s);
    }

    cout << res; // 516657
}