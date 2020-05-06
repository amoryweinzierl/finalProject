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
void graph::DFS(){
    //initializes every index in checked to false
    for(int i = 0; i < numVertices; i++){
        checked[i] = false;
    }

    //checks every index in checked
    //if false, run dfs to visit edge and find adjacent edges
    for(int j = 0; j < numVertices; j++){
        if(checked[j] == false){
            DFSCheck(j);
            cout << endl;
        }
    }
}

//depth first search
void graph::DFSCheck(int v) {
    // Mark the current node as visited and print it
    checked[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator iter;
    for (iter = adjacencyList[v].begin(); iter != adjacencyList[v].end(); iter++)
        if (!checked[*iter])
            DFSCheck(*iter);
}

//kosaraju's algorithm
void graph::Kosajaru(){
    //initializes all vertices in checked to false
    for(int i = 0; i < numVertices; i++)
        checked[i] = false;

    // Fill vertices in stack according to their finishing times
    for(int j = 0; j < numVertices; j++)
        if(checked[j] == false)
            calcTime(j);

    //get transposed graph
    graph transposedGraph = transpose();

    //reset all vertices in to false
    for(int i = 0; i < numVertices; i++)
        checked[i] = false;

    //while stack not empty
    while (!Stack.empty()){
        //get top vertex from stack and assign to variable vertex, then pop element off stack
        int vertex = Stack.top();
        Stack.pop();

        //get SCCs of vertex
        if (checked[vertex] == false){
            transposedGraph.DFSCheck(vertex);
            cout << endl;
        }
    }
}

//kosaraju's algorithm
void graph::calcTime(int vertex){
    //mark vertex as checked
    checked[vertex] = true;

    //check all adjacent vertexes to vertex in adjacency list
    list<int>::iterator iter;
    for(iter = adjacencyList[vertex].begin(); iter != adjacencyList[vertex].end(); iter++)
        if(checked[*iter] == false)
            //recursively call calcTime
            calcTime(*iter);

    //push vertex onto stack
    Stack.push(vertex);
}

//kosaraju's algorithm
graph graph::transpose(){
    //create graph object for transposed graph
    graph transposedGraph(numVertices);

    //check for all vertices
    for (int i = 0; i < numVertices; i++){
        list<int>::iterator iter;
        //check all adjacent vertexes in adjacencyList
        for(iter = adjacencyList[i].begin(); iter != adjacencyList[i].end(); iter++){
            transposedGraph.adjacencyList[*iter].push_back(i);
        }
    }
    //returned fully transposed graph
    return transposedGraph;
}

void graph::Tarjan() {
    //times is an int pointer that points to array of ints that holds time to vertices
    int *times = new int[numVertices];
    //minVertex is int pointer that points to array of ints that holds vertices with lowest time
    int *minVertex = new int[numVertices];

    //initializes all arrays
    for(int i = 0; i < numVertices; i++){
        checked[i] = false;
        times[i] = -1;
        minVertex[i] = -1;
    }

    //for all vertices in minVertex, if time not assigned
    //time assigned through call to TSCC
    for(int j = 0; j <numVertices; j++){
        if(minVertex[j] == -1){
            TSCC(j, times, minVertex);
        }
    }
}

void graph::TSCC(int vertex, int times[], int minVertex[]){
    //initialize static int time
    static int time = 0;

    //initializes times and minVertex
    times[vertex] = minVertex[vertex] = ++time;
    //push vertex to stack
    Stack.push(vertex);
    //vertex is in stack
    checked[vertex] = true;

    list<int>::iterator iter;
    //goes through all vertices adjacent to vertex in adjacecy list
    for (iter = adjacencyList[vertex].begin(); iter != adjacencyList[vertex].end(); iter++){
        //adjacentVertex set
        int adjVertex = *iter;
        //if time hasn't been set
        if (times[adjVertex] == -1){
            //recursively calls TSCC
            TSCC(adjVertex, times, minVertex);
            //checks if vertex and adjVertex are connected to each other in subtree
            minVertex[vertex]  = min(minVertex[vertex], minVertex[adjVertex]);
        }

        //if adjVertex in stack
        else if (checked[adjVertex] == true) {
            //updates value of vertex in minVertex
            minVertex[vertex] = min(minVertex[vertex], times[adjVertex]);
        }
    }
    int tempVert;
    //if head node
    if (minVertex[vertex] == times[vertex]){
        //while vertex is not found
        while (Stack.top() != vertex){
            //pop stack
            tempVert = Stack.top();

            //print tempVert
            cout << tempVert << " ";

            //take tempVert off stack
            checked[tempVert] = false;
            Stack.pop();
        }

        //tempVert is vertex
        tempVert = Stack.top();
        //print
        cout << tempVert << endl;

        //take off stack
        checked[tempVert] = false;
        Stack.pop();
    }
}