#include "canvas.h"

Canvas::Canvas() {
	bitmap = new Color[MAX_CANVAS_WIDTH * MAX_CANVAS_HEIGHT];
	xStart = 0;
	xEnd = MAX_CANVAS_WIDTH;
	yStart = 0;
	yEnd = MAX_CANVAS_HEIGHT;
	clear_all();
}

Canvas::~Canvas() {
	delete bitmap;
}

Color Canvas::getPixel(int x, int y) {
	return bitmap[y * MAX_CANVAS_WIDTH + x];
}

void Canvas::setPixel(int x, int y, Color c) {
	if (x >= 0 && x < MAX_CANVAS_WIDTH && y >= 0 && y < MAX_CANVAS_HEIGHT) {
		bitmap[y * MAX_CANVAS_WIDTH + x] = c;
	}
}

void Canvas::clear_all(){
	for(int j = yStart; j < yEnd; ++j){
		for(int i = xStart;i < xEnd; ++i){
			setPixel(i, j, transparent);
		}
	}
}

void Canvas::mergeCanvas(Canvas* destination, std::vector<Canvas*> layers) {
	for (size_t i = 0; i < layers.size(); i++) {
		Canvas* layer = layers[i];
		for(int y = layer->yStart; y < layer->yEnd; ++y){
			for(int x = layer->xStart; x < layer->xEnd; ++x){
				Color cpx = layer->getPixel(x, y);
				if (i == 0 || cpx != layer->transparent) {
					destination->setPixel(x, y, cpx);
				}
			}
		}
	}
}


/**
* boundary_fill berfungsi untuk mewarnai objek dari dalam. seperti flood fill
*	x : kordinat x
*	y : kordinat y
*	new_color 	: warna buat fill objek
*	b_color		: warna dalam objek sebelum diwarnai. warna backgroundnya.
*/
void Canvas::boundary_fill (int x, int y, Color new_color, Color b_color) {
	Color current;
	if ((x > xStart) && (x < xEnd) && (y > yStart) && (y < yEnd)) {
		current = getPixel(x, y);
		if (current == b_color) {
			setPixel (x, y, new_color);

			boundary_fill(x+1, y, new_color, b_color);
			boundary_fill(x, y+1, new_color, b_color);
			boundary_fill(x-1, y, new_color, b_color);
			boundary_fill(x, y-1, new_color, b_color);
		}
	}
}
