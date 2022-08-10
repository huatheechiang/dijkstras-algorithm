#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include <list>
#include <limits.h>
#include <queue>
#include <map>

class Edge { 
public:
    //constructor
    Edge(std::string label1 = "", unsigned long _weight = 0) : endpoint{label1}, weight{_weight} {}
    //destructor
    ~Edge() = default;
    //accessors
    std::string getEndpt() const { return endpoint; }
    unsigned long getWeight() const { return weight; }

private: // data members
    std::string endpoint; //other endpoint (not vertex)
    unsigned long weight; //weight of the edge
    friend class Graph;
};

class Vertex {
public:
    //constructor
    Vertex(std::string held = "") : element{held} {};
    //destructor
    ~Vertex() = default;

    std::string operator*() { return element; }; //return element at vertex
    
    // utility functions to modify Vertex object's data members
    void push_back_edge(Edge* e) { edgeList.push_back(e); }
    void remove_edge(Edge* edge) { edgeList.remove(edge); }

    // edge_list accessor
    std::list<Edge*> getEdgeList() { return edgeList; }

private:
		std::string element;
    std::list<Edge*> edgeList; //every edge connected to the Vertex. Do we need the asterisk? 
    friend class Graph;
};

class Graph : public GraphBase {
public:
    //constructor
    Graph() = default;
    //destructor
    ~Graph(); 

    //accessor
    std::vector<Vertex> getAdjacencyList() const { return adjList; } 

    // METHODS TO IMPLEMENT FOR ASSIGNMENT
    virtual void addVertex(std::string label); //inserts a new vertex storing the element
    virtual void removeVertex(std::string label);  // remove vertex containing the element and all its incident edges
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight); //insert a new undirected edge with end vertices
    virtual void removeEdge(std::string label1, std::string label2); // remove the edge between the two vertices given
    virtual unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path); //calculates the weight of the shortestPath of all verticies
private:
    //adjacency_list that holds Vertex objects
    std::vector<Vertex> adjList;
};

#endif