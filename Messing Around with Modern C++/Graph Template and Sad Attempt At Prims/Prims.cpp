//
//  Prims.hpp
//  Prims
//
//  Created by Mikaela Schaefer on 3/27/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//


#ifndef Prims_hpp
#define Prims_hpp
#include "graphTemplate.cpp"
#include <stdio.h>
#include <vector>
#include <queue>


template <class T>
class myComparator{
public:
    inline T operator() (const Edge<T>& edge1, const Edge<T>& edge2){ return edge1.weight > edge2.weight;};
};

template <class T>
struct PrimHelper {
    T sourceIndex;             //Source Vertex
    int size;
    std::vector<T> Distances;   //Distance from Source to Vertex
    std::vector<T> Edges;       //Which Vertex in the Tree is each vertex "closest" to
    std::vector<T> Visited;  //List of Visited Nodes
    std::priority_queue<Edge<T>, std::vector<Edge<T> >,  myComparator<T> > UnVisited;  //Min Heap for Edges
};
              


template <class T>
void PrimsAlg(Graph<T>& outputGraph, T inputIndex){
    PrimHelper<T> ph;
    ph.sourceIndex = inputIndex;
    ph.size = 0;
    //Get Vertices
    vector<Node<T> > vertices(outputGraph.getVertexSet());
    //Get Source Index
    //Initialize Arrays
    std::fill(ph.Edges.begin(), ph.Edges.end()+vertices.size(),-100);
    std::fill(ph.Distances.begin(), ph.Distances.end()+vertices.size(),-100);
    ph.Visited.resize(vertices.size());
    
    ph.Distances[inputIndex] = 0;
    //Add All Edges From Source Index to Min Heap
    //for s in vector[i].adjacency
    for (auto &s : vertices[ph.sourceIndex].adjacent){
        ph.UnVisited.push(s);
    }
    //Get Min Edge from Source
    if (ph.UnVisited.empty() == false){
        auto weight = ph.UnVisited.top().weight;
        auto vertex = ph.UnVisited.top().GetDest()->getData();
        ph.Distances[vertex] = weight;
        ph.Edges[vertex] = ph.sourceIndex;
    }
    
};


#endif /* Prims_hpp */
