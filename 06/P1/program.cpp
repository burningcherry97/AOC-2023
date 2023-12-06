#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {

    vector<int> times, distances;
    fstream in{"input.txt"};
    string line, token;
    int n;
    getline(in, line);
    stringstream time_stream{line};
    time_stream >> token;
    while (!time_stream.eof()) {
        time_stream >> n;
        times.push_back(n);
    }
    getline(in, line);
    stringstream distance_stream{line};
    distance_stream >> token;
    while (!distance_stream.eof()) {
        distance_stream >> n;
        distances.push_back(n);
    }
    in.close();

    int res = 1;

    // quadratic equation
    for (int i = 0; i < times.size(); ++i) {
        double t = times[i];
        double d = distances[i];
        double delta = sqrt(t*t - 4*d);
        double x1 = (t - delta)/2;
        double x2 = (t + delta)/2;
        if (x1 == floor(x1) && x2 == floor(x2)) {
            x1 = x1 + 1;
        }
        res *= floor(x2) - floor(x1);
    }

    cout << res; // 2269432

    return 0;
}