#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

enum Direction { NORTH, EAST, SOUTH, WEST };

struct Node {
    int x;
    int y;
    // int edge;
    Direction direction;
    int part_dist;

    Node(int x, int y, Direction direction, int part_dist) {
        this->x = x;
        this->y = y;
        this->direction = direction;
        this->part_dist = part_dist;
    }

    Node() {}
};

bool operator<(const Node l, const Node r) {
    if (l.x < r.x) return true;
    if (l.x > r.x) return false;
    if (l.y < r.y) return true;
    if (l.y > r.y) return false;
    if (l.direction < r.direction) return true;
    if (l.direction > r.direction) return false;
    if (l.part_dist < r.part_dist) return true;
    if (l.part_dist > r.part_dist) return false;
    return false;
}

bool can_move_forward(int X, int Y, Node n) {
    switch (n.direction)
    {
    case Direction::NORTH:
        return n.y > 0;
    case Direction::EAST:
        return n.x < X;
    case Direction::SOUTH:
        return n.y < Y;
    case Direction::WEST:
        return n.x > 0;
    default:
        return false;
    }
}

Node forward_node(Node n) {
    ++n.part_dist;
    switch (n.direction)
    {
    case Direction::NORTH:
        --n.y;
        return n;
    case Direction::EAST:
        ++n.x;
        return n;
    case Direction::SOUTH:
        ++n.y;
        return n;
    case Direction::WEST:
        --n.x;
        return n;
    default:
        return n;
    }
}

bool can_move_right(int X, int Y, Node n) {
    switch (n.direction)
    {
    case Direction::NORTH:
        return n.x < X;
    case Direction::EAST:
        return n.y < Y;
    case Direction::SOUTH:
        return n.x > 0;
    case Direction::WEST:
        return n.y > 0;
    default:
        return false;
    }
}

Node right_node(Node n) {
    n.part_dist = 1;
    switch (n.direction)
    {
    case Direction::NORTH:
        n.direction = Direction::EAST;
        ++n.x;
        return n;
    case Direction::EAST:
        n.direction = Direction::SOUTH;
        ++n.y;
        return n;
    case Direction::SOUTH:
        n.direction = Direction::WEST;
        --n.x;
        return n;
    case Direction::WEST:
        n.direction = Direction::NORTH;
        --n.y;
        return n;
    default:
        return n;
    }
}

bool can_move_left(int X, int Y, Node n) {
    switch (n.direction)
    {
    case Direction::NORTH:
        return n.x > 0;
    case Direction::EAST:
        return n.y > 0;
    case Direction::SOUTH:
        return n.x < X;
    case Direction::WEST:
        return n.y < Y;
    default:
        return false;
    }
}

Node left_node(Node n) {
    n.part_dist = 1;
    switch (n.direction)
    {
    case Direction::NORTH:
        n.direction = Direction::WEST;
        --n.x;
        return n;
    case Direction::EAST:
        n.direction = Direction::NORTH;
        --n.y;
        return n;
    case Direction::SOUTH:
        n.direction = Direction::EAST;
        ++n.x;
        return n;
    case Direction::WEST:
        n.direction = Direction::SOUTH;
        ++n.y;
        return n;
    default:
        return n;
    }
}

std::vector<Node> adjacent(int X, int Y, Node n) {
    auto res = std::vector<Node>();
    if (can_move_forward(X,Y,n)) {
        if (n.part_dist < 3) {
            res.push_back(forward_node(n));
        }
    }
    if (can_move_right(X,Y,n)) {
        res.push_back(right_node(n));
    }
    if (can_move_left(X,Y,n)) {
        res.push_back(left_node(n));
    }
    return res;
}

void relax(std::priority_queue<Node*>& q, int x, int y, Direction direction, int part_dist) {
    
}

int main(int argc, char** argv) {
    using namespace std;

    fstream in{"input.txt"};
    vector<Node> nodes;
    vector<int> weight;
    vector<int> distance;
    map<Node, int> index;
    // map<Node,Node> prev;

    int x = 0;
    int y = 0;
    while (!in.eof()) {
        char c = in.get();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            x = 0;
            ++y;
        } else {
            for (Direction d : {NORTH,EAST,SOUTH,WEST}) {
                for (int i = 1; i <= 3; ++i) {
                    // cout << x << ' ';
                    index[Node{x,y,d,i}] = nodes.size();
                    nodes.push_back({x,y,d,i});
                    weight.push_back(c - '0');
                    distance.push_back(2147483647/4);
                }
            }
            ++x;
        }
    }

    --x;
    
    distance[index[{1,0,Direction::EAST,1}]] = 0;
    distance[index[{0,1,Direction::SOUTH,1}]] = 0;

    priority_queue<pair<int,Node>, vector<pair<int,Node>>, greater<pair<int,Node>>> pq;
    for (int i = 0; i < nodes.size(); ++i) {
        pq.push({distance[i],nodes[i]});
    }

    while (!pq.empty()) {
        Node n = pq.top().second;
        int i = index[n];
        int w = weight[i];
        pq.pop();

        auto adj = adjacent(x,y,n);

        for (Node a : adj) {
            if (distance[index[n]] + w < distance[index[a]]) {
                distance[index[a]] = distance[index[n]] + w;
                pq.push({distance[index[n]] + w, a});
                // prev[a] = n;
                // cout << "y: " << a.y << " x: " << a.x << " dir: " << a.direction << " part dist: " << a.part_dist << " total dist: " << distance[index[n]] + w << '\n';
            }
        }
    }

    // for (int j = 0; j <= y; ++j) {
    //     for (int k = 0; k <= x; ++k) {
    //         cout << "y: " << j << " x: " << k << "       ";
    //         for (Direction d : {NORTH,EAST,SOUTH,WEST}) {
    //             for (int i = 1; i <= 3; ++i) {
    //                 cout << distance[index[Node{k,j,d,i}]] << ' ';
    //             }
    //             cout << "   ";
    //         }
    //         cout << '\n';
    //     }
    // }

    int res = 2147483647/4;
    for (Direction d : {NORTH,EAST,SOUTH,WEST}) {
        for (int i = 1; i <= 3; ++i) {
            res = min(res, distance[index[{x,y,d,i}]]);
        }
    }

    res += weight.back();

    cout << res;

    return 0;
}