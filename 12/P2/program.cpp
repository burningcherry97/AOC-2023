// takes about 3 minutes to run on my PC
// the idea is to use memoized recursion

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::string string_tail(std::string s) {
    return s.substr(1, s.size()-1);
}

long long int matches(std::string scheme, std::vector<int> broken,
        std::map<std::tuple<std::string,std::vector<int>,bool,bool>,long long int>& cache,
        bool must_start_good, bool must_start_broken) {
    if (scheme == "" ) {
        if (broken.empty()) {
            return 1;
        }
        return 0;
    }
    std::string tail = string_tail(scheme);
    if (scheme[0] == '?') {
        if (broken.empty()) {
            if (cache.find({tail, broken, true, false}) == cache.end())
                cache[{tail, broken, true, false}] = matches(tail, broken, cache, true, false);
            return cache[{tail, broken, true, false}];
        }
        if (must_start_good) {
            if (cache.find({tail, broken, false, false}) == cache.end())
                cache[{tail, broken, false, false}] = matches(tail, broken, cache, false, false);
            return cache[{tail, broken, false, false}];
        }
        if (must_start_broken) {
            --broken.front();
            if (broken.front() == 0) {
                broken.erase(broken.begin());
                if (cache.find({tail, broken, true, false}) == cache.end())
                    cache[{tail, broken, true, false}] = matches(tail, broken, cache, true, false);
                return cache[{tail, broken, true, false}];
            } else {
                if (cache.find({tail, broken, false, true}) == cache.end())
                    cache[{tail, broken, false, true}] = matches(tail, broken, cache, false, true);
                return cache[{tail, broken, false, true}];
            }
        }
        // if nothing specified
        long long int good_case;
        if (cache.find({tail, broken, false, false}) == cache.end())
            cache[{tail, broken, false, false}] = matches(tail, broken, cache, false, false);
        good_case = cache[{tail, broken, false, false}];
        long long int broken_case;
        --broken.front();
        if (broken.front() == 0) {
            broken.erase(broken.begin());
            if (cache.find({tail, broken, true, false}) == cache.end())
                cache[{tail, broken, true, false}] = matches(tail, broken, cache, true, false);
            broken_case = cache[{tail, broken, true, false}];
        } else {
            if (cache.find({tail, broken, false, true}) == cache.end())
                cache[{tail, broken, false, true}] = matches(tail, broken, cache, false, true);
            broken_case = cache[{tail, broken, false, true}];
        }
        return good_case + broken_case;
    }
    if (scheme[0] == '.') {
        if (must_start_broken) {
            return 0;
        }
        if (cache.find({tail, broken, false, false}) == cache.end())
            cache[{tail, broken, false, false}] = matches(tail, broken, cache, false, false);
        return cache[{tail, broken, false, false}];
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
            if (cache.find({tail, broken, true, false}) == cache.end())
                cache[{tail, broken, true, false}] = matches(tail, broken, cache, true, false);
            return cache[{tail, broken, true, false}];
        } else {
            if (cache.find({tail, broken, false, true}) == cache.end())
                cache[{tail, broken, false, true}] = matches(tail, broken, cache, false, true);
            return cache[{tail, broken, false, true}];
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"../P1/input.txt"};
    string line;
    vector<string> schemes;
    vector<vector<int>> broken;
    long long int res = 0;

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
        string s = schemes[i];
        int nn = broken[i].size();
        for (int j = 0; j < 4; ++j) {
            schemes[i] += '?';
            schemes[i] += s;
            for (int k = 0; k < nn; ++k) {
                broken[i].push_back(broken[i][k]);
            }
        }
    }

    for (int i = 0; i < schemes.size(); ++i) {
        // cout << i << ' ';
        map<tuple<string,vector<int>,bool,bool>,long long int> cache;
        long long int base = matches(schemes[i], broken[i], cache, false, false);
        res += base;
    }

    cout << res; // 4968620679637

    return 0;
}