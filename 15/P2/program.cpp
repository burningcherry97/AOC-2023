#include <algorithm>
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

struct Instruction {
    std::string label;
    int power;
    char mode;

    Instruction(std::string l, int p, char m) {
        label = l;
        power = p;
        mode = m;
    }
};

struct Lens {
    std::string label;
    int f;

    Lens(std::string s, int ff) {
        label = s;
        f = ff;
    }
};

int main(int argc, char** argv) {
    using namespace std;

    // cout << aoc_hash("HASH");
    fstream in{"../P1/input.txt"};
    vector<Instruction> instructions;
    // instructions.push_back("");
    int res = 0;
    vector<vector<Lens>> boxes(256);

    while (!in.eof()) {
        std::string label = "";
        char mode;
        int power;
        char c = in.get();
        if (c == EOF) {
            break;
        }
        while (isalpha(c)) {
            label += c;
            c = in.get();
        }
        if (c == '=') {
            mode = 1;
        } else {
            mode = 0;
        }
        if (mode) {
            in >> power;
        }
        in.get();
        instructions.push_back({label,power,mode});
    }

    for (Instruction& i : instructions) {
        int box = aoc_hash(i.label);
        // cout << box << ' ';
        if (i.mode == 0) {
            boxes[box].erase(
                remove_if(boxes[box].begin(), boxes[box].end(), 
                [&](Lens& l){ return l.label == i.label; }), 
                boxes[box].end());
        } else {
            bool found = false;
            for (Lens& l : boxes[box]) {
                if (l.label == i.label) {
                    l.f = i.power;
                    found = true;
                }
            }
            if (!found) {
                boxes[box].push_back(Lens(i.label,i.power));
            }
        }
    }

    for (int i = 0; i < boxes.size(); ++i) {
        for (int j = 0; j < boxes[i].size(); ++j) {
            res += (i+1) * (j+1) * boxes[i][j].f;
        }
    }

    cout << res; // 210906
}