#ifndef HELIP_H
#define HELIP_H
#include "shape.h"

class HeliPropeller: public Shape {
	public:
		HeliPropeller(Point);
		HeliPropeller(Point, int);
		int scale;
};

#endif
