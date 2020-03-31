#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

typedef struct Node Node;

struct Node {
    string name;
    vector<Node *> neighbors;

    Node(string s) {
        name = s;
    }
};

class Graph {
private:
    unordered_set<Node *> nodes;
public:
    void addNode(string nodeVal);
    void addUndirectedEdge(Node *first, Node *second);
    void removeUndirectedEdge(Node *first, Node *second);

    unordered_set<Node *> getAllNodes() {
        return nodes;
    }

    Node *getNode(string name);

    void printGraph();
};

#endif