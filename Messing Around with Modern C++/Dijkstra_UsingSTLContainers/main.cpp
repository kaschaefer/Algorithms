//
//  main.cpp
//  dijkstra
//
//  Created by Mikaela Schaefer on 3/28/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//

#include <iostream>
#include <limits>
#include "graph.cpp"

#define V 9

int main()
{
    /* Let us create the example graph discussed above */
    Graph<int> theIntGraph(V);
    Graph<double> theDoubGraph(V);
    Graph<float> theFloatGraph(V);
    
    theIntGraph.AddEdge(0, 1, 4);
    theIntGraph.AddEdge(0, 7, 8);
    theIntGraph.AddEdge(1, 2, 8);
    theIntGraph.AddEdge(1, 7, 11);
    theIntGraph.AddEdge(2, 3, 7);
    theIntGraph.AddEdge(2, 8, 2);
    theIntGraph.AddEdge(2, 5, 4);
    theIntGraph.AddEdge(3, 4, 9);
    theIntGraph.AddEdge(3, 5, 14);
    theIntGraph.AddEdge(4, 5, 10);
    theIntGraph.AddEdge(5, 6, 2);
    theIntGraph.AddEdge(6, 7, 1);
    theIntGraph.AddEdge(6, 8, 6);
    theIntGraph.AddEdge(7, 8, 7);
    
    theDoubGraph.AddEdge(0, 1, 4);
    theDoubGraph.AddEdge(0, 7, 8);
    theDoubGraph.AddEdge(1, 2, 8);
    theDoubGraph.AddEdge(1, 7, 11);
    theDoubGraph.AddEdge(2, 3, 7);
    theDoubGraph.AddEdge(2, 8, 2);
    theDoubGraph.AddEdge(2, 5, 4);
    theDoubGraph.AddEdge(3, 4, 9);
    theDoubGraph.AddEdge(3, 5, 14);
    theDoubGraph.AddEdge(4, 5, 10);
    theDoubGraph.AddEdge(5, 6, 2);
    theDoubGraph.AddEdge(6, 7, 1);
    theDoubGraph.AddEdge(6, 8, 6);
    theDoubGraph.AddEdge(7, 8, 7);
    
    theFloatGraph.AddEdge(0, 1, 4);
    theFloatGraph.AddEdge(0, 7, 8);
    theFloatGraph.AddEdge(1, 2, 8);
    theFloatGraph.AddEdge(1, 7, 11);
    theFloatGraph.AddEdge(2, 3, 7);
    theFloatGraph.AddEdge(2, 8, 2);
    theFloatGraph.AddEdge(2, 5, 4);
    theFloatGraph.AddEdge(3, 4, 9);
    theFloatGraph.AddEdge(3, 5, 14);
    theFloatGraph.AddEdge(4, 5, 10);
    theFloatGraph.AddEdge(5, 6, 2);
    theFloatGraph.AddEdge(6, 7, 1);
    theFloatGraph.AddEdge(6, 8, 6);
    theFloatGraph.AddEdge(7, 8, 7);
    
    theIntGraph.ShortestPath(0);
    theDoubGraph.ShortestPath(0);
    theFloatGraph.ShortestPath(0);
    
    return 0;
}

