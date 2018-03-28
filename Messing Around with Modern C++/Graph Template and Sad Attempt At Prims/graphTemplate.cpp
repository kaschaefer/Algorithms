//
//  graphTemplate.hpp
//  Prims
//
//  Created by Mikaela Schaefer on 3/27/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//

#ifndef graphTemplate_hpp
#define graphTemplate_hpp

#include <stdio.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>
#include <queue>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Node;

template <class T>
class Node {
private:
    T data;
    bool visited;
    
public:
    //because i'm lazy
    vector<Edge<T> > adjacent;
    
    Node() : data(-1), visited(false){;};
    Node(T in);
    Node(const Node<T> &v);
    bool isVisited() const {return isVisited;};
    T getData() const {return data;};
    void AddEdge(Node<T> dest, double weight);
    bool RemoveEdgeTo(Node<T> d);
    
    friend class Graph<T>;
};
//Edge Defs

template <class T>
class Edge {
private:
    shared_ptr<Node<T> > dest;
    
    bool isVisited;
    
public:
    //lazzzzzzzzzy
    double weight;
    shared_ptr<Node<T> > GetDest() const {return dest;};
    Edge();
    Edge(Node<T> dest, double w);
    friend class Graph<T>;
    friend class Node<T>;
};

//First Arg is Type of Weights for Edges, Second Arg is Type of Edges, A is allocator
template <class T>
class Graph{
private:
    //A Graph Has A List of Vertices
    vector<unique_ptr<Node<T> > > nodeSet;
    void depthFS(Node<T> v, vector<Node<T> > &result);
    int counter;
    
public:
    Graph() : counter(0){;};
    bool AddVertex(const T& in);
    bool AddEdge(const T& sourc, const T& dest, double w);
    bool RemoveVertex(const T& in);
    bool RemoveEdge(const T& sourc, const T &dest);
    vector<Node<T> > depthFS();
    vector<Node<T> > bfs(unique_ptr<Node<T> > v) const;
    vector<Node<T> > getVertexSet() const;
    inline int getNumVertex() const {return counter;};
//    void clone(Graph<T> &g);
};

//Node Class Implementation

//Constructor
template <class T>
Node<T>::Node(T in) : data(in), visited(false){}

//Copy Constructor
template <class T>
Node<T>::Node(const Node<T> &v) : data(v.data), visited(v.visited), adjacent(v.adjacent){}

//Add Edge to Adjacency List
template <class T>
void Node<T>::AddEdge(Node<T> dest, double weight){
    adjacent.push_back(Edge<T>(dest, weight));
}

template <class T>
bool Node<T>::RemoveEdgeTo(Node<T> d){
    bool returnVal = false;
    auto it = adjacent.begin();
    auto ite = adjacent.end();
    while (it != ite){
        if (it->dest == d) {
            adjacent.erase(it);
            returnVal = true;
        }
    }
    return returnVal;
}


//Edge Class Implementation
//Make Edge with Destination node newDest
template <class T>
Edge<T>::Edge(Node<T> newDest, double w) : isVisited(false){
    weight = w;
    dest = std::make_shared<Node<T> >(newDest);
}

//Graph Class
template <class T>
void Graph<T>::depthFS(Node<T> v, vector<Node<T> > &resultVec){
    v.visited = true;
    resultVec.push_back(v.data);
    typename vector<unique_ptr<Node<T> > >::iterator it = v.adjacent.begin();
    typename vector<unique_ptr<Node<T> > >::iterator ite = v.adjacent.end();
    for (; it != ite; it++){
        if (it->dest->isVisited() == false){
            dfs(it->dest, resultVec);
        }
    }
}

template <class T>
bool Graph<T>::AddVertex(const T& in){
    bool shouldAdd = true;
    for (auto const& i: nodeSet){
        if (i->data == in) {
            shouldAdd = false;
        }
    }
    if (shouldAdd){
        unique_ptr<Node<T > > ptr = make_unique<Node<T> >(in);
        nodeSet.push_back(std::move(ptr));
        counter++;
    }
    return shouldAdd;
}

