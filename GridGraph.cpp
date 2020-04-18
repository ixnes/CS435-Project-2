#include "GridGraph.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

void GridGraph::addNode(int x, int y, string nodeVal) {
    GridNode *n = new GridNode(x, y, nodeVal);
    nodes.insert(n);
}

void GridGraph::addUndirectedEdge(GridNode *first, GridNode *second) {
    int xDiff = abs(first->x - second->x);

    int yDiff = abs(first->y - second->y);
    
    if (xDiff + yDiff != 1)
        return;

    first->neighbors[second] = 1;
    second->neighbors[first] = 1;
}

void GridGraph::removeUndirectedEdge(GridNode *first, GridNode *second) {
    first->neighbors.erase(second);
    second->neighbors.erase(first);
}

//This horrific function returns the GridNode with the specified name
GridNode *GridGraph::getNode(string name) {
    for (auto it = nodes.begin(); it != nodes.end(); it++)
        if ((*it)->name.compare(name) == 0)
            return *it;
}

void GridGraph::printGraphDBG() {
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
            out[n.y + ((GridNode *)(*j).first)->y][n.x + ((GridNode *)(*j).first)->x] = '#';
    }

    for (int i = 0; i < 2*yMax + 1; i++) {
        cout << out[i] << endl;
    }
}