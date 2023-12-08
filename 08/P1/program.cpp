#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

struct Node {
    std::string left, right;

    Node(std::string l, std::string r) {
        left = l;
        right = r;
    }

    Node () {}
};

int main(int argc, char** argv) {

    std::fstream in{"input.txt"};
    std::string pattern, line;
    std::map<std::string, Node> paper;
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
    }

    std::string place = "AAA";

    for (int i = 0; ; ++i) {
        if (pattern[i%pattern.size()] == 'R') {
            place = paper[place].right;
        } else {
            place = paper[place].left;
        }
        if (place == "ZZZ") {
            std::cout << i + 1; // 20569
            break;
        }
    }

    return 0;
}