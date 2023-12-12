#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string tail(std::string s) {
    return s.substr(1, s.size()-1);
}

int matches(std::string scheme, std::vector<int> broken, bool must_start_good, bool must_start_broken) {
    if (scheme == "" ) {
        if (broken.empty()) {
            return 1;
        }
        return 0;
    }
    if (scheme[0] == '?') {
        if (broken.empty()) {
            return matches(tail(scheme), broken, true, false);
        }
        if (must_start_good) {
            return matches(tail(scheme), broken, false, false);
        }
        if (must_start_broken) {
            --broken.front();
            if (broken.front() == 0) {
                broken.erase(broken.begin());
                return matches(tail(scheme), broken, true, false);
            } else {
                return matches(tail(scheme), broken, false, true);
            }
        }
        // if nothing specified
        int good_case = matches(tail(scheme), broken, false, false);
        int broken_case;
        --broken.front();
        if (broken.front() == 0) {
            broken.erase(broken.begin());
            broken_case = matches(tail(scheme), broken, true, false);
        } else {
            broken_case = matches(tail(scheme), broken, false, true);
        }
        return good_case + broken_case;
    }
    if (scheme[0] == '.') {
        if (must_start_broken) {
            return 0;
        }
        return matches(tail(scheme), broken, false, false);
    }
    if (scheme[0] == '#') {
        if (broken.empty()) {
            return 0;
        }
        if (must_start_good) {
            return 0;
        }
        --broken.front();
        if (broken.front() == 0) {
            broken.erase(broken.begin());
            return matches(tail(scheme), broken, true, false);
        } else {
            return matches(tail(scheme), broken, false, true);
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"input.txt"};
    string line;
    vector<string> schemes;
    vector<vector<int>> broken;
    int res = 0;

    while (!in.eof()) {
        getline(in, line);
        stringstream ss{line};
        string token; int n;
        ss >> token;
        schemes.push_back(token);
        broken.push_back(vector<int>());
        while (!ss.eof()) {
            ss >> n;
            broken.back().push_back(n);
            ss.get();
        }
    }

    for (int i = 0; i < schemes.size(); ++i) {
        int n = matches(schemes[i], broken[i], false, false);
        res += n;
        // cout << n << '\n';
    }

    cout << res; // 8022

    return 0;
}