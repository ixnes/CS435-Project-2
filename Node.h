#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

typedef struct Node Node;

struct Node {
    string name;
    vector<Node *> neighbors;

    Node(string s) {
        name = s;
    }
};

#endif