/*
 * GraphEdge.cpp
 *
 *  Created on: Oct 23, 2022
 *      Author: potts
 */

#include "GraphEdge.h"

GraphEdge::GraphEdge(EuclideanPoint pnode, EuclideanPoint* pnext):node(pnode),next(pnext) {
}

GraphEdge::~GraphEdge() {
	// Delete Pointer?
}

EuclideanPoint GraphEdge::getPoint() {
	return this->node;
}

EuclideanPoint* GraphEdge::getNext() {
	return this->next;
}
