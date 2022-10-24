/*
 * EuclideanGraph.h
 *
 *  Created on: Oct 23, 2022
 *      Author: potts
 */

#ifndef EUCLIDEANGRAPH_H_
#define EUCLIDEANGRAPH_H_
#include <string>
#include "DistanceMatrix.h"
#include "GraphEdge.h"

class EuclideanGraph {
public:
	EuclideanGraph(std::string data_file);
	virtual ~EuclideanGraph();
	GraphEdge* getEdges();
private:
	GraphEdge *edges;  // Linked List/Tree/Graph like structure
};

#endif /* EUCLIDEANGRAPH_H_ */
