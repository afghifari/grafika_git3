#include "shape.h"

Shape::Shape(int _size) : color(255, 255, 255) {
	size = _size;
	P = new Point[size];
	for(int i = 0;i < size; ++i){
		P[i] = Point();
	}
}

Shape::Shape(int _size, Point* _P) : color(255, 255, 255) {
	size = _size;
	P = new Point[size];

	for(int i = 0;i < size; ++i){
		P[i] = Point(_P[i]);
	}
}

Shape::~Shape(){
	delete [] P;
}

Shape::Shape(const Shape& S) : color(255, 255, 255) {

	size = S.size;
	P = new Point[size];

	for(int i = 0;i < size; ++i){
		P[i] = Point(S.P[i]);
	}
}

Shape& Shape::operator=(const Shape& S){

	delete [] P;
	size = S.size;
	P = new Point[size];

	for(int i = 0;i < size; ++i){
		P[i] = Point(S.P[i]);
	}

	color = S.color;

	return *this;
}

Point* Shape::getAllPoint() const{
	return P;
}
Point Shape::getPoint(int idx) const{
	return P[idx];
}
int Shape::getSize() const{
	return size;
}

void Shape::setAllPoint(Point* _P){
	delete [] P;
	P = new Point[size];
	for(int i = 0;i < size; ++i){
		P[i] = Point(_P[i]);
	}
}
void Shape::setPoint(int idx, Point _P){
	P[idx] = _P;
}

bool lineIntersect(Point a1, Point a2, Point b1, Point b2) {
	// Based on https://stackoverflow.com/a/1968345/3816975
	float s1_x, s1_y, s2_x, s2_y;
    s1_x = a2.getX() - a1.getX();     s1_y = a2.getY() - a1.getY();
    s2_x = b2.getX() - b2.getX();     s2_y = b2.getY() - b1.getY();

    float s, t;
    s = (-s1_y * (a1.getX() - b1.getX()) + s1_x * (a1.getY() - b1.getY())) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (a1.getY() - b1.getY()) - s2_y * (a1.getX() - b1.getX())) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        return true;
    }

    return false;
}

bool lineInsideRect(Point a1, Point a2, int x, int y, int w, int h) {
	Point r0(x, y);
	Point r1(x + w, y);
	Point r2(x + w, y + h);
	Point r3(x, y + h);
	return
		pointInsideRect(a1, x, y, w, h) ||
		pointInsideRect(a2, x, y, w, h) ||
		lineIntersect(a1, a2, r0, r1) ||
		lineIntersect(a1, a2, r1, r2) ||
		lineIntersect(a1, a2, r2, r3) ||
		lineIntersect(a1, a2, r3, r0);
}

bool pointInsideRect(Point p, int x, int y, int w, int h) {
	return p.getX() >= x && p.getX() < x + w && p.getY() >= y && p.getY() < y + h;
}
