#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "shape.h"

class Explosion: public Shape {
	public:
		Explosion(Point);
		Explosion(Point, int);
		Point center;
		int scale;
		void moveByX(int x);
		void moveByY(int y);

};

#endif