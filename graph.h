//
// Created by amory on 4/25/2020.
//

#ifndef FINALPROJECT_GRAPH_H
#define FINALPROJECT_GRAPH_H

#include <list>
#include <stack>
#include <vector>

using namespace std;
class graph{
private:
    int numVertices;
    list <int> *adjacencyList;

    stack<int> Stack;
    bool *checked;

public:
    graph(int);
    ~graph();

    void addEdge(int, int);

    void DFS();
    void DFSCheck(int);

    void Kosajaru();
    void calcTime(int);
    graph transpose();

    void Tarjan();
    void TSCC(int, int[], int[]);
};


#endif //FINALPROJECT_GRAPH_H
