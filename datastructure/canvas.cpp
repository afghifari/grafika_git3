#include "canvas.h"

Canvas::Canvas() {
	bitmap = new Color[MAX_CANVAS_WIDTH * MAX_CANVAS_HEIGHT];
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
	for(int j = 0;j < MAX_CANVAS_HEIGHT; ++j){
		for(int i = 0;i < MAX_CANVAS_WIDTH; ++i){
			setPixel(i, j, Color(0,0,0));
		}
	}
}
