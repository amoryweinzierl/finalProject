//
// Created by amory on 4/25/2020.
//

#ifndef FINALPROJECT_GRAPH_H
#define FINALPROJECT_GRAPH_H

#include <list>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;
class graph{
private:
    int numVertices;
    list <int> *adjacencyList;

    stack<int> Stack;
    bool *checked;

    bool DFSTracker;
public:
    graph(int);
    ~graph();

    void addEdge(int, int);

    void DFS(ofstream&);
    void DFSCheck(int, ofstream&);
    void DFSCheck(int, bool[], ofstream&);

    void Kosajaru(ofstream&);
    void calcTime(int, bool[]);

    void Tarjan(ofstream&);
    void TSCC(int, int[], int[], ofstream&);
};


#endif //FINALPROJECT_GRAPH_H
