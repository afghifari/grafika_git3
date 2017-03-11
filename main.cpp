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

#include "datastructure/point.h"
#include "datastructure/line.h"
#include "datastructure/color.h"
#include "datastructure/shape.h"
#include "datastructure/canvas.h"

using namespace std;

//framebuffer related
int fbfd = 0;
long int screensize = 0;
long int location = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
char *fbp = 0;
Point P1(200,200);
Point P2(300, 200);
int scale = 1;

Canvas *bangunan;
Canvas *clipping;
bool b, j, p;

std::mutex qMutex;
std::deque<char> keyQueue;

//drawer
void drawCanvas(Canvas *C){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if (i < vinfo.yres && j < vinfo.xres) {
				int location = (j + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
					(i + vinfo.yoffset) * finfo.line_length;

				if (vinfo.bits_per_pixel == 32) {
					*(fbp + location) = C->IMAGE[j][i].getB();
					*(fbp + location + 1) = C->IMAGE[j][i].getG();
					*(fbp + location + 2) = C->IMAGE[j][i].getR();
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
		case ' ':
			break;
		case 'w':
			P1.setY(P1.getY() - 10);
			break;
		case 'a':
			P1.setX(P1.getX() - 10);
			break;
		case 'd':
			P1.setX(P1.getX() + 10);
			break;
		case 's':
			P1.setY(P1.getY() + 10);
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
	bangunan = new Canvas("src/bangunanitb.txt","src/potato","src/tree.txt");
	clipping = new Canvas("src/bangunanitb.txt", "src/potato","src/tree.txt");

	b = true, p = true, j = true;
	startKeystrokeThread();

	bool dirty = true;

	while(true){
		if (dirty) {
			bangunan->setArg(p, b, j);

			bangunan->clear_all();

			bangunan->draw_all_shapes(P1, scale);
			drawCanvas(bangunan);

			dirty = false;
		}

		{
			std::lock_guard<std::mutex> lck(qMutex);
			while (!keyQueue.empty()) {
				processInput(keyQueue.front());
				keyQueue.pop_front();
				dirty = true;
			}
		}

		// About 30 fps
		usleep(33000);
	}

	return 0;
}
