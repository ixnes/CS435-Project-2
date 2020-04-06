#include "DirectedGraph.h"
#include "Graph.h"
#include "GraphSearch.h"
#include "GridGraph.h"
#include "TopSort.h"
#include "WeightedGraph.h"

#include <iostream>
#include <iterator>
#include <queue>
#include <random>

#define MIN_EDGES 0
#define MAX_EDGES 3

//#define RANDOM_SEED 0


using namespace std;

//Mersenne-twister random engine for random number generation
mt19937  mt;

///////////////////////
//
//  HELPER FUNCTIONS
//
///////////////////////

//This function just converts a number, n >= 0, to a unique series of letters
//for functions that need to generate node names on the fly
string getNodeName(int n) {
    if (n < 0)
        return "error";
    
    if (n == 0)
        return "A";

    string ret = "";

    while (n != 0) {
        ret += (char)(65 + n % 26);
        n /= 26;
    }
    
    return ret;
}

int getRandomNumber(int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

int getNumberofEdges() {
    return getRandomNumber(MIN_EDGES, MAX_EDGES);
}

void printPath(vector<Node *> *path) {
    std::cout << (*path)[0]->name;

    for (int i = 1; i < (*path).size(); i++) {
        std::cout << "->" << (*path)[i]->name;
    }

    std::cout << endl;
}

void printGridPath(vector<GridNode *> *path) {
    if (path == nullptr) {
        cout << "No path found" << endl;
        return;
    }
    std::cout << (*path)[0]->name;

    for (int i = 1; i < (*path).size(); i++) {
        std::cout << "->" << (*path)[i]->name;
    }

    std::cout << endl;
}

void printTraversal(vector<Node *> *traversal) {
    std::cout << (*traversal)[0]->name;

    for (int i = 1; i < (*traversal).size(); i++) {
        std::cout << " , " << (*traversal)[i]->name;
    }

    std::cout << endl;
}

void printDijkstra(unordered_map<WeightedNode *, int> *result) {
    for (pair<WeightedNode *, int> p : *result) {
        cout << p.first->name << ": " << p.second << endl;
    }
}

void initializeRandomNumberGenerator() {
    #ifdef RANDOM_SEED
        mt = mt19937(RANDOM_SEED);
    #else
        random_device rd;
        mt = mt19937(rd());
    #endif

}

WeightedGraph *createRandomWeightedGraph(int n) {
    WeightedGraph *ret = new WeightedGraph();

    vector<WeightedNode *> tmp;

    for (int i = 0; i < n; i++) {
        ret->addNode(getNodeName(i));
    }

    copy(ret->getAllNodes().begin(), ret->getAllNodes().end(), back_inserter(tmp));

    for (auto from = tmp.begin(); from != tmp.end(); from++) {
        int numEdges = getNumberofEdges();
        for (int j = 0; j < numEdges; j++) {
            WeightedNode *to = tmp[getRandomNumber(0, n - 1)];
            ret->addWeightedEdge(*from, to, getRandomNumber(1, 100));
        }
    }

    return ret;
}


///////////////////////
//
//  Problem 3
//
///////////////////////

//I hate how ugly this is, but it's O(n) instead of O(n^2) so...
Graph *createRandomUnweightedGraphIter(int n) {
    Graph *ret = new Graph();

    vector<Node *> tmp;

    for (int i = 0; i < n; i++) {
        ret->addNode(getNodeName(i));
    }

    copy(ret->getAllNodes().begin(), ret->getAllNodes().end(), back_inserter(tmp));

    for (auto from = tmp.begin(); from != tmp.end(); from++) {
        int numEdges = getNumberofEdges();
        for (int j = 0; j < numEdges; j++) {
            Node *to = tmp[getRandomNumber(0, n - 1)];
            ret->addUndirectedEdge(*from, to);
        }
    }

    return ret;
}

Graph *createLinkedList(int n) {
    if (n < 0) 
        return nullptr;
    
    Graph *g = new Graph();

    for (int i = 0; i < n; i++) {
        g->addNode(getNodeName(i));
    }

    unordered_set<Node *> nodes = g->getAllNodes();

    auto i = nodes.begin();
    Node *tmp = *i;
    i++;
    for ( ; i != nodes.end(); i++) {
        g->addUndirectedEdge(tmp, *i);
        tmp = *i;
    }

    return g;
}

vector<Node *> *BFTRecLinkedList() {
    return GraphSearch::BFTRec(createLinkedList(10000));
}

vector<Node *> *BFTIterLinkedList() {
    return GraphSearch::BFTIter(createLinkedList(10000));
}

///////////////////////
//
//  Problem 4
//
///////////////////////

DirectedGraph *createRandomDAGIter(int n) {
    DirectedGraph *ret = new DirectedGraph();

    vector<Node *> tmp;

    for (int i = 0; i < n; i++) {
        ret->addNode(getNodeName(i));
    }

    copy(ret->getAllNodes().begin(), ret->getAllNodes().end(), back_inserter(tmp));

    for (int i = 0; i < tmp.size(); i++) {
        int numEdges = getNumberofEdges();
        for (int j = 0; j < numEdges; j++) {
            int r = getRandomNumber(i+1, (n + MAX_EDGES) - 1);
            if (r >= n)
                continue;
            ret->addDirectedEdge(tmp[i], tmp[r]);
        }
    }

    return ret;
}

///////////////////////
//
//  Problem 5
//
///////////////////////

WeightedGraph *createRandomCompleteWeightedGraph(int n) {
    WeightedGraph *ret = new WeightedGraph();

    vector<WeightedNode *> tmp;

    for (int i = 0; i < n; i++) {
        ret->addNode(getNodeName(i));
    }

    copy(ret->getAllNodes().begin(), ret->getAllNodes().end(), back_inserter(tmp));

    for (auto from = tmp.begin(); from != tmp.end(); from++) {
        for (auto to = tmp.begin(); to != tmp.end(); to++) {
            if (*from != *to)
                ret->addWeightedEdge(*from, *to, getRandomNumber(1, 100));
        }
    }

    return ret;
}

WeightedGraph *createWeightedLinkedList(int n) {
    if (n < 0) 
        return nullptr;
    
    WeightedGraph *g = new WeightedGraph();

    for (int i = 0; i < n; i++) {
        g->addNode(getNodeName(i));
    }

    unordered_set<WeightedNode *> nodes = g->getAllNodes();

    auto i = nodes.begin();
    WeightedNode *tmp = *i;
    i++;
    for ( ; i != nodes.end(); i++) {
        g->addWeightedEdge(tmp, *i, 1);
        tmp = *i;
    }

    return g;
}


/*struct CompareNode {
    bool operator()(pair<WeightedNode *, int> const& a, pair<WeightedNode *, int> const& b) {
        return a.second < b.second;
    }
};*/

WeightedNode *getNextMinNode(unordered_map<WeightedNode *, bool> &visited, unordered_map<WeightedNode *, int> &distance) {
    WeightedNode *minNode = nullptr;
    int minDist = 0;

    for (pair<WeightedNode *, bool> p : visited) {
        if (!p.second) {
            if (minNode == nullptr) {
                minNode = p.first;
                minDist = distance[p.first];
            }
            else if (distance[p.first] < minDist) {
                minNode = p.first;
                minDist = distance[p.first];
            }
        }
    }

    return minNode;
}

unordered_map<WeightedNode *, int> *dijkstras(WeightedNode *start) {
    unordered_map<WeightedNode *, int> *distance = new unordered_map<WeightedNode *, int>();
    unordered_map<WeightedNode *, WeightedNode *> parent;
    unordered_map<WeightedNode *, bool> visited;

    //priority_queue<pair<WeightedNode *, int>, vector<pair<WeightedNode *, int>>, CompareNode> q;

    (*distance)[start] = 0;
    parent[start] = nullptr;
    visited[start] = false;
    //q.push(make_pair(start, distance[start]));

    /*while (q.size() != 0) {
        WeightedNode *n = q.top().first;
        q.pop();*/

    WeightedNode *n;
    while ( (n = getNextMinNode(visited, *distance)) != nullptr ) {
        visited[n] = true;

        for (pair<WeightedNode *, int> p : n->neighbors) {
            if (visited.find(p.first) != visited.end() || !visited[p.first]) {
                int dist = (*distance)[n] + p.second;
                if (distance->find(p.first) == distance->end()) {
                    (*distance)[p.first] = dist;
                    parent[p.first] = n;
                    //q.push(make_pair(p.first, dist));
                    visited[p.first] = false;
                }
                else if (dist < (*distance)[p.first]) {
                    (*distance)[p.first] = dist;
                    parent[p.first] = n;
                }
            }
        }
    }

    return distance;
}

///////////////////////
//
//  Problem 6
//
///////////////////////

GridGraph *createRandomGridGraph(int n) {
    GridGraph *gg = new GridGraph();
    
    for (int x = 0; x <= n; x++) {
        for (int y = 0; y <= n; y++) {
            gg->addNode(x, y, "(" + to_string(x) + ", " + to_string(y) + ")");
        }
    }
    
    unordered_set<GridNode *> nodes = gg->getAllNodes();

    for (GridNode * const& a: nodes) {
        for (GridNode * const& b: nodes) {
            //So because I did this one with a lazy, iterate over the whole
            //graph n times way, I had to do a tiny bit of math to get the
            //50% chance of being connected to the neighbor thing right.
            //Theres a 2x(1-x) chance of one connecting and the other not
            //and an x^2 chance of both choosing to connect.
            //If you do the math the solution of x in the 0 <= x <= 1 
            //range (for a probability) is 0.29289...
            //The approximation 0.293 gives a 0.500151 chance of
            //two neighbors being connected, which should be close enough
            //to 0.5 for this toy implementation
            if (getRandomNumber(1, 1000) < 293) {
                gg->addUndirectedEdge(a, b);
            }
        }
    }

    return gg;
}

int getManhattanDistance(GridNode *src, GridNode *dst) {
    int xDiff = src->x - dst->x;
    if (xDiff < 0)
        xDiff *= -1;

    int yDiff = src->y - dst->y;
    if (yDiff < 0)
        yDiff *= -1;

    return xDiff + yDiff;
}

GridNode *getNextMinNodeAStar(unordered_map<GridNode *, bool> &visited, unordered_map<GridNode *, int> &distance, GridNode *dest) {
    GridNode *minNode = nullptr;
    int minDist = 0;

    for (pair<GridNode *, bool> p : visited) {
        if (!p.second) {
            if (minNode == nullptr) {
                minNode = p.first;
                minDist = distance[p.first] + getManhattanDistance(p.first, dest);
            }
            else if (distance[p.first] < minDist) {
                minNode = p.first;
                minDist = distance[p.first] + getManhattanDistance(p.first, dest);
            }
        }
    }

    return minNode;
}

vector<GridNode *> *astar(GridNode *sourceNode, GridNode *destNode) {
    unordered_map<GridNode *, int> distance;
    unordered_map<GridNode *, GridNode *> parent;
    unordered_map<GridNode *, bool> visited;

    //priority_queue<pair<WeightedNode *, int>, vector<pair<WeightedNode *, int>>, CompareNode> q;

    distance[sourceNode] = 0;
    parent[sourceNode] = nullptr;
    visited[sourceNode] = false;
    //q.push(make_pair(start, distance[start]));

    /*while (q.size() != 0) {
        WeightedNode *n = q.top().first;
        q.pop();*/

    GridNode *n;
    while ( (n = getNextMinNodeAStar(visited, distance, destNode)) != nullptr ) {
        visited[n] = true;

        for (GridNode * m : n->neighbors) {
            if (visited.find(m) != visited.end() || !visited[m]) {
                int dist = distance[n] + 1;
                if (distance.find(m) == distance.end()) {
                    distance[m] = dist;
                    parent[m] = n;
                    //q.push(make_pair(p.first, dist));
                    visited[m] = false;
                }
                else if (dist < distance[m]) {
                    distance[m] = dist;
                    parent[m] = n;
                }
            }
        }
    }

    if (visited.find(destNode) == visited.end())
        return nullptr;

    stack<GridNode *> s;
    GridNode *tmp = destNode;

    while (tmp != nullptr) {
        s.push(tmp);
        tmp = parent[tmp];
    }

    vector<GridNode *> *ret = new vector<GridNode *>();

    while (s.size() != 0) {
        ret->push_back(s.top());
        s.pop();
    }

    return ret;
}

int main() {
    initializeRandomNumberGenerator();

    //Problem 3b
    cout << "Graph: " << endl;
    createRandomUnweightedGraphIter(10)->printGraph();

    //problem 3c
    cout << endl << "Linked list: " << endl;
    createLinkedList(10)->printGraph();

    //Problem 3d
    Graph *g = createRandomUnweightedGraphIter(26);
        cout << endl << "Graph: " << endl;
    g->printGraph();

    unordered_set<Node *> nodes = g->getAllNodes();

    Node *start = g->getNode("A");
    Node *end = g->getNode("Z");

    vector<Node *> *path = GraphSearch::DFSRec(start, end);

    if (path == nullptr)
        cout << "No path found" << endl;
    else 
        printPath(path);

    //Problem 3e
    g = createRandomUnweightedGraphIter(26);
    cout << endl << "Graph: " << endl;
    g->printGraph();

    nodes = g->getAllNodes();

    start = g->getNode("A");
    end = g->getNode("Z");

    path = GraphSearch::DFSIter(start, end);

    if (path == nullptr)
        cout << "No path found" << endl;
    else 
        printPath(path);

    //Problem 3f
    g = createRandomUnweightedGraphIter(26);
    cout << endl << "Graph: " << endl;
    g->printGraph();

    vector<Node *> *traversal = GraphSearch::BFTRec(g);

    printTraversal(traversal);

    //Problem 3g
    g = createRandomUnweightedGraphIter(26);
        cout << endl << "Graph: " << endl;
    g->printGraph();

    traversal = GraphSearch::BFTIter(g);

    printTraversal(traversal);

    //Problem 3h
    BFTIterLinkedList();
    cout << "Iter done" << endl;

    //Problem 3i
    BFTRecLinkedList();
    cout << "Rec done" << endl;

    //Problem 4c
    DirectedGraph *dg = createRandomDAGIter(26);
    cout << endl << "Directed graph: " << endl;
    dg->printGraph();

    //Problem 4d
    dg = createRandomDAGIter(1000);
    cout << endl << "Directed graph: " << endl;
    dg->printGraph();
    vector<Node *> *topsort = TopSort::Kahns(dg);
    printTraversal(topsort);

    //Problem 4e
    dg = createRandomDAGIter(1000);
    cout << endl << "Directed graph: " << endl;
    dg->printGraph();
    topsort = TopSort::mDFS(dg);
    printTraversal(topsort);

    //Problem 5c
    WeightedGraph *wg = createRandomCompleteWeightedGraph(10);
    cout << endl << "Weighted graph: " << endl;
    wg->printGraph();

    //Problem 5d
    wg = createWeightedLinkedList(10);
    cout << endl << "Weighted graph: " << endl;
    wg->printGraph();

    //Problem 5e
    wg = createRandomWeightedGraph(10);
    cout << endl << "Weighted graph: " << endl;
    wg->printGraph();
    unordered_map<WeightedNode *, int> *result = dijkstras(wg->getNode("A"));
    printDijkstra(result);

    //Problem 6b
    GridGraph *gg = createRandomGridGraph(4);
    //gg->printGraphDBG();
    cout << endl << "Grid graph: " << endl;
    gg->printGraph();

    //Problem 6d
    int gridsize = 100;
    gg = createRandomGridGraph(gridsize);
    //gg->printGraphDBG();
    cout << endl << "Grid graph: " << endl;
    gg->printGraph();
    vector<GridNode *> *gpath = astar(gg->getNode("(0, 0)"), gg->getNode("(" + to_string(gridsize) + ", " + to_string(gridsize) + ")"));
    printGridPath(gpath);
}