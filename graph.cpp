//
// Created by amory on 4/25/2020.
//

#include "graph.h"
#include <iostream>

using namespace std;
//takes in parameter number of vertices that helps create array for vertices
//creates adjacency list of arrays
graph::graph(int vertices) {
    numVertices = vertices;
    adjacencyList = new list<int>[numVertices];
    checked = new bool[numVertices];
    DFSTracker = 0;
}

graph::~graph(){
    delete[] adjacencyList;
    delete[] checked;
}

//add directed edge, so only added one way
void graph::addEdge(int v1, int v2) {
    adjacencyList[v1].push_back(v2);
}

//depth first search
//referenced https://www.techiedelight.com/check-given-graph-strongly-connected-not/
void graph::DFS(ofstream& ofile){
    //initializes every index in checked to false
    for(int i = 0; i < numVertices; i++){
        checked[i] = false;
    }

    //checks every index in checked
    //if false, run dfs to visit edge and find adjacent edges
    for(int j = 0; j < numVertices; j++){
        if(checked[j] == false){
            DFSCheck(j, ofile);
            ofile << endl;
        }
    }
}

//depth first search
//checks if strongly connected
//referenced https://www.techiedelight.com/check-given-graph-strongly-connected-not/
void graph::DFSCheck(int vertex, ofstream& ofile) {
    //marks vertex and true
    checked[vertex] = true;
        ofile << vertex << " ";

    //check all adjacent vertices to vertex in adjacencyList
    list<int>::iterator iter;
    for (iter = adjacencyList[vertex].begin(); iter != adjacencyList[vertex].end(); iter++)
        if (!checked[*iter])
            //if not checked, recursively call DFSCheck
            DFSCheck(*iter, ofile);
}

//depth first search
//checks if strongly connected
//redefinition that takes in a local bool array instead of utilizing class variable
//used for kosaraju's algorithm
//referenced https://www.techiedelight.com/check-given-graph-strongly-connected-not/
void graph::DFSCheck(int vertex, bool localCheck[], ofstream &ofile) {
    //marks vertex and true
    localCheck[vertex] = true;
    if(DFSTracker == 0) {
        ofile << vertex << " ";
    }

    //check all adjacent vertices to vertex in adjacencyList
    list<int>::iterator iter;
    for (iter = adjacencyList[vertex].begin(); iter != adjacencyList[vertex].end(); iter++) {
        if (!localCheck[*iter]) {
            //if not checked, recursively call DFSCheck
            DFSCheck(*iter, localCheck, ofile);
        }
    }
    if(DFSTracker == 1) {
        Stack.push(vertex);
    }
}

//kosaraju's algorithm
//referenced https://cp-algorithms.com/graph/strongly-connected-components.html
//referenced https://www.geeksforgeeks.org/strongly-connected-components/
//referenced https://rosettacode.org/wiki/Kosaraju#C.2B.2B
void graph::Kosajaru(ofstream& ofile){
    //sets boolean that first round of dfs hasn't occurred yet
    DFSTracker = 1;
    //local checked boolean array
    bool *localCheck = new bool[numVertices];

    //initializes all vertices in checked to false
    for(int i = 0; i < numVertices; i++) {
        localCheck[i] = false;
    }

    // Fill vertices in stack according to their finishing times
    for(int j = 0; j < numVertices; j++) {
        if (localCheck[j] == false) {
            DFSCheck(j, localCheck, ofile);
        }
    }
    //first round down, second round now
    DFSTracker = 0;

    //create graph object for transposed graph
    graph transposedGraph(numVertices);

    //creates transpose graph
    //check for all vertices
    for (int i = 0; i < numVertices; i++){
        list<int>::iterator iter;
        //check all adjacent vertexes in adjacencyList
        for(iter = adjacencyList[i].begin(); iter != adjacencyList[i].end(); iter++){
            transposedGraph.adjacencyList[*iter].push_back(i);
        }
    }

    //reset all vertices in to false
    for(int i = 0; i < numVertices; i++) {
        localCheck[i] = false;
    }

    //while stack not empty
    while (!Stack.empty()){
        //get top vertex from stack and assign to variable vertex, then pop element off stack
        int vertex = Stack.top();
        Stack.pop();

        //get SCCs of vertex
        if (localCheck[vertex] == false){
            transposedGraph.DFSCheck(vertex, localCheck, ofile);
            ofile << endl;
        }
    }
}

//tarjan's algorithm
//referenced https://www.programming-algorithms.net/article/44220/Tarjan's-algorithm
//referenced https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
//referenced https://www.youtube.com/watch?v=wUgWX0nc4NY
void graph::Tarjan(ofstream& ofile) {
    //only one pass of dfs required
    DFSTracker = 0;
    //times is an int pointer that points to array of ints that holds time to vertices
    int *ids = new int[numVertices];
    //lowlink is int pointer that points to array of ints that holds vertices with lowest time
    int *lowlink = new int[numVertices];

    //initializes all arrays
    for(int i = 0; i < numVertices; i++){
        checked[i] = false;
        ids[i] = -1;
        lowlink[i] = -1;
    }

    //for all vertices in lowlink, if time not assigned
    //time assigned through call to TSCC
    for(int j = 0; j <numVertices; j++){
        if(lowlink[j] == -1){
            TSCC(j, ids, lowlink, ofile);
        }
    }
}

//tarjan's algorithm
//referenced https://www.programming-algorithms.net/article/44220/Tarjan's-algorithm
//referenced https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
//referenced https://www.youtube.com/watch?v=wUgWX0nc4NY
void graph::TSCC(int vertex, int ids[], int lowlink[], ofstream& ofile){
    //initialize static int time
    static int initial = 0;

    //initializes ids and lowlink to be same value
    ids[vertex] = lowlink[vertex] = ++initial;
    //push vertex to stack
    Stack.push(vertex);
    //vertex is in stack
    checked[vertex] = true;

    //depth first search
    list<int>::iterator iter;
    //goes through all vertices adjacent to vertex in adjacecy list
    for (iter = adjacencyList[vertex].begin(); iter != adjacencyList[vertex].end(); iter++){
        //adjacentVertex set
        int adjVertex = *iter;
        //if time hasn't been set
        if (ids[adjVertex] == -1){
            //recursively calls TSCC
            TSCC(adjVertex, ids, lowlink, ofile);
            //checks if vertex and adjVertex are connected to each other in subtree by checking stack
            //then takes min of the twos lowlink
            lowlink[vertex]  = min(lowlink[vertex], lowlink[adjVertex]);
        }

        //if adjVertex in stack
        else if (checked[adjVertex] == true) {
            //updates value of vertex in lowlink
            lowlink[vertex] = min(lowlink[vertex], ids[adjVertex]);
        }
    }
    int tempVert;
    //if lowlink and id are same, SCC done
    if (lowlink[vertex] == ids[vertex]){
        //pop all vertexes in SCC off stack
        while (Stack.top() != vertex){
            //pop stack
            tempVert = Stack.top();
            ofile << tempVert << " ";

            //take tempVert off stack
            checked[tempVert] = false;
            Stack.pop();
        }

        //tempVert is vertex
        tempVert = Stack.top();
        ofile << tempVert << endl;

        //take off stack
        checked[tempVert] = false;
        Stack.pop();
    }
}