//
//  main.cpp
//  Prims
//
//  Created by Mikaela Schaefer on 3/27/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//
#include "Prims.cpp"
#include <stdio.h>

using namespace std;

int main(){
    int numVertices;
    Graph<int> theGraph;
    cout << "Enter num vertices ";
    cin >> numVertices;
    int i = 0;
    bool treeIsWorking = true;
    while (i < numVertices && treeIsWorking){
        int pushVal = 0;
        cin >> pushVal;
        if (!theGraph.AddVertex(pushVal)){
            treeIsWorking = false;
        }
        i++;
    }
    int numEdges;
    cout << "How many edges are there? ";
    cin >> numEdges;
    cout << "Enter edges one at a time in following format: Src_Node, Dest_Node, Weight " << endl;
    int dest;
    int src;
    double w;
    i=0;
    while (i < numEdges){
        cin >> src;
        cin >> dest;
        cin >> w;
        theGraph.AddEdge(src, dest, w);
        i++;
    }
    Graph<int> PrimGraph;
    //theGraph.clone(PrimGraph);
    //Okay Now A Graph is Made -- Run Prim's First?
    PrimsAlg<int>(theGraph, 0);
    
    return 0;
}

