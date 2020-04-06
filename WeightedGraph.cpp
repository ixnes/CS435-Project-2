#include "WeightedGraph.h"

#include <algorithm>
#include <iostream>

void WeightedGraph::addNode(string nodeVal) {
    WeightedNode *n = new WeightedNode(nodeVal);
    nodes.insert(n);
}

void WeightedGraph::addWeightedEdge(WeightedNode *first, WeightedNode *second, int edgeWeight) {
    first->neighbors[second] = edgeWeight;
    //checkAndAdd(second, first);
}

static void checkAndRemove(WeightedNode *a, WeightedNode *b) {
    auto i = a->neighbors.find(b);
    if (i != a->neighbors.end())
        a->neighbors.erase(i);
}

void WeightedGraph::removeWeightedEdge(WeightedNode *first, WeightedNode *second) {
    checkAndRemove(first, second);
    //checkAndRemove(second, first);
}

//This horrific function returns the Node with the specified name
WeightedNode *WeightedGraph::getNode(string name) {
    return *find_if(nodes.begin(), nodes.end(), [name](WeightedNode *n){ return n->name.compare(name) == 0; });
}

void WeightedGraph::printGraph() {
    for (auto i = nodes.begin(); i != nodes.end(); i++) {
        cout << (*i)->name << ": ";

        if ((*i)->neighbors.size() == 0) {
            cout << endl;
            continue;
        }

        auto j = (*i)->neighbors.begin();
        cout << (*j).first->name << "[" << (*j).second << "]";
        j++;

        for ( ; j != (*i)->neighbors.end(); j++)
            cout << " , " << (*j).first->name << "[" << (*j).second << "]";
        
        cout << endl;
    }
}