#ifndef DRAWER_H
#define DRAWER_H

#include "shape.h"
#include "circle.h"
#include "color.h"
#include "canvas.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cmath>

class Drawer {
public:
  Drawer(Canvas* c);
  void draw_shapes(std::vector<Shape*> shapes);
  void draw_shape(Shape*);
  void draw_circles(std::vector<Circle*> circles);
  void draw_circle(Circle*);
  void gambarGaris(Point, Point, int, Color);
  void gambarPoint(const Point&, Color);
  void drawEightPoint(Point, int, int, Color);

  // Where to draw the pixels to the screen, and how much to draw
  int xOffset;
  int yOffset;
  int xClipWidth;
  int yClipHeight;

  // What to do with the shapes before they are drawn
  int xTranslate;
  int yTranslate;
  double drawScale;

  bool topFirstMode;

	int getcode(Point P);
	int getcode(double x, double y);
	void plotSlopPositiveLine (Point P1, Point P2, Color C);
	void plotSlopNegativeLine (Point P1, Point P2, Color C);
	void plotVerticalLine (Point P1, Point P2, Color C);
	int xl,yl,xr,yr;

  Canvas* destination;
};

#endif
