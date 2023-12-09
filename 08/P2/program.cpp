#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Node {
    std::string left, right;

    Node(std::string l, std::string r) {
        left = l;
        right = r;
    }

    Node () {}
};

int main(int argc, char** argv) {

    std::fstream in{"../P1/input.txt"};
    std::string pattern, line;
    std::map<std::string, Node> paper;
    std::vector<std::string> ghosts;

    getline(in, pattern);
    getline(in, line);
    while (!in.eof()) {
        getline(in, line);
        std::stringstream ss{line};
        std::string origin, left, right;
        ss >> origin >> left;
        ss.get(); ss.get();
        ss >> left;
        left.pop_back();
        ss >> right;
        right.pop_back();
        paper[origin] = Node(left, right);
        if (origin.back() == 'A') {
            ghosts.push_back(origin);
        }
    }

    for (std::string& place : ghosts) {            
        for (int i = 0; ; ++i) {
            if (pattern[i%pattern.size()] == 'R') {
                place = paper[place].right;
            } else {
                place = paper[place].left;
            }
            if (place.back() == 'Z') {
                std::cout << i + 1 << ", ";
                break;
            }
        }
    }

    // output: 18113, 20569, 21797, 13201, 24253, 22411
    // res = lcm(output): 21366921060721
    // the inputs are constructed so that the above is correct

    return 0;
}