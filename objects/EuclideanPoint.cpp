/*
 * EuclideanPoint.cpp
 *
 *  Created on: Oct 23, 2022
 *      Author: potts
 */

#include "includes/EuclideanPoint.h"

EuclideanPoint::EuclideanPoint(int point_id, int px, int py):id(point_id),x(px),y(py) {}

EuclideanPoint::~EuclideanPoint() {}  // Has no dynamic memory

int EuclideanPoint::getPointID() {
	return this->id;
}

int EuclideanPoint::getX() {
	return this->x;
}

int EuclideanPoint::getY() {
	return this->y;
}

