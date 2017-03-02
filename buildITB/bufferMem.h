#ifndef BUFFERMEM_H
#define BUFFERMEM_H

#include "Point.h"
#include "color.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


class bufferMem {
	public :
		bufferMem();
		~bufferMem();

		void startBuffer();
		void closeBuffer();


		void printSquare (int edge, int loc_x, int loc_y, color C);
		void printBackground(color C);
		color get_pixel(int loc_x, int loc_y);
		void put_pixel (int loc_x, int loc_y, color C);
		void printSquareZoom(int edge, int loc_x, int loc_y, color C, double multiplier);
	private :
		static int fbfd;
		static struct fb_var_screeninfo vinfo;
		static struct fb_fix_screeninfo finfo;
		static long int screensize;
		static char *fbp;
		int displayWidth, displayHeight;
};
#endif
