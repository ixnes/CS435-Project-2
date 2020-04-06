#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include "GridNode.h"

#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class GridGraph {
private:
    unordered_set<GridNode *> nodes;
public:
    void addNode(int x, int y, string nodeVal);
    void addUndirectedEdge(GridNode *first, GridNode *second);
    void removeUndirectedEdge(GridNode *first, GridNode *second);

    unordered_set<GridNode *> getAllNodes() {
        return nodes;
    }

    GridNode *getNode(string name);

    void printGraphDBG();

    void printGraph();
};

#endif