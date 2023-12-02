#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    
    fstream in{"../P1/input.txt"};
    string line;
    int game = 0;
    int res = 0;

    while (!in.eof()) {
        ++game;
        getline(in,line);
        line += ';';
        stringstream ss{line};
        int n; string token;
        ss >> token >> token;

        bool exceeded = false;
        int red = 0, green = 0, blue = 0;
        while (!ss.eof()) {
            ss >> n >> token;
            if (token.front() == 'r') 
                red = max(red,n);
            else if (token.front() == 'b')
                blue = max(blue,n);
            else
                green = max(green,n);
        }
        res += (red ? red : 1) * (green ? green : 1) * (blue ? blue : 1);
    }

    cout << res << endl; // 69929
}