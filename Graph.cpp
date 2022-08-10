#include "Graph.hpp"
#include <iostream>

//Graph Destructor
Graph::~Graph() {
	
  for(auto itrVer = adjList.begin(); itrVer != adjList.end(); itrVer++){ //iterate through adjList
		for (auto edge : itrVer->getEdgeList()){
			// delete every edge for every vertex in the graph
			delete edge;
		}
	}
	// clear the adjacency list 
	adjList.clear();
}

/* ============= Add Methods =============*/

void Graph::addVertex(std::string label){
  Vertex v(label); 
  adjList.push_back(v); //push back into vector 
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
	Edge* vertex = new Edge(label1, weight);//initialize object vertex
	Edge* endpt = new Edge(label2, weight); //initialize object endpt 

  for(auto itrVer = adjList.begin(); itrVer != adjList.end(); itrVer++){ //iterate through adjList
		
    if(itrVer->element == label1) itrVer->push_back_edge(endpt); //push object endpt
		else if(itrVer->element == label2) itrVer->push_back_edge(vertex); //push object vertex
    
  }
}

/* ============= Remove Methods  =============*/

void Graph::removeVertex(std::string label) {

	auto itrVer = adjList.begin();
	while(itrVer < adjList.end()) { //iterate through adjList
    if (itrVer->element == label) adjList.erase(itrVer); //delete the entire vertex 
			
    else{ //to iterate through the edgelist and delete...
      auto edgeList = itrVer->getEdgeList();  

			for (auto itrEdge = edgeList.begin(); itrEdge != edgeList.end(); itrEdge++) {
				auto edge = *itrEdge;
				if (edge->getEndpt() == label) itrVer->remove_edge(edge);
			}
			itrVer++; //iterate through adjList
		}
	}
}

void Graph::removeEdge(std::string label1, std::string label2) {
	// for every vertex in the graph
  for(auto itrVer = adjList.begin(); itrVer != adjList.end(); itrVer++){
		auto edgeList = itrVer->getEdgeList();
		
		for (auto itrEdge = edgeList.begin(); itrEdge != edgeList.end(); itrEdge++) {
			auto edge = *itrEdge;
			if(itrVer->element == label1 && edge->getEndpt() == label2) { 
					// found the appropiate edge and can remove
					itrVer->remove_edge(edge);
					break;
				}
			
			else if (itrVer->element == label2 && edge->getEndpt() == label1) {
				//found edge and remove
				itrVer->remove_edge(edge);
				break;
			} 
		}
	}
}

/* ============= Dijkstra's Algorithm =============*/

void getPath(std::vector<std::string>& path, std::map<std::string, std::string> previous, std::string endLabel) {
	if (previous[endLabel] == "")  //if it is not the empty string
		return;
			
	else { //return void when the endLabel = ""
		getPath(path, previous, previous[endLabel]); // recursive call
		path.push_back(endLabel);
	}
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
	// Initalize Data Structures
	std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pQueue;
	std::map<std::string, int> distanceFromStart;
	std::map<std::string, std::string> prev;

	// assign infinity path values to all other devicesh
	for(auto itrVer = adjList.begin(); itrVer != adjList.end(); itrVer++){
		// add them to each map with default values
		distanceFromStart[itrVer->element] = INT_MAX;
		prev[itrVer->element] = "\0";
	}
	// push the first vertex into the pq
	pQueue.push(std::make_pair(0, startLabel));
	distanceFromStart[startLabel] = 0; //initial distance is just to itself
	
	do {
		std::string currVertex = pQueue.top().second; // get a current_vertex
		pQueue.pop(); //pop it from the queue
		std::string adjVertex;

		// for each vertex in the graph
		for(auto itrVer = adjList.begin(); itrVer != adjList.end(); itrVer++){
			for (auto edge : itrVer->getEdgeList()) { //for each edge at the vertex
				
				// loop to the current vertex
				if(itrVer->element == currVertex) 
					adjVertex = edge->getEndpt();
				
				else  // if not the current vertex
					continue;

				auto weight = edge->getWeight();
				long distanceToAdjacent = distanceFromStart[adjVertex]; 
				long distancetoCurrVertex = distanceFromStart[currVertex] + weight;

				// Checking if the distance 
				if(distanceToAdjacent > distancetoCurrVertex) {
					prev[adjVertex] = currVertex; // set the previous vertex of the neighbor to the curr_vertex
					distanceFromStart[adjVertex] = distanceFromStart[currVertex] + weight; //set the new distance
					pQueue.push(std::make_pair(distanceFromStart[adjVertex], adjVertex)); // push back into queue
				} 
				else continue;
			}
		}
		
	} while (!pQueue.empty()); //keep looping while priority queue is not empty

	path.push_back(startLabel);
	getPath(path, prev, endLabel); // finish creating path
	return distanceFromStart[endLabel]; // return the weight of the entire path (start->endLabel)
}

