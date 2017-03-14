#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "shape.h"
#include "animatable.h"

class Explosion: public Shape, public Animatable {
	public:
		Explosion(Point);
		Explosion(Point, int);
		Point center;
		int scale;
		void moveByX(int x);
		void moveByY(int y);
		virtual bool animate();
	private:
		double animProgress;
};

#endif
