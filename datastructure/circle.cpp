#include "circle.h"

Circle::Circle(int _radius, Point _center) : color(255, 255, 255) {
	radius = _radius;
	center = _center;
}

Circle::Circle(const Circle& C) : color(255,255,255) {
	radius = C.radius;
	center = C.center;
}

Circle& Circle::operator=(const Circle& C) {
	radius = C.radius;
	center = C.center;
	color = C.color;
}

Point Circle::getCenter() const {
	return center;
}

int Circle::getRadius() const {
	return radius;
}

void Circle::setCenter(Point _center) {
	center = _center;
}

void Circle::setRadius(int _radius) {
	radius = _radius;
}

