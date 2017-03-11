#ifndef DRAWER_H
#define DRAWER_H

#include "shape.h"
#include "color.h"
#include "canvas.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

class Drawer {
public:
  Drawer(Canvas* c);
  void draw_shapes(std::vector<Shape*> shapes);
  void draw_shape(Shape*);
  void gambarGaris(Point, Point, int);
  void gambarPoint(const Point&);

  // Where to draw the pixels to the screen, and how much to draw
  int xOffset;
  int yOffset;
  int xClipWidth;
  int yClipHeight;

  // What to do with the shapes before they are drawn
  int xTranslate;
  int yTranslate;
  double drawScale;

private:
  Canvas* destination;

};

#endif
