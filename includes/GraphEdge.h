/*
 * GraphEdge.h
 *
 *  Created on: Oct 23, 2022
 *      Author: potts
 */

#ifndef GRAPHEDGE_H_
#define GRAPHEDGE_H_
#include "EuclideanPoint.h"

class GraphEdge {
public:
	GraphEdge(EuclideanPoint pnode, EuclideanPoint* pnext);
	virtual ~GraphEdge();
	EuclideanPoint getPoint();
	EuclideanPoint* getNext();
private:
	EuclideanPoint node;
	EuclideanPoint* next;
};

#endif /* GRAPHEDGE_H_ */
