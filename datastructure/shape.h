#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"

class Shape{
private:
	Point *P;
	int size;
public:

	Shape(int);
	Shape(int, Point*);
	virtual ~Shape();
	Shape(const Shape&);
	Shape& operator=(const Shape&);

	Point* getAllPoint() const;
	Point getPoint(int) const;
	int getSize() const;

	void setAllPoint(Point*);
	void setPoint(int, Point);

	//virtual void flood_fill();
};

// Utility functions
bool lineIntersect(Point a1, Point a2, Point b1, Point b2);
bool lineInsideRect(Point a1, Point a2, int x, int y, int w, int h);
bool pointInsideRect(Point p, int x, int y, int w, int h);

#endif
