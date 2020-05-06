//
// Created by amory on 4/29/2020.
//

#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <chrono>
#include "graph.h"

using namespace std;
int main(){
    ifstream ifile;

    ifile.open("graphData3.txt");

    if (ifile.fail()) {
        cout << "file not open" << endl;
    }
    else {
        char buffer[50];
        ifile.getline(buffer, 50, '\n'); //takes in num at the top of the file
        string numVertices = buffer;

        string::size_type sz;
        int numV = stoi(numVertices, &sz); //converts string to integer

        graph g(numV);

        ifile.getline(buffer, 50, '\n'); //takes in num at the top of the file
        string numEdges = buffer;

        int numE = stoi(numEdges, &sz);

        for (int i = 0; i < numE; i++) {
            buffer[50];

            string::size_type sz;

            ifile.getline(buffer, 50, ',');
            int root = stoi(buffer, &sz);

            //cout << root << " ";

            ifile.getline(buffer, 50, '\n');
            int dest = stoi(buffer, &sz);

            //cout << dest << endl;

            g.addEdge(root, dest);
        }

        cout << "DEPTH FIRST SEARCH IMPLEMENTATION" << endl;
        auto t1 = chrono::high_resolution_clock::now();
        g.DFS();
        auto t2 = chrono::high_resolution_clock::now();
        auto Time = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
        cout << "time to analyze: " << Time << "microseconds" << endl;
        cout << endl;

        cout << "KOSARAJU'S ALGORITHM" << endl;
        t1 = chrono::high_resolution_clock::now();
        g.Kosajaru();
        t2 = chrono::high_resolution_clock::now();
        Time = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
        cout << "time to analyze: " << Time << "microseconds" << endl;
        cout << endl;

        cout << "TARJAN'S ALGORITHM" << endl;
        t1 = chrono::high_resolution_clock::now();
        g.Tarjan();
        t2 = chrono::high_resolution_clock::now();
        Time = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
        cout << "time to analyze: " << Time << "microseconds" << endl;
    }
    return 0;
}

