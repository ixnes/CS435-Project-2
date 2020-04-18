#include "Graph.h"

#include <algorithm>
#include <iostream>

void Graph::addNode(string nodeVal) {
    Node *n = new Node(nodeVal);
    nodes.insert(n);
}

void Graph::addUndirectedEdge(Node *first, Node *second) {
    first->neighbors[second] = 1;
    second->neighbors[first] = 1;
}

void Graph::removeUndirectedEdge(Node *first, Node *second) {
    first->neighbors.erase(second);
    second->neighbors.erase(first);
}

//This horrific function returns the Node with the specified name
Node *Graph::getNode(string name) {
    for (auto it = nodes.begin(); it != nodes.end(); it++)
        if ((*it)->name.compare(name) == 0)
            return *it;
}

void Graph::printGraph() {
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