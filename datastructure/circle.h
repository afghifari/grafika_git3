#ifndef CIRCLE_H
#define CIRCLE_H

#include "color.h"
#include "point.h"

class Circle{
private:
	Point center;
	int radius;
public:

	Circle(int, Point);
	Circle(const Circle&);
	Circle& operator=(const Circle&);

	Point getCenter() const;
	int getRadius() const;

	void setCenter(Point);
	void setRadius(int);

	Color color;
};

#endif
