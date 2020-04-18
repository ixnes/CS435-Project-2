#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include "Node.h"

#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class WeightedGraph {
private:
    unordered_set<Node *> nodes;
public:
    void addNode(string nodeVal);
    void addWeightedEdge(Node *first, Node *second, int edgeWeight);
    void removeWeightedEdge(Node *first, Node *second);

    unordered_set<Node *> getAllNodes() {
        return nodes;
    }

    Node *getNode(string name);

    void printGraph();
};

#endif