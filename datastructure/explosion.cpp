#include "explosion.h"

Explosion::Explosion(Point _P) : Shape(13) {
	int cx = _P.getX();
	int cy = _P.getY();
	scale = 5;
	center.setX(cx);
	center.setY(cy);

	animProgress = 0;

	setPoint(0,Point(cx, cy-12*scale));
			setPoint(1,Point(cx-6*scale,cy-8*scale));
			setPoint(2,Point(cx-12*scale,cy-4*scale));
			setPoint(3,Point(cx-6*scale,cy));
			setPoint(4,Point(cx-12*scale,cy+4*scale));
			setPoint(5,Point(cx-6*scale,cy+8*scale));
			setPoint(6,Point(cx,cy+12*scale));
			setPoint(7,Point(cx+6*scale,cy+8*scale));
			setPoint(8,Point(cx+12*scale,cy+12*scale));
			setPoint(9,Point(cx+6*scale,cy));
			setPoint(10,Point(cx+12*scale,cy-4*scale));
			setPoint(11,Point(cx+6*scale,cy-8*scale));
			setPoint(12,Point(cx, cy-12*scale));
}

Explosion::Explosion(Point _P,int _scale): Shape(13) {
	int cx = _P.getX();
	int cy = _P.getY();
	scale = _scale;
	center.setX(cx);
	center.setY(cy);
	setPoint(0,Point(cx, cy-12*scale));
			setPoint(1,Point(cx-4*scale,cy-8*scale));
			setPoint(2,Point(cx-12*scale,cy-4*scale));
			setPoint(3,Point(cx-6*scale,cy));
			setPoint(4,Point(cx-12*scale,cy+4*scale));
			setPoint(5,Point(cx-4*scale,cy+8*scale));
			setPoint(6,Point(cx,cy+12*scale));
			setPoint(7,Point(cx+4*scale,cy+8*scale));
			setPoint(8,Point(cx+12*scale,cy+4*scale));
			setPoint(9,Point(cx+6*scale,cy));
			setPoint(10,Point(cx+12*scale,cy-4*scale));
			setPoint(11,Point(cx+4*scale,cy-8*scale));
			setPoint(12,Point(cx, cy-12*scale));
}

void Explosion::moveByX(int x){
	Shape::moveByX(x);
	center.translate(x,0);
}

void Explosion::moveByY( int y){
	Shape::moveByY(y);
	center.translate(0,y);
}

bool Explosion::animate() {
	if (animProgress < 10) {
		scaleUp(center, 1.5);
		animProgress++;
		return false;
	} else {
		return true;
	}
}
