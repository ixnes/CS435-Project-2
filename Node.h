#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>

using namespace std;

//typedef struct Node Node;

class Node {
public:
    string name;
    unordered_map<Node *, int> neighbors;

    Node(string s) {
        name = s;
    }
};

#endif