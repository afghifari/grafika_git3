//main.cpp
#include <iostream>

#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include <termios.h>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <deque>
#include <pthread.h>

#include "datastructure/point.h"
#include "datastructure/line.h"
#include "datastructure/color.h"
#include "datastructure/shape.h"
#include "datastructure/canvas.h"
#include "datastructure/drawer.h"
#include "datastructure/itbmap.h"
#include "datastructure/helicopter.h"
#include "datastructure/heli_propeller.h"
#include "datastructure/explosion.h"
#include "datastructure/credit.h"

using namespace std;

//framebuffer related
int fbfd = 0;
long int screensize = 0;
long int location = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
char *fbp = 0;
Helicopter *Heli = new Helicopter(Point(300,300),5);
HeliPropeller *HeliProp = new HeliPropeller(Point(300,300),5);
std::vector<Circle*> holes;
std::vector<Explosion*> explosions;

int scale = 1;

bool b, j, p;

bool heliMoved = true;
bool holeNewlyAdded = true;

std::mutex qMutex;
std::deque<char> keyQueue;

//drawer
void drawCanvas(Canvas *C){
	for(int i = 0; i < MAX_CANVAS_HEIGHT; i++){
		for(int j = 0; j < MAX_CANVAS_WIDTH; j++){
			if (i < vinfo.yres && j < vinfo.xres) {
				int location = (j + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
					(i + vinfo.yoffset) * finfo.line_length;

				if (vinfo.bits_per_pixel == 32) {
					*(fbp + location) = C->getPixel(j, i).getB();
					*(fbp + location + 1) = C->getPixel(j, i).getG();
					*(fbp + location + 2) = C->getPixel(j, i).getR();
					*(fbp + location + 3) = 0;
				}
			}
		}
	}
}

//init
void initAll(){
	//============ Init FrameBuffer
	// Open the file for reading and writing
	fbfd = open("/dev/fb0", O_RDWR);
	if (fbfd == -1) {
		perror("Error: cannot open framebuffer device");
		exit(1);
	}
	printf("The framebuffer device was opened successfully.\n");

	// Get fixed screen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
		perror("Error reading fixed information");
		exit(2);
	}

	// Get variable screen information
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
		perror("Error reading variable information");
		exit(3);
	}

	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

	// Figure out the size of the screen in bytes
	if (vinfo.xres > 900) {
		screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	} else {
		screensize = finfo.line_length * vinfo.yres * vinfo.bits_per_pixel / 8;
	}

	// Map the device to memory
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if (*fbp == -1) {
		perror("Error: failed to map framebuffer device to memory");
		exit(4);
	}
	printf("The framebuffer device was mapped to memory successfully.\n");
	//============ EndOF Init FrameBuffer
}

