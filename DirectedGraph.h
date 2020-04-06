#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include "Node.h"

#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class DirectedGraph {
private:
    unordered_set<Node *> nodes;
public:
    void addNode(string nodeVal);
    void addDirectedEdge(Node *first, Node *second);
    void removeDirectedEdge(Node *first, Node *second);

    unordered_set<Node *> getAllNodes() {
        return nodes;
    }

    Node *getNode(string name);

    void printGraph();
};

#endif