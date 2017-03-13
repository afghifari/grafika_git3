#ifndef HELI_H
#define HELI_H
#include "shape.h"

class Helicopter: public Shape {
	public:
		Helicopter(Point);
		Helicopter(Point, int);
		int scale;
};

#endif
