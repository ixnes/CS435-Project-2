#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include "WeightedNode.h"

#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class WeightedGraph {
private:
    unordered_set<WeightedNode *> nodes;
public:
    void addNode(string nodeVal);
    void addWeightedEdge(WeightedNode *first, WeightedNode *second, int edgeWeight);
    void removeWeightedEdge(WeightedNode *first, WeightedNode *second);

    unordered_set<WeightedNode *> getAllNodes() {
        return nodes;
    }

    WeightedNode *getNode(string name);

    void printGraph();
};

#endif