#include "Graph.h"
#include "GraphSearch.h"

#include <iterator>
#include <iostream>
#include <random>

#define MIN_EDGES 0
#define MAX_EDGES 3


using namespace std;

//Mersenne-twister random engine for random number generation
mt19937  mt;

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

void printPath(vector<Node *> *path) {
    cout << (*path)[0]->name;

    for (int i = 1; i < (*path).size(); i++) {
        cout << "->" << (*path)[i]->name;
    }

    cout << endl;
}

void printTraversal(vector<Node *> *traversal) {
    cout << (*traversal)[0]->name;

    for (int i = 1; i < (*traversal).size(); i++) {
        cout << " , " << (*traversal)[i]->name;
    }

    cout << endl;
}

void initializeRandomNumberGenerator() {
    random_device rd;
    mt = mt19937(rd());

}

int main() {
    initializeRandomNumberGenerator();
    
    /*cout << "Graph: " << endl;
    createRandomUnweightedGraphIter(10)->printGraph();

    cout << "Linked list: " << endl;
    createLinkedList(10)->printGraph();*/

    //Graph *g = createLinkedList(10);

    /*Graph *g = createRandomUnweightedGraphIter(26);
    g->printGraph();*/

    /*unordered_set<Node *> nodes = g->getAllNodes();
    
    Node *start = g->getNode("A");
    Node *end = g->getNode("Z");

    vector<Node *> *path = GraphSearch::DFSIter(start, end);

    if (path == nullptr)
        cout << "No path found" << endl;
    else 
        printPath(path);*/
    
    /*vector<Node *> *traversal = GraphSearch::BFTIter(g);

    printTraversal(traversal);*/

    BFTIterLinkedList();
    cout << "Iter done" << endl;

    BFTRecLinkedList();
    cout << "Rec done" << endl;
}