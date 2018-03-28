//
//  graph.cpp
//  dijkstra
//
//  Created by Mikaela Schaefer on 3/28/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <set>
#include <limits>

//Graph Class
//Vertices are represented by ints
//Weights can be any type (The T argument in the template declaration)

template <typename T>
class Graph {
private:
    Graph() noexcept : numVertices(0), numEdges(0), adjacent(nullptr){ ; };
    int numVertices;
    int numEdges;
    struct adjList;                         //Poppin PIMPLs
    std::shared_ptr<adjList> adjacent;      //Poppin PIMPLs
    
public:
    //Overloaded Constructor
    Graph(int v) noexcept;
    //Compiler Generated Destructor should work fine
    ~Graph() noexcept = default;
    //Add Edge
    void AddEdge(int u, int v, T w) noexcept;
    //Find Shortest Path from Vertex S
    void ShortestPath(int s);
    
};

//PIMPL Idiom
template <typename T>
struct Graph<T>::adjList {
    std::vector<std::list<std::pair<T, int> > > adj;
};

//Graph Implementation

//Constructor
template <typename T>
Graph<T>::Graph(int v) noexcept : numVertices(v), numEdges(0) {
    adjacent = std::make_unique<struct adjList>();
    adjacent->adj.resize(v);
}

//Add an edge between u and v with weight W to the Graph
//Pairs are stored weight, destination Vertex to allow for comparison by first key
template<typename T>
void Graph<T>::AddEdge(int u, int v, T w) noexcept {
    adjacent->adj[u].push_back(std::make_pair(w, v));
    adjacent->adj[v].push_back(std::make_pair(w, u));
    numEdges += 2;
}

//Find Shortest Path from S
//AKA DIJKSTRA's
template<typename T>
void Graph<T>::ShortestPath(int s){
    const auto INF = std::numeric_limits<T>::max();
    //Make A set to hold processed vertices
    //Every item of the set is a pair
    std::set< std::pair<T, int> > processed;
    std::vector<T> weights(numVertices, INF);
    
    //Process the source vertex
    processed.insert(std::make_pair(0, s));
    //make its distance 0
    weights[s] = 0;
    
    //while set isn't empty
    while(!processed.empty()){
        //Extract min dist vertex u
        std::pair<T, int> temp = *(processed.begin());
        
        //Remove u from Processed
        processed.erase(processed.begin());
        
        //Get Vertex Index
        auto u = temp.second;
        
        //get iterator to u's adjacency list
        typename std::list<std::pair<T, int> >::iterator it = adjacent->adj[u].begin();
        typename std::list<std::pair<T, int> >::iterator ite = adjacent->adj[u].end();
      
        // For each adj vertex v
        for (; it != ite; ++it){
            //Get Vertex Index and Weight (note weight is not int)
            auto v = (*it).second;
            auto v_w = (*it).first;
            
            //If there is a path to v through u
            if (weights[v] > weights[u] + v_w){
                //If distance of V isn't INF, then we must have encountered it already
                //So It's already in our processed set - We must remove and reinsert with the updated distance
                if (weights[v] != INF){
                    processed.erase(processed.find(std::make_pair(weights[v], v)));
                }
                weights[v] = weights[u] + v_w;
                processed.insert(std::make_pair(weights[v], v));
            }
        }
        
        
    }
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < numVertices; ++i){
        std::cout << i << "   " << weights[i] << std::endl;
    }
    
}






