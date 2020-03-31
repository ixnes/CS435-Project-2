#include "Graph.h"

#include <algorithm>
#include <iostream>

void Graph::addNode(string nodeVal) {
    Node *n = new Node(nodeVal);
    nodes.insert(n);
}

void checkAndAdd(Node *a, Node *b) {
    if (find(a->neighbors.begin(), a->neighbors.end(), b) == a->neighbors.end())
        a->neighbors.push_back(b);
}

void Graph::addUndirectedEdge(Node *first, Node *second) {
    checkAndAdd(first, second);
    checkAndAdd(second, first);
}

void checkAndRemove(Node *a, Node *b) {
    auto i = find(a->neighbors.begin(), a->neighbors.end(), b);
    if (i != a->neighbors.end())
        a->neighbors.erase(i);
}

void Graph::removeUndirectedEdge(Node *first, Node *second) {
    checkAndRemove(first, second);
    checkAndRemove(second, first);
}

//This horrific function returns the Node with the specified name
Node *Graph::getNode(string name) {
    return *find_if(nodes.begin(), nodes.end(), [name](Node *n){ return n->name.compare(name) == 0; });
}

void Graph::printGraph() {
    for (auto i = nodes.begin(); i != nodes.end(); i++) {
        cout << (*i)->name << ": ";

        if ((*i)->neighbors.size() == 0) {
            cout << endl;
            continue;
        }

        auto j = (*i)->neighbors.begin();
        cout << (*j)->name;
        j++;

        for ( ; j != (*i)->neighbors.end(); j++)
            cout << " , " << (*j)->name;
        
        cout << endl;
    }
}