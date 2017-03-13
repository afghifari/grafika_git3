#ifndef POINT_H
#define POINT_H

#include "base/base_point.h"

class Point : public BasePoint{
	public:
		Point();
		Point(double,double);
		Point(const Point&);

		void translate(double, double);
		void rotate(const Point&, int);
		Point translated(double, double);
		Point scaleUp(const Point&,double);
		void grow(const Point&,double);
		Point scaleUp(double);
};

#endif
