#include "point.h"
#include <cmath>
#define PI 3.14159265

Point::Point() : BasePoint(){
	//do nothing
}

Point::Point(double _x, double _y) : BasePoint(_x, _y){
	//do nothing
}

Point::Point(const Point& P) : BasePoint(P){
	//do nothing
}

void Point::translate(double deltaX, double deltaY){
	setX(getX() + deltaX);
	setY(getY() + deltaY);
}

void Point::rotate(const Point& poros, int theta){
	double oldX = getX(), oldY = getY();
	double degree = ((double)theta)* PI/180 ;
	setX(poros.getX() + ((oldX - poros.getX()) * cos(degree) - (poros.getY() - oldY) * sin(degree)));
	setY(poros.getY() - ((oldX - poros.getX()) * sin(degree) + (poros.getY() - oldY) * cos(degree)));

}

Point Point::translated(double deltaX, double deltaY){
	return Point(getX() + deltaX, getY() + deltaY);
}

Point Point::scaleUp(const Point& center, double scale){
	Point P_new;
	P_new.setX(((getX() - center.getX()) * scale) + center.getX());
	P_new.setY(((getY() - center.getY()) * scale) + center.getY());
	return P_new;
}

void Point::grow(const Point& center, double scale){
	setX(((getX() - center.getX()) * scale) + center.getX());
	setY(((getY() - center.getY()) * scale) + center.getY());
}

Point Point::scaleUp(double scale){
	Point P_new;
	P_new.setX((getX() * scale));
	P_new.setY((getY() * scale));
	return P_new;
}
