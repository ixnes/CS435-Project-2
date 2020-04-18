#ifndef GRIDNODE_H
#define GRIDNODE_H

#include "Node.h"

#include <string>
#include <unordered_map>

using namespace std;

class GridNode : public Node {
public:
    int x;
    int y;

    GridNode(int xPos, int yPos, string s) : Node(s) {
        this->x = xPos;
        this->y = yPos;
    }
};

#endif