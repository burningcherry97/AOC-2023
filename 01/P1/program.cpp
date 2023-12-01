#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

    ifstream in{"input.txt"};
    string line;
    int res = 0;

    while (!in.eof()) {
        in >> line;
        int first_digit, second_digit;
        bool past_first = false;
        for (char c : line) {
            if (c >= '0' && c <= '9') {
                second_digit = c - '0';
                if (!past_first) {
                    first_digit = c - '0';
                    past_first = true;
                }
            }
        }
        res += first_digit * 10 + second_digit;
    }

    cout << res << endl; // 54450

    return 0;
}