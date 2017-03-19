#include "drawer.h"
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
using namespace std;

Drawer::Drawer(Canvas* c) {
	destination = c;

  xOffset = 0;
  yOffset = 0;
  xClipWidth = MAX_CANVAS_WIDTH;
  yClipHeight = MAX_CANVAS_HEIGHT;

  xTranslate = 0;
  yTranslate = 0;
  drawScale = 1;

  xl = 0;
	yl = 0;

	xr = 800;
	yr = 600;

	topFirstMode = false;
}

void Drawer::draw_shapes(std::vector<Shape*> shapes) {
	for (size_t i = 0; i < shapes.size(); i++) {
		draw_shape(shapes[i]);
	}
}

void Drawer::draw_shape(Shape *S){
	int num_titik = S->getSize();
	for(int i = 0;i < num_titik - 1; ++i){
		gambarGaris(
			(S->getPoint(i)).translated(xTranslate, yTranslate).scaleUp(drawScale),
			(S->getPoint(i+1)).translated(xTranslate, yTranslate).scaleUp(drawScale),
			drawScale > 1 ? drawScale-1 : 0,
			S->color
		);
	}
}



void Drawer::draw_circles(std::vector<Circle*> circles) {
	for (size_t i = 0; i < circles.size(); i++) {
		draw_circle(circles[i]);
	}
}

void Drawer::draw_circle(Circle* IC) {
	Circle Cl(IC->getRadius()*drawScale, IC->getCenter().translated(xTranslate, yTranslate).scaleUp(drawScale));
	Cl.color = IC->color;

	Circle* C = &Cl;
	int d, p, q;

    p = 0;
    q = C->getRadius();
    d = 3 - 2*C->getRadius();

    drawEightPoint(C->getCenter(), p, q,C->color);

    while (p < q) {
        p++;
        if (d<0) {
            d = d + 4*p + 6;
        }
        else {
            q--;
            d = d + 4*(p-q) + 10;
        }

        drawEightPoint(C->getCenter(), p, q,C->color);
    }
}

void Drawer::drawEightPoint(Point P, int p, int q, Color C) {
	Point temp;
	temp.setX(P.getX()+p); temp.setY(P.getY()+q);
	gambarGaris(P,temp,1,C);

	temp.setX(P.getX()-p); temp.setY(P.getY()+q);
	gambarGaris(P,temp,1,C);

	temp.setX(P.getX()+p); temp.setY(P.getY()-q);
	gambarGaris(P,temp,1,C);

	temp.setX(P.getX()-p); temp.setY(P.getY()-q);
	gambarGaris(P,temp,1,C);

	temp.setX(P.getX()+q); temp.setY(P.getY()+p);
	gambarGaris(P,temp,1,C);

	temp.setX(P.getX()-q); temp.setY(P.getY()+p);
	gambarGaris(P,temp,1,C);

	temp.setX(P.getX()+q); temp.setY(P.getY()-p);
	gambarGaris(P,temp,1,C);

	temp.setX(P.getX()-q); temp.setY(P.getY()-p);
	gambarGaris(P,temp,1,C);
}

/*
void Drawer::gambarGaris(Point P1, Point P2, int tebal, Color color) {
	if (!lineInsideRect(P1, P2, 0, 0, xClipWidth, yClipHeight)) return;

	for(int t1 = -tebal; t1 <= tebal; ++t1){
		for(int t2 = -tebal; t2 <= tebal; ++t2){
			int xawal = P1.getX() < P2.getX() ? P1.getX() : P2.getX();
			int xakhir = P2.getX() > P1.getX() ? P2.getX() : P1.getX();

			int yawal = P1.getY(), yakhir = P2.getY();
			if(xawal != P1.getX()){
				std::swap(yawal, yakhir);
			}

			xawal += t1;
			xakhir += t1;
			yawal += t2;
			yakhir += t2;

			int selisihAbsX = xawal - xakhir >= 0 ? xawal - xakhir : xakhir - xawal;
			int selisihAbsY = yawal - yakhir >= 0 ? yawal - yakhir : yakhir - yawal;

			//bagi kasus kalo selisihnya 0
			if(selisihAbsX == 0){
				if(yawal > yakhir) std::swap(yawal, yakhir);
				for(int i = yawal; i <= yakhir; ++i){
					Point P = Point(xawal, i);
					gambarPoint(P, color);
				}
			}
			else if (selisihAbsY == 0){
				if(xawal > xakhir) std::swap(xawal, xakhir);
				for(int i = xawal; i <= xakhir; ++i){
					Point P = Point(i, yawal);
					gambarPoint(P, color);
				}
			}
			else if(selisihAbsY < selisihAbsX){
				if(xawal > xakhir) std::swap(xawal, xakhir), std::swap(yawal, yakhir);
				int deltaY = yakhir - yawal;
				int deltaX = xakhir - xawal;
				for(int i = 0; i <= deltaX; ++i){
					int modY = (deltaY * i) % deltaX;
					int ynow = yawal + (deltaY * i) / deltaX + (modY * 2) / deltaX;

					Point P = Point(xawal + i, ynow);
					gambarPoint(P, color);
				}
			}
			else{
				if(yawal > yakhir) std::swap(xawal, xakhir), std::swap(yawal, yakhir);
				int deltaY = yakhir - yawal;
				int deltaX = xakhir - xawal;
				for(int i = 0; i <= deltaY; ++i){
					int modX = (deltaX * i) % deltaY;
					int xnow = xawal + (deltaX * i) / deltaY + (modX * 2) / deltaY;

					Point P = Point(xnow, yawal + i);
					gambarPoint(P, color);
				}
			}

		}
	}
}
*/

