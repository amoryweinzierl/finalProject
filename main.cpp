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
    ofstream ofile;

    //change to graphData1.txt to run graph data (change output file to results1.txt)
    //change to graphData2.txt to run graph data (change output file to results2.txt)
    ifile.open("graphData3.txt");
    ofile.open("results3txt");

    if (ifile.fail()) {
        cout << "input file not open" << endl;
    }
    //goes through and gets all edges from graphs
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

            ifile.getline(buffer, 50, '\n');
            int dest = stoi(buffer, &sz);

            g.addEdge(root, dest);
        }
        ifile.close();

        if(ofile.fail()){
            cout << "output file not open" << endl;
        }
        else {
            ofile << "DEPTH FIRST SEARCH IMPLEMENTATION" << endl;
            auto t1 = chrono::high_resolution_clock::now();
            g.DFS(ofile);
            auto t2 = chrono::high_resolution_clock::now();
            auto Time = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
            ofile << "time to analyze: " << Time << "microseconds" << endl;
            ofile << endl;

            ofile << "KOSARAJU'S ALGORITHM" << endl;
            t1 = chrono::high_resolution_clock::now();
            g.Kosajaru(ofile);
            t2 = chrono::high_resolution_clock::now();
            Time = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
            ofile << "time to analyze: " << Time << "microseconds" << endl;
            ofile << endl;

            ofile << "TARJAN'S ALGORITHM" << endl;
            t1 = chrono::high_resolution_clock::now();
            g.Tarjan(ofile);
            t2 = chrono::high_resolution_clock::now();
            Time = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
            ofile << "time to analyze: " << Time << "microseconds" << endl;

            ofile.close();
        }
    }
    return 0;
}

