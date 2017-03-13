#include "base_point.h"

BasePoint::BasePoint(){
	x = 0;
	y = 0;
}

BasePoint::BasePoint(double _x, double _y){
	x = _x, y = _y;
}

BasePoint::BasePoint(const BasePoint& BP){
	x = BP.x;
	y = BP.y;
}

double BasePoint::getX() const{
	return x;
}
double BasePoint::getY() const{
	return y;
}
void BasePoint::setX(double _x){
	x = _x;
}
void BasePoint::setY(double _y){
	y = _y;
}