template <class T>
bool Graph<T>::AddEdge(const T& sourc, const T& dest, double w){
    bool returnVal = false;
    int found = 0;
    //Create Observer Pointers
    Node<T>* edgeSrc;
    Node<T>* edgeDest;
    for (auto const& i: nodeSet){
        if ( i->data == sourc){
            edgeSrc = &(*i);
            found++;
        }
        if ( i->data == dest){
            edgeDest = &(*i);
            found++;
        }
        if (found == 2){
            break;
        }
    }
    if (found != 2) {
        returnVal = false;
    }
    edgeSrc->AddEdge(*edgeDest, w);
    return returnVal;
}

template <class T>
bool Graph<T>::RemoveVertex(const T& in){
    typename vector<unique_ptr<Node<T> > >::iterator it= nodeSet.begin();
    typename vector<unique_ptr<Node<T> > >::iterator ite= nodeSet.end();
    for (; it!=ite; it++) {
        if ((*it)->info == in) {
            Node<T> * v= *it;
            nodeSet.erase(it);
            auto it1= nodeSet.begin();
            auto it1e= nodeSet.end();
            for (; it1!=it1e; it1++) {
                (*it1)->removeEdgeTo(v);
            }
            delete v;
            counter--;
            return true;
        }
    }
    return false;
}

template <class T>
bool Graph<T>::RemoveEdge(const T &sourc, const T &dest){
    typename vector<unique_ptr<Node<T> > >::iterator  it = nodeSet.begin();
    typename vector<unique_ptr<Node<T> > >::iterator ite = nodeSet.end();
    int found=0;
    Node<T> edgeSrc;
    Node<T> edgeDest;
    while (found!=2 && it!=ite ) {
        if ((*it)->info == sourc ){
            edgeSrc=*it;
            found++;
            
        }
        if ((*it)->info == dest ){
            edgeDest=*it;
            found++;
        }
        it ++;
    }
    if (found!=2) return false;
    return edgeSrc.removeEdgeTo(edgeDest);
}

template <class T>
vector<Node< T> > Graph<T>::depthFS(){
    typename vector<unique_ptr<Node<T> > >::const_iterator it= nodeSet.begin();
    typename vector<unique_ptr<Node<T> > >::const_iterator ite= nodeSet.end();
    for (; it !=ite; it++)
        (*it)->visited=false;
    vector<T> res;
    it=nodeSet.begin();
    for (; it !=ite; it++)
        if ( (*it)->visited==false )
            depthFS(**it,res);
    return res;
}

template <class T>
vector<Node<T> > Graph<T>::bfs(unique_ptr<Node<T> > v) const{
    vector<T> res;
    queue<Node<T> > q;
    q.push(*v);
    v->visited = true;
    while (!q.empty()) {
        Node<T> v1 = q.front();
        q.pop();
        res.push_back(v1.data);
        typename vector<Edge<T> >::iterator it=v1.adjacent.begin();
        typename vector<Edge<T> >::iterator ite=v1.adjacent.end();
        for (; it!=ite; it++) {
            Node<T> d = it->dest;
            if (d->visited==false) {
                d->visited=true;
                q.push(d);
            }
        }
    }
    return res;
}

template <class T>
vector<Node<T> > Graph<T>::getVertexSet() const {
    vector<Node<T> > returnVector;
    returnVector.push_back(**nodeSet.begin());
    for (auto i = std::next(nodeSet.begin()); i != nodeSet.end(); i++){
        returnVector.push_back(**i);
    }
    return std::forward<vector<Node<T> > >(returnVector);
}
//
//template <class T>
//void Graph<T>::clone(Graph<T> &g){
//    typename vector<unique_ptr<Node<T> > >::const_iterator it= nodeSet.begin();
//    typename vector<unique_ptr<Node<T> > >::const_iterator ite= nodeSet.end();
//
//    // 1. clone vertices
//    for (; it !=ite; it++) {
//        g.addVertex((*it)->getInfo());
//        g.vertexSet[g.getNumVertex()-1]->visited = false;
//    }
//
//    // 2. clone edges
//    for (it=nodeSet.begin(); it !=ite; it++) {
//        typename vector<Edge<T> >::iterator edgeIt= ((*it)->adj).begin();
//        typename vector<Edge<T> >::iterator edgeIte= ((*it)->adj).end();
//        for (; edgeIt !=edgeIte; edgeIt++) {
//            g.addEdge((*it)->getInfo(), edgeIt->dest->getInfo(), edgeIt->weight);
//        }
//    }
//}


#endif /* graphTemplate_hpp */
