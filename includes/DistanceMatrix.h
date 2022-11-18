/*
 * DistanceMatrix.h
 *
 *  Created on: Oct 23, 2022
 *      Author: potts
 */

#ifndef DISTANCEMATRIX_H_
#define DISTANCEMATRIX_H_
#include <string>
#include "EuclideanPoint.h"

class DistanceMatrix {
public:
	DistanceMatrix(std::string data_set);
	virtual ~DistanceMatrix();
	float** getDistanceMatrix();
	float getDistanceBetweenPoints(int p1, int p2);
	EuclideanPoint* getListOfPoints();
private:
	int set_size;
	float **dist_matrix;
	EuclideanPoint *points_list;
};

#endif /* DISTANCEMATRIX_H_ */
