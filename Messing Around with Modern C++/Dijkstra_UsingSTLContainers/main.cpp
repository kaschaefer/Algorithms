//
//  main.cpp
//  dijkstra
//Goal: Compare times of Dijkstra's using Set vs. PQ
//
//  Created by Mikaela Schaefer on 3/28/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//

#include <iostream>
#include <limits>
#include "graph.cpp"
#include <ctime>

#define V 9

int main()
{
    /* Let us create the example graph discussed above */
    Graph<int> theIntGraph(V);
    
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
    clock_t begin = clock();
    theIntGraph.ShortestPath(0);
    clock_t set = clock();
    theIntGraph.ShortestPathPQ(0);
    clock_t end = clock();
    std::cout << "Time using Set: " << (set - begin) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    std::cout << "Time using PQ: " << (end - set) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    
    begin = clock();
    //For all paths
    for (int i =0; i < V; ++i){
        theIntGraph.ShortestPath(i);
    }
    set = clock();
    for (int i =0; i < V; ++i){
        theIntGraph.ShortestPathPQ(i);
    }
    end = clock();
    
    std::cout << "Time using Set: " << (set - begin) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    std::cout << "Time using PQ: " << (end - set) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    
    return 0;
}

