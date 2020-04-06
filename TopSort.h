#ifndef TOPSORT_H
#define TOPSORT_H

#include "DirectedGraph.h"

#include <queue>
#include <stack>
#include <unordered_map>

class TopSort {
private:
    static unordered_map<Node *, bool> visited;

    static void initializeVisited() {
        visited = unordered_map<Node *, bool>();
    }

    static bool isVisited(Node *n) {
        if (visited.find(n) == visited.end())
            return false;
        
        return visited[n];
    }

    static bool setVisited(Node *n) {
        visited[n] = true;
    }

    static void mDFS_(Node *n, stack<Node *> *s) {
        setVisited(n);

        for (Node * const& m: n->neighbors)
            if (!isVisited(m))
                mDFS_(m, s);
        
        s->push(n);
    }
public:
    static vector<Node *> *Kahns(DirectedGraph *graph) {
        vector<Node *> *ret = new vector<Node *>();

        unordered_map<Node *, int> numDependencies;

        unordered_set<Node *> nodes = graph->getAllNodes();

        for (Node * const& n : nodes)
            numDependencies[n] = 0;

        for (Node * const& n : nodes) {
            for (Node * const& m : n->neighbors)
                numDependencies[m]++;
        }

        queue<Node *> q;

        for (Node * const& n : nodes)
            if (numDependencies[n] == 0)
                q.push(n);
        
        while (q.size() != 0) {
            Node *n = q.front();
            q.pop();

            ret->push_back(n);

            numDependencies[n] = -1;

            for (Node * const& m : n->neighbors) {
                numDependencies[m]--;
                if (numDependencies[m] == 0)
                    q.push(m);
            }
        }

        return ret;
    }

    static vector<Node *> *mDFS(DirectedGraph *graph) {
        initializeVisited();
        stack<Node *> *s = new stack<Node *>();

        unordered_set<Node *> nodes = graph->getAllNodes();

        for (Node * const& n : nodes) {
            if (!isVisited(n))
                mDFS_(n, s);
        }

        vector<Node *> *ret = new vector<Node *>();

        while (s->size() != 0) {
            ret->push_back(s->top());
            s->pop();
        }

        return ret;
    }
};

unordered_map<Node *, bool> TopSort::visited;

#endif