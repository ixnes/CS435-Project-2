#include "WeightedGraph.h"

#include <algorithm>
#include <iostream>

void WeightedGraph::addNode(string nodeVal) {
    Node *n = new Node(nodeVal);
    nodes.insert(n);
}

void WeightedGraph::addWeightedEdge(Node *first, Node *second, int edgeWeight) {
    first->neighbors[second] = edgeWeight;
}

void WeightedGraph::removeWeightedEdge(Node *first, Node *second) {
    first->neighbors.erase(second);
}

Node *WeightedGraph::getNode(string name) {
    for (auto it = nodes.begin(); it != nodes.end(); it++)
        if ((*it)->name.compare(name) == 0)
            return *it;
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