int getch(void) {
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

void processInput(char chardata){
	Circle* hole;
	Explosion* explosion;
	switch(chardata){
		case 'x':
			terminate();
			break;
		case '-':
			if(scale > 1) scale--;
			break;
		case '=':
			if(scale < 10) scale++;
			break;
		case 'p':
			p ^= 1;
			break;
		case 'j':
			j ^= 1;
			break;
		case 'b':
			b ^= 1;
			break;
		case 'e':
			hole = new Circle(100, Heli->center);
			explosion = new Explosion(Heli->center);
			hole->color = Color(20, 20, 20);
			holes.push_back(hole);
			explosions.push_back(explosion);
			break;
		case 'w':
			Heli->moveByY(-10);
			HeliProp->moveByY(-10);
			heliMoved = true;
			break;
		case 'a':
			Heli->moveByX(-10);
			HeliProp->moveByX(-10);
			heliMoved = true;
			break;
		case 'd':
			Heli->moveByX(10);
			HeliProp->moveByX(10);
			heliMoved = true;
			break;
		case 's':
			Heli->moveByY(10);
			HeliProp->moveByY(10);
			heliMoved = true;
			break;
		case '[':
			Heli->rotate(Heli->center, 5);
			break;
		case ']':
			Heli->rotate(Heli->center, -5);
			break;
		default:
			break;
	}
}

void keyReader() {
	while (1) {
		char c = getch();
		{
			std::lock_guard<std::mutex> lck(qMutex);

			keyQueue.push_back(c);
		}
	}
}

void startKeystrokeThread(){
	std::thread t1(keyReader);
	t1.detach();
}

int main(){
	initAll();

	Canvas canvas;

	Canvas mapCanvas;
	Canvas heliCanvas;
	Canvas propCanvas;
	Canvas holeCanvas;
	Canvas explosionCanvas;
	Canvas creditCanvas;

	std::vector<Canvas*> canvases;
	canvases.push_back(&mapCanvas);
	canvases.push_back(&holeCanvas);
	canvases.push_back(&explosionCanvas);
	canvases.push_back(&heliCanvas);
	canvases.push_back(&propCanvas);

	Drawer mainDrawer(&canvas);
	mainDrawer.xClipWidth = 600;
	mainDrawer.yClipHeight = 600;

	Drawer helicamDrawer(&canvas);
	helicamDrawer.xOffset = 600;
	helicamDrawer.xClipWidth = 200;
	helicamDrawer.yClipHeight = 200;
	helicamDrawer.drawScale = 2;

	Drawer mapMainDrawer(mainDrawer);
	mapMainDrawer.destination = &mapCanvas;
	Drawer mapHelicamDrawer(helicamDrawer);
	mapHelicamDrawer.destination = &mapCanvas;

	Drawer holeMainDrawer(mainDrawer);
	holeMainDrawer.destination = &holeCanvas;
	Drawer holeHelicamDrawer(helicamDrawer);
	holeHelicamDrawer.destination = &holeCanvas;

	Drawer explosionDrawer(mainDrawer);
	explosionDrawer.destination = &explosionCanvas;

	Drawer heliDrawer(mainDrawer);
	heliDrawer.destination = &heliCanvas;
	Drawer propDrawer(mainDrawer);
	propDrawer.destination = &propCanvas;

	ITBMap itbMap("src/bangunanitb.txt","src/potato","src/tree.txt");

	b = true, p = true, j = true;
	startKeystrokeThread();

	bool dirty = true;
	bool loopdone = false;

	while(!loopdone){
		//if (dirty) {
		mapHelicamDrawer.xTranslate = -(Heli->center.getX()-100);
		mapHelicamDrawer.yTranslate = -(Heli->center.getY()-100);
		holeHelicamDrawer.xTranslate = -(Heli->center.getX()-100);
		holeHelicamDrawer.yTranslate = -(Heli->center.getY()-100);

		HeliProp->animate();

		// Map rendering
		mapCanvas.clear_all();
		mapMainDrawer.draw_shapes(itbMap.get_all_drawn_shapes());
		mapHelicamDrawer.draw_shapes(itbMap.get_all_drawn_shapes());

		// Hole rendering
		holeCanvas.clear_all();
		holeMainDrawer.draw_circles(holes);
		holeHelicamDrawer.draw_circles(holes);

		// Explosion rendering
		explosionCanvas.clear_all();
		std::vector<Explosion*> newExplosions;
		for (size_t i = 0; i < explosions.size(); i++) {
			Explosion* e = explosions[i];
			bool drawn = !e->animate();
			if (drawn) {
				explosionDrawer.draw_shape(e);
				// explosionCanvas.boundary_fill(
				// 	e->center.getX(),
				// 	e->center.getY(),
				// 	e->color,
				// 	explosionCanvas.transparent
				// );

				newExplosions.push_back(e);
			} else {
				delete e;
				if (holes.size() > 5) {
					loopdone = true;
				}
			}
		}
		explosions = newExplosions;

		// Helicopter rendering
		Point heliCenter = Heli->center;
		heliCanvas.xStart = heliCenter.getX()-200;
		heliCanvas.yStart = heliCenter.getY()-200;
		heliCanvas.xEnd = heliCenter.getX()+200;
		heliCanvas.yEnd = heliCenter.getY()+200;
		propCanvas.xStart = heliCenter.getX()-150;
		propCanvas.yStart = heliCenter.getY()-150;
		propCanvas.xEnd = heliCenter.getX()+150;
		propCanvas.yEnd = heliCenter.getY()+150;

		heliCanvas.clear_all();
		heliDrawer.draw_shape(Heli);
		heliCanvas.boundary_fill(
			Heli->center.getX(),
			Heli->center.getY(),
			Color(120, 120, 120),
			heliCanvas.transparent
		);

		propCanvas.clear_all();
		propDrawer.draw_shape(HeliProp);
		propCanvas.boundary_fill(
			HeliProp->center.getX(),
			HeliProp->center.getY(),
			Color(180, 180, 180),
			propCanvas.transparent
		);


		Canvas::mergeCanvas(&canvas, canvases);

		drawCanvas(&canvas);

			//dirty = false;
		//}

		{
			std::lock_guard<std::mutex> lck(qMutex);
			while (!keyQueue.empty()) {
				processInput(keyQueue.front());
				keyQueue.pop_front();
				//dirty = true;
			}
		}

		// About 60 fps
		usleep(16000);
	}

	Credit lastCredit("datastructure/credit/credit.bmp");

	int i,j;
	for (i=0;i<lastCredit.getHeight();i++) {
		for (j=0;j<lastCredit.getWidth();j++) {
			creditCanvas.setPixel(i,j,new Color(lastCredit.getData()[j * lastCredit.getWidth() + i], 
												lastCredit.getData()[j * lastCredit.getWidth() + i + 1],
												lastCredit.getData()[j * lastCredit.getWidth() + i + 2]));
		}
	}

	drawCanvas(&creditCanvas);

	printf("Selamat, anda telah menghancurkan ITB!\n");

	return 0;
}
