#include "bufferMem.h"

int bufferMem::fbfd = 0;
struct fb_var_screeninfo bufferMem::vinfo;
struct fb_fix_screeninfo bufferMem::finfo;
long int bufferMem::screensize = 0;
char* bufferMem::fbp = NULL;

bufferMem::bufferMem() {
	
}

bufferMem::~bufferMem() {

}

void bufferMem::startBuffer() {
	fbfd = open("/dev/fb0", O_RDWR);
	if (fbfd == -1) {
	 perror("Error: cannot open framebuffer device");
	 exit(1);
	}

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

	// Figure out the size of the screen in bytes
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	// Map the device to memory
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
	                fbfd, 0);
	if (atoi(fbp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

	displayWidth = vinfo.xres;
	displayHeight = vinfo.yres;
}

void bufferMem::closeBuffer() {
	munmap(fbp, screensize);
	close(fbfd);
}

void bufferMem::printSquare (int edge, int loc_x, int loc_y, color C) {
	long int location;
    int i,j;
    // if (((loc_x)>=149) && ((loc_x + edge)<vinfo.xres - 140) && ((loc_y)>=50) && ((loc_y + edge)<vinfo.yres - 80)) {
    if (((loc_x)>= 0 ) && ((loc_x + edge)<vinfo.xres - 20) && ((loc_y) >= 0) && ((loc_y + edge)<vinfo.yres - 20)) {
		for (i = loc_x; i < (loc_x+edge); i++) {
			for (j = loc_y; j < (loc_y+edge); j++) {
				location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;
				if (fbp + location) { //check for segmentation fault
					if (vinfo.bits_per_pixel == 32) {
						*(fbp + location) = C.getB();            //Blue
						*(fbp + location + 1) = C.getG();        //Green
						*(fbp + location + 2) = C.getR();        //Red
						*(fbp + location + 3) = 0;          //Transparancy
					} else  { //assume 16bpp
						int r = C.getR();     //Red
						int g = C.getG();     //Green
						int b = C.getB();     //Blue

						unsigned short int t = r<<11 | g << 5 | b;
						*((unsigned short int*)(fbp + location)) = t;
					}
				} else {
					return;
				}
			}
		}
	}
}

void bufferMem::printSquareZoom(int edge, int loc_x, int loc_y, color C, double multiplier) {
	long int location;
    int i,j;
    loc_x -= (edge*multiplier-edge)/2;
    loc_y -= (edge*multiplier-edge)/2;
    edge = multiplier*edge;
    // i (((loc_x)>=149) && ((loc_x + edge)<vinfo.xres - 140) && ((loc_y)>=50) && ((loc_y + edge)<vinfo.yres - 80)) {
    if (((loc_x)>= 0 ) && ((loc_x + edge)<vinfo.xres - 20) && ((loc_y) >= 0) && ((loc_y + edge)<vinfo.yres - 20)) {
		for (i = loc_x; i < (loc_x+edge); i++) {
			for (j = loc_y; j < (loc_y+edge); j++) {
				location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;
				if (fbp + location) { //check for segmentation fault
					if (vinfo.bits_per_pixel == 32) {
						*(fbp + location) = C.getB();            //Blue
						*(fbp + location + 1) = C.getG();        //Green
						*(fbp + location + 2) = C.getR();        //Red
						*(fbp + location + 3) = 0;          //Transparancy
					} else  { //assume 16bpp
						int r = C.getR();     //Red
						int g = C.getG();     //Green
						int b = C.getB();     //Blue

						unsigned short int t = r<<11 | g << 5 | b;
						*((unsigned short int*)(fbp + location)) = t;
					}
				} else {
					return;
				}
			}
		}
	}
}


void bufferMem::printBackground(color C) {
	long int location;
    int width = displayWidth - 6;
    int height = displayHeight - 6;
    int i,j;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;
            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = C.getB();         //Blue
                *(fbp + location + 1) = C.getG();     //Green
                *(fbp + location + 2) = C.getR();     //Red
                *(fbp + location + 3) = 0;       //No transparency
            } else  { //assume 16bpp
                int r = C.getR();     //Red
                int g = C.getG();     //Green
                int b = C.getB();     //Blue

                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
        }
    }
}


color bufferMem::get_pixel (int loc_x, int loc_y) {
	color initial;

    long int location;
    int i,j;
    if (((loc_x)>=0) && ((loc_x + 1)<vinfo.xres) && ((loc_y)>=0) && ((loc_y + 1)<vinfo.yres)) {
		for (i = loc_x; i < (loc_x + 1); i++) {
			for (j = loc_y; j < (loc_y + 1); j++) {
				location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;

				if (fbp + location) {  	//check for segmentation fault
					initial.setColor((*(fbp + location + 2)), (*(fbp + location + 1)), (*(fbp + location)));
				} else {
					initial.setColor(0, 0, 0);
				}
			}
		}
	}
	return initial;
}

void bufferMem::put_pixel (int loc_x, int loc_y, color C) {
	long int location;
	location = (loc_x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (loc_y+vinfo.yoffset) * finfo.line_length;
	if (vinfo.bits_per_pixel == 32) {
		*(fbp + location) = C.getB();         //Blue
		*(fbp + location + 1) = C.getG();     //Green
		*(fbp + location + 2) = C.getR();     //Red
		*(fbp + location + 3) = 0;       //No transparency
	} else  { //assume 16bpp
		int r = C.getR();     //Red
		int g = C.getG();     //Green
		int b = C.getB();     //Blue

		unsigned short int t = r<<11 | g << 5 | b;
		*((unsigned short int*)(fbp + location)) = t;
	}
}