void Drawer::gambarPoint(const Point& P, Color color){
	int x = P.getX();
	int xd = x + xOffset;
	int y = P.getY();
	int yd = y + yOffset;
	bool performDraw = x >= 0 && y >= 0 && x < xClipWidth && y < yClipHeight
	                   && (!topFirstMode || destination->getPixel(x, y) == destination->transparent);
	if (performDraw) {
		destination->setPixel(xd, yd, color);
	}

}


int Drawer::getcode(Point P){
	int x = P.getX(), y = P.getY();
	int code = 0;
	//Perform Bitwise OR to get outcode
	if(y > yr) code |=TOP;
	if(y < yl) code |=BOTTOM;
	if(x < xl) code |=LEFT;
	if(x > xr) code |=RIGHT;
	return code;
}


int Drawer::getcode(double x, double y){

	int code = 0;
	//Perform Bitwise OR to get outcode
	if(y > yr) code |=TOP;
	if(y < yl) code |=BOTTOM;
	if(x < xl) code |=LEFT;
	if(x > xr) code |=RIGHT;
	return code;
}

void Drawer::plotSlopPositiveLine (Point P1, Point P2, Color C) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.getX() - P1.getX());
	dY = abs(P2.getY() - P1.getY());
	i = P1.getX();
	j = P1.getY();

	if (dX >= dY) {
		p = 2*dY - dX;

		for (x=P1.getX(); x<=P2.getX(); x++) {
			gambarPoint(Point(x,j), C);
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j++;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;

		for (y=P1.getY(); y<=P2.getY(); y++) {
			gambarPoint(Point(i,y), C);
			if (p >= 0) {
				p += 2* (dX - dY);
				i++;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}


void Drawer::plotSlopNegativeLine (Point P1, Point P2, Color C) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.getX() - P1.getX());
	dY = abs(P2.getY() - P1.getY());

	if (dX >= dY) {
		i = P1.getX();
		j = P1.getY();
		p = 2*dY - dX;

		for (x=P1.getX(); x<=P2.getX(); x++) {
			gambarPoint(Point(x, j), C);
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j--;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;
		i = P2.getX();
		j = P2.getY();

		for (y=P2.getY(); y<=P1.getY(); y++) {
			gambarPoint(Point(i,y), C);
			if (p >= 0) {
				p += 2* (dX - dY);
				i--;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}

void Drawer::plotVerticalLine (Point P1, Point P2, Color C) {
	int j;

	if (P2.getY() < P1.getY()) {
		Point *temp = new Point(P1.getX(),P1.getY());
			P1.setX(P2.getX());
			P1.setY(P2.getY());
			P2.setX(temp->getX());
			P2.setY(temp->getY());
	}

	for(j = P1.getY() ; j <= P2.getY(); j++) {
		gambarPoint(Point(P1.getX(),j), C);
	}
}

void Drawer::gambarGaris (Point P1, Point P2, int tebal, Color C) {
	bool accept = false;
	double x0,y0,x1,y1;
	x0 = P1.getX(); y0 = P1.getY();
	x1 = P2.getX(); y1 = P2.getY();
	int outcode1 = getcode(x0,y0);
	int outcode2 = getcode(x1,y1);

	while(1){
		if(!(outcode1|outcode2)){
			accept = true;
			break;
		}

		else if(outcode2 & outcode1){
			break;
		}

		else{
			double x,y;
			int outcode = outcode1 ? outcode1 : outcode2;

			if (outcode & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (yr - y0) / (y1 - y0);
				y = yr;
			} else if (outcode & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (yl - y0) / (y1 - y0);
				y = yl;
			} else if (outcode & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (xr - x0) / (x1 - x0);
				x = xr;
			} else if (outcode & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (xl - x0) / (x1 - x0);
				x = xl;
			}

			if(outcode == outcode1){
				x0 = x, y0 = y;
				outcode1 = getcode(x,y);
			}
			else if(outcode == outcode2){
				x1 = x, y1 = y;
				outcode2 = getcode(x,y);
			}
		}


	}
	if(accept){
		P1 = Point(x0,y0),P2=Point(x1,y1);
		if (P1.getX() > P2.getX()) {
			//P1.swapPoint(&P2);
			Point *temp = new Point(P1.getX(),P1.getY());
			P1.setX(P2.getX());
			P1.setY(P2.getY());
			P2.setX(temp->getX());
			P2.setY(temp->getY());
		}

		if ((P2.getX() >= P1.getX() && P1.getY() > P2.getY())) {
			plotSlopNegativeLine(P1,P2,C);
		}
		else if (P1.getX() == P2.getX()) {
			plotVerticalLine(P1,P2,C);
		}
		else {
			plotSlopPositiveLine(P1,P2,C);
		}
	}


}
