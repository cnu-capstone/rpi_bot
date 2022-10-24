/*
 * EuclideanPoint.h
 *
 *  Created on: Oct 23, 2022
 *      Author: potts
 */

#ifndef EUCLIDEANPOINT_H_
#define EUCLIDEANPOINT_H_

class EuclideanPoint {
public:
	EuclideanPoint(int point_id, int px, int py);
	virtual ~EuclideanPoint();
	int getPointID();
	int getX();
	int getY();
private:
	int id;
	int x;
	int y;
};

#endif /* EUCLIDEANPOINT_H_ */
