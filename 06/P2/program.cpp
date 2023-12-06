#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {

    vector<int> times, distances;
    fstream in{"../P1/input.txt"};
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

    long long int time_total = times[0], distance_total = distances[0];

    for (int i = 1; i < times.size(); ++i) {
        time_total = time_total * pow(10, ceil(log10(times[i]))) + times[i];
        distance_total = distance_total * pow(10, ceil(log10(distances[i]))) + distances[i];
    }

    int res = 1;

    double t = time_total;
    double d = distance_total;
    double delta = sqrt(t*t - 4*d);
    double x1 = (t - delta)/2;
    double x2 = (t + delta)/2;
    if (x1 == floor(x1) && x2 == floor(x2)) {
        x1 = x1 + 1;
    }
    res *= floor(x2) - floor(x1);

    cout << res; // 35865985

    return 0;
}