#include "DirectedGraph.h"

#include <algorithm>
#include <iostream>

void DirectedGraph::addNode(string nodeVal) {
    Node *n = new Node(nodeVal);
    nodes.insert(n);
}

void DirectedGraph::addDirectedEdge(Node *first, Node *second) {
    first->neighbors[second] = 1;
}

void DirectedGraph::removeDirectedEdge(Node *first, Node *second) {
    first->neighbors.erase(second);
}

//This horrific function returns the Node with the specified name
Node *DirectedGraph::getNode(string name) {
    for (auto it = nodes.begin(); it != nodes.end(); it++)
        if ((*it)->name.compare(name) == 0)
            return *it;
}

void DirectedGraph::printGraph() {
    for (auto i = nodes.begin(); i != nodes.end(); i++) {
        cout << (*i)->name << ": ";

        if ((*i)->neighbors.size() == 0) {
            cout << endl;
            continue;
        }

        auto j = (*i)->neighbors.begin();
        cout << (*j).first->name;
        j++;

        for ( ; j != (*i)->neighbors.end(); j++)
            cout << " , " << (*j).first->name;
        
        cout << endl;
    }
}