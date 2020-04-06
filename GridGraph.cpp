#include "GridGraph.h"

#include <algorithm>
#include <iostream>

void GridGraph::addNode(int x, int y, string nodeVal) {
    GridNode *n = new GridNode(x, y, nodeVal);
    nodes.insert(n);
}

static void checkAndAdd(GridNode *a, GridNode *b) {
    if (find(a->neighbors.begin(), a->neighbors.end(), b) == a->neighbors.end())
        a->neighbors.push_back(b);
}

void GridGraph::addUndirectedEdge(GridNode *first, GridNode *second) {
    int xDiff = first->x - second->x;
    if (xDiff < 0)
        xDiff *= -1;

    int yDiff = first->y - second->y;
    if (yDiff < 0)
        yDiff *= -1;
    
    if (xDiff + yDiff != 1)
        return;

    checkAndAdd(first, second);
    checkAndAdd(second, first);
}

static void checkAndRemove(GridNode *a, GridNode *b) {
    auto i = find(a->neighbors.begin(), a->neighbors.end(), b);
    if (i != a->neighbors.end())
        a->neighbors.erase(i);
}

void GridGraph::removeUndirectedEdge(GridNode *first, GridNode *second) {
    checkAndRemove(first, second);
    checkAndRemove(second, first);
}

//This horrific function returns the GridNode with the specified name
GridNode *GridGraph::getNode(string name) {
    return *find_if(nodes.begin(), nodes.end(), [name](GridNode *n){ return n->name.compare(name) == 0; });
}

void GridGraph::printGraphDBG() {
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

void GridGraph::printGraph() {
    GridNode *init = *nodes.begin();

    int xMax = init->x;
    int yMax = init->y;

    for (auto i = nodes.begin(); i != nodes.end(); i++) {
        if ((*i)->x > xMax)
            xMax = (*i)->x;
        
        if ((*i)->y > yMax)
            yMax = (*i)->y;
    }

    char out[2*yMax+1][2*(xMax + 1)];

    for (int i = 0; i < 2*(xMax+1); i++) {
        for (int j = 0; j < 2*yMax+1; j++) {
            if (i == 2*(xMax+1)-1)
                out[j][i] = '\0';
            else
                out[j][i] = ' ';
        }
    }

    for (auto i = nodes.begin(); i != nodes.end(); i++) {
        GridNode n = **i;

        out[2*n.y][2*n.x] = 'O';

        for (auto j = n.neighbors.begin(); j != n.neighbors.end(); j++)
            out[n.y + (*j)->y][n.x + (*j)->x] = '#';
    }

    for (int i = 0; i < 2*yMax + 1; i++) {
        cout << out[i] << endl;
    }
}