#include "heli_propeller.h"

HeliPropeller::HeliPropeller(Point _P) : Shape(13) {
	int cx = _P.getX();
	int cy = _P.getY();
	center.setX(cx);
	center.setY(cy);

	scale = 5;
	setPoint(0,Point(cx-scale,cy-scale));
			setPoint(1,Point(cx-12*scale,cy-scale));
			setPoint(2,Point(cx-12*scale,cy+scale));
			setPoint(3,Point(cx-scale,cy+scale));
			setPoint(4,Point(cx-scale,cy+12*scale));
			setPoint(5,Point(cx+scale,cy+12*scale));
			setPoint(6,Point(cx+scale,cy+scale));
			setPoint(7,Point(cx+12*scale,cy+scale));
			setPoint(8,Point(cx+12*scale,cy-scale));
			setPoint(9,Point(cx+scale,cy-scale));
			setPoint(10,Point(cx+scale,cy-12*scale));
			setPoint(11,Point(cx-scale,cy-12*scale));
			setPoint(12,Point(cx-scale, cy-scale));
}

HeliPropeller::HeliPropeller(Point _P,int _scale): Shape(13) {
	int cx = _P.getX();
	int cy = _P.getY();
	center.setX(cx);
	center.setY(cy);
	scale = 5;
	setPoint(0,Point(cx-scale,cy-scale));
	setPoint(1,Point(cx-12*scale,cy-scale));
	setPoint(2,Point(cx-12*scale,cy+scale));
	setPoint(3,Point(cx-scale,cy+scale));
	setPoint(4,Point(cx-scale,cy+12*scale));
	setPoint(5,Point(cx+scale,cy+12*scale));
	setPoint(6,Point(cx+scale,cy+scale));
	setPoint(7,Point(cx+12*scale,cy+scale));
	setPoint(8,Point(cx+12*scale,cy-scale));
	setPoint(9,Point(cx+scale,cy-scale));
	setPoint(10,Point(cx+scale,cy-12*scale));
	setPoint(11,Point(cx-scale,cy-12*scale));
	setPoint(12,Point(cx-scale, cy-scale));
}

void HeliPropeller::moveByX( int x){
	Shape::moveByX(x);
	center.translate(x,0);
}

void HeliPropeller::moveByY( int y){
	Shape::moveByY(y);
	center.translate(0,y);
}

bool HeliPropeller::animate() {
	rotate(center, 15);
	return false;
}
