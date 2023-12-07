#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <array>

struct Hand {
    std::string cards;
    int bet;
    int figure;
    int jokers;

    int get_symbol(char c) {
        switch (c)
        {
        case 'A':
            return 14;
            break;
        
        case 'K':
            return 13;
            break;
        
        case 'Q':
            return 12;
            break;

        case 'J':
            return 0;
            break;

        case 'T':
            return 10;
            break;
        
        default:
            return c - '0';
            break;
        }
    }

    void calculate_figure() {
        std::vector<int> deck(15, 0);
        for (char c : cards) {
            if (c == 'J')
                ++jokers;
            else
                ++deck[get_symbol(c)];
        }
        std::sort(deck.begin(), deck.end(), std::greater<int>());
        if (deck[0] == 5) {
            figure = 0;
        } else if (deck[0] == 4) {
            if (jokers)
                figure = 0;
            else
                figure = 1;
        } else if (deck[0] == 3) {
            if (deck[1] == 2) {
                figure = 2;
            } else {
                if (jokers == 2)
                    figure = 0;
                else if (jokers == 1) {
                    figure = 1;
                } else {
                    figure = 3;
                }
            }
        } else if (deck[0] == 2) {
            if (deck[1] == 2) {
                if (jokers) {
                    figure = 2;
                } else {
                    figure = 4;
                }
            } else {
                if (jokers == 3) {
                    figure = 0;
                } else if (jokers == 2) {
                    figure = 1;
                } else if (jokers == 1) {
                    figure = 3;
                } else {
                    figure = 5;
                }
            }
        } else {
            if (jokers == 4 || jokers == 5) {
                figure = 0;
            } else if (jokers == 3) {
                figure = 1;
            } else if (jokers == 2) {
                figure = 3;
            } else if (jokers == 1) {
                figure = 5;
            } else {
                figure = 6;
            }
        }
    }

    friend bool operator<(Hand& h1, Hand& h2) {
        if (h1.figure > h2.figure)
            return true;
        if (h1.figure < h2.figure)
            return false;
        for (int i = 0; i < 5; ++i) {
            if (h1.get_symbol(h1.cards[i]) < h2.get_symbol(h2.cards[i])) {
                return true;
            }
            if (h1.get_symbol(h1.cards[i]) > h2.get_symbol(h2.cards[i])) {
                return false;
            }
        }
        return false;
    }

    Hand(std::string s, int b) {
        cards = s;
        bet = b;
        figure = -1;
    }

    Hand() {
        figure = -1;
        jokers = 0;
    }
};

int main(int argc, char** argv) {

    std::fstream in{"../P1/input.txt"};
    std::vector<Hand> deck;
    while (!in.eof()) {
        deck.push_back(Hand());
        in >> deck.back().cards;
        in >> deck.back().bet;
    }
    in.close();

    for (Hand& h : deck)
        h.calculate_figure();

    std::sort(deck.begin(), deck.end());

    long long int res = 0;
    for (long long int i = 0; i < deck.size(); ++i) {
        res += deck[i].bet * (i + 1);
    }

    std::cout << res; // 248750248

    return 0;
}