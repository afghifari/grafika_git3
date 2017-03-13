#ifndef CANVAS_H
#define CANVAS_H

#include "shape.h"
#include "color.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

#define MAX_CANVAS_HEIGHT 600
#define MAX_CANVAS_WIDTH 1280

class Canvas {
	public:
		Canvas();
		~Canvas();

		Color getPixel(int x, int y);
		void setPixel(int x, int y, Color c);

		void clear_all();

		Color transparent;

		static void mergeCanvas(Canvas* destination, std::vector<Canvas*> layers);

		int xStart;
		int xEnd;
		int yStart;
		int yEnd;

	private:
		Color* bitmap;
};

#endif
