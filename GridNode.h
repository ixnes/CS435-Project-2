#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <string>
#include <vector>

using namespace std;

typedef struct GridNode GridNode;

struct GridNode {
    string name;
    vector<GridNode *> neighbors;

    int x;
    int y;

    GridNode(int xPos, int yPos, string s) {
        x = xPos;
        y = yPos;
        name = s;
    }
};

#endif