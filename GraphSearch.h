#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H

#include "Graph.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

//using namespace std;

class GraphSearch {
private:
    //DEBUG
    static void printTraversal(vector<Node *> *traversal) {
        if (traversal == nullptr) {
            std::cout << "Null" << endl;
            return;
        }
        
        if (traversal->size() == 0) {
            std::cout << "Empty" << endl;
            return;
        }
        std::cout << (*traversal)[0]->name;

        for (int i = 1; i < (*traversal).size(); i++) {
            std::cout << " , " << (*traversal)[i]->name;
        }

        std::cout << endl;
    }

    static unordered_map<Node *, bool> visited;

    static stack<Node *> *DFSRec_(Node *start, Node *end) {
        if (start == end) {
            stack<Node *> *ret = new stack<Node *>();
            ret->push(start);
            return ret;
        }

        setVisited(start);

        for (Node *& node:start->neighbors) {
            if (isVisited(node))
                continue;

            stack<Node *> *ret = DFSRec_(node, end);
            if (ret != nullptr) {
                ret->push(start);
                return ret;
            }
        }

        return nullptr;
    }

    static vector<Node *> *BFTRec_(vector<Node *> *nodes) {
        if (nodes->size() == 0)
            return new vector<Node*>();

        vector<Node *> *ret = new vector<Node *>();

        copy(nodes->begin(), nodes->end(), back_inserter(*ret));

        vector<Node *> *fwd = new vector<Node *>();

        for (Node * const& n : *nodes)
            for (Node * const& neighbor : n->neighbors)
                if (!isVisited(neighbor)) {
                    fwd->push_back(neighbor);
                    setVisited(neighbor);
                }

        vector<Node *> *bft = BFTRec_(fwd);

        copy(bft->begin(), bft->end(), back_inserter(*ret));

        return ret;
    }    

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

public:
    static vector<Node *> *DFSRec(Node *start, Node *end) {
        vector<Node *> *ret = new vector<Node *>();

        initializeVisited();

        stack<Node *> *s = DFSRec_(start, end);

        if (s == nullptr)
            return nullptr;

        while (s->size() != 0) {
            ret->push_back(s->top());
            s->pop();
        }

        return ret;
    }

    static vector<Node *> *DFSIter(Node *start, Node *end) {
        unordered_map<Node *, Node *> parent;

        stack<Node *> s;

        s.push(start);

        parent[start] = nullptr;

        Node *curr;

        bool found = false;

        while (s.size() != 0) {
            curr = s.top();
            s.pop();

            if (curr == end) {
                found = true;
                break;
            }

            if (isVisited(curr))
                continue;
            
            setVisited(curr);

            for (Node *& node:curr->neighbors) {
                if (isVisited(node))
                    continue;

                s.push(node);
                parent[node] = curr;
            }

        }

        if (!found)
            return nullptr;

        stack<Node *> tmp;

        while (curr != nullptr) {
            tmp.push(curr);
            curr = parent[curr];
        }

        vector<Node *> *ret = new vector<Node *>();

        while (tmp.size() != 0) {
            ret->push_back(tmp.top());
            tmp.pop();
        }

        return ret;
    }

    static vector<Node *> *BFTRec(Graph *graph) {
        initializeVisited();

        unordered_set<Node *> nodes = graph->getAllNodes();

        vector<Node *> *ret = new vector<Node *>();

        for (Node * const& n : nodes) {
            if (isVisited(n))
                continue;
            
            vector<Node *> *vec = new vector<Node *>();
            vec->push_back(n);
            setVisited(n);
            vector<Node *> *bft = BFTRec_(vec);

            copy(bft->begin(), bft->end(), back_inserter(*ret));
        }

        return ret;
    }

    static vector<Node *> *BFTIter(Graph *graph) {
        initializeVisited();

        unordered_set<Node *> nodes = graph->getAllNodes();

        vector<Node *> *ret = new vector<Node *>();

        for (Node * const& n : nodes) {
            if (isVisited(n))
                continue;
            
            queue<Node *> *q = new queue<Node *>();
            q->push(n);
            
            while (q->size() != 0) {
                Node *curr = q->front();
                q->pop();

                if (!isVisited(curr)) {
                    setVisited(curr);
                    ret->push_back(curr);

                    for (Node * const& neighbor : curr->neighbors) {
                        if (!isVisited(neighbor))
                            q->push(neighbor);
                    }
                }
            }
        }

        return ret;
    }
};

unordered_map<Node *, bool> GraphSearch::visited;

#endif