#include "helicopter.h"

Helicopter::Helicopter(Point _P) : Shape(13) {
	int cx = _P.getX();
	int cy = _P.getY();
	center.setX(cx);
	center.setY(cy);
	scale = 5;
	setPoint(0,Point(cx-4*scale,cy-2*scale));
			setPoint(1,Point(cx-scale,cy-6*scale));
			setPoint(2,Point(cx+scale,cy-6*scale));
			setPoint(3,Point(cx+4*scale,cy-2*scale));
			setPoint(4,Point(cx+4*scale,cy+2*scale));
			setPoint(5,Point(cx+scale,cy+5*scale));
			setPoint(6,Point(cx+scale,cy+15*scale));
			setPoint(7,Point(cx+3*scale,cy+16*scale));
			setPoint(8,Point(cx-3*scale,cy+16*scale));
			setPoint(9,Point(cx-scale,cy+15*scale));
			setPoint(10,Point(cx-scale,cy+5*scale));
			setPoint(11,Point(cx-4*scale,cy+2*scale));
			setPoint(12,Point(cx-4*scale, cy-2*scale));
}

Helicopter::Helicopter(Point _P,int _scale): Shape(13) {
	int cx = _P.getX();
	int cy = _P.getY();
	center.setX(cx);
	center.setY(cy);
	scale = _scale;
	setPoint(0,Point(cx-4*scale,cy-2*scale));
			setPoint(1,Point(cx-scale,cy-6*scale));
			setPoint(2,Point(cx+scale,cy-6*scale));
			setPoint(3,Point(cx+4*scale,cy-2*scale));
			setPoint(4,Point(cx+4*scale,cy+2*scale));
			setPoint(5,Point(cx+scale,cy+5*scale));
			setPoint(6,Point(cx+scale,cy+15*scale));
			setPoint(7,Point(cx+3*scale,cy+16*scale));
			setPoint(8,Point(cx-3*scale,cy+16*scale));
			setPoint(9,Point(cx-scale,cy+15*scale));
			setPoint(10,Point(cx-scale,cy+5*scale));
			setPoint(11,Point(cx-4*scale,cy+2*scale));
			setPoint(12,Point(cx-4*scale, cy-2*scale));
}

void Helicopter::moveByX(int x){
	Shape::moveByX(x);
	center.translate(x,0);
}

void Helicopter::moveByY( int y){
	Shape::moveByY(y);
	center.translate(0,y);
}
