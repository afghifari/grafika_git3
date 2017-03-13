#ifndef HELIP_H
#define HELIP_H
#include "shape.h"

class HeliPropeller: public Shape {
	public:
		HeliPropeller(Point);
		HeliPropeller(Point, int);
		int scale;
		Point center;
		void moveByX( int x);
		void moveByY(int y);

};

#endif
