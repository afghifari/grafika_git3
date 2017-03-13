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
