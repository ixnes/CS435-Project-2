#ifndef WEIGHTEDNODE_H
#define WEIGHTEDNODE_H

#include <string>
#include <unordered_map>

using namespace std;

typedef struct WeightedNode WeightedNode;

struct WeightedNode {
    string name;
    unordered_map<WeightedNode *, int> neighbors;

    WeightedNode(string s) {
        name = s;
    }
};

#endif