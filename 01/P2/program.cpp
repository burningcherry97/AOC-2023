#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

    ifstream in{"../P1/input.txt"};
    string line;
    int res = 0;

    while (!in.eof()) {
        in >> line;
        int first_digit, second_digit;
        bool past_first = false;
        vector<string> patterns = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        for (int i = 0; i < line.size(); ++i) {
            char c = line[i];
            int recognized = -1;
            if (c >= '0' && c <= '9')
                recognized = c - '0';
            for (int j = 0; j < patterns.size(); ++j) {
                if (strncmp(&line[i],&patterns[j][0],patterns[j].size()) == 0) {
                    recognized = j;
                }
            }
            if (recognized != -1) {
                second_digit = recognized;
                if (!past_first) {
                    first_digit = recognized;
                    past_first = true;
                }
            }
        }
        res += first_digit * 10 + second_digit;
    }

    cout << res << endl; // 54265

    return 0;
}