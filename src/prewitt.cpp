#include "prewitt.h"


int i, j;
CImg<unsigned char> image("L.jpg");
int width = image.width();
int height = image.height();
int depth = image.depth();
CImg<unsigned char> gray(width,height,depth,1);
CImg<unsigned char> ghost(width+2,height+2,depth,1);
CImg<unsigned char> auxh(width,height,depth,1);
CImg<unsigned char> auxv(width,height,depth,1);
CImg<unsigned char> final(width,height,depth,1);

const int MH[3][3] = {1,1,1, 0,0,0, -1,-1,-1}, MV[3][3] = {-1,0,1, -1,0,1, -1,0,1};


void run(){
	init();
	ghost_image();
	convolve();
	display();
}

void ghost_image(){
	for (i = 0; i < width+1; ++i)
	{
		for (j = 0; j < height+1; ++j)
		{
			if (i == 0){
				ghost(0, j, 0, 0) = gray(1, j, 0, 0);
			} else if (i == width) {
				ghost(width, j, 0, 0) = gray(width-1, j, 0, 0);
			} else if (j == 0){
				ghost(i, 0, 0, 0) = gray(i, 1, 0, 0);
			} else if (j == width) {
				ghost(i, width, 0, 0) = gray(i, width-1, 0, 0);
			} else {
				ghost(i, j, 0, 0) = gray(i, j, 0, 0);
			}
		}
	}
}

void convolve(){
	for (i = 1; i < width; ++i)
	{
		for (j = 1; j < height; ++j)
		{
			auxh(i, j, 0, 0) = ghost(i, j, 0, 0)*MH[1][1];
	    auxh(i, j, 0, 0) += ghost(i, j-1, 0, 0)*MH[1][0];
	    auxh(i, j, 0, 0) += ghost(i+1, j-1, 0, 0)*MH[2][0];
	    auxh(i, j, 0, 0) += ghost(i+1, j, 0, 0)*MH[2][1];
	    auxh(i, j, 0, 0) += ghost(i+1, j+1, 0, 0)*MH[2][2];
	    auxh(i, j, 0, 0) += ghost(i, j+1, 0, 0)*MH[1][2];
	    auxh(i, j, 0, 0) += ghost(i-1, j+1, 0, 0)*MH[0][2];
	    auxh(i, j, 0, 0) += ghost(i-1, j, 0, 0)*MH[0][1];
	    auxh(i, j, 0, 0) += ghost(i-1, j-1, 0, 0)*MH[0][0];

			auxv(i, j, 0, 0) = ghost(i, j, 0, 0)*MV[1][1];
	    auxv(i, j, 0, 0) += ghost(i, j-1, 0, 0)*MV[1][0];
	    auxv(i, j, 0, 0) += ghost(i+1, j-1, 0, 0)*MV[2][0];
	    auxv(i, j, 0, 0) += ghost(i+1, j, 0, 0)*MV[2][1];
	    auxv(i, j, 0, 0) += ghost(i+1, j+1, 0, 0)*MV[2][2];
	    auxv(i, j, 0, 0) += ghost(i, j+1, 0, 0)*MV[1][2];
	    auxv(i, j, 0, 0) += ghost(i-1, j+1, 0, 0)*MV[0][2];
	    auxv(i, j, 0, 0) += ghost(i-1, j, 0, 0)*MV[0][1];
	    auxv(i, j, 0, 0) += ghost(i-1, j-1, 0, 0)*MV[0][0];

	    final(i, j, 0, 0) = auxh(i, j, 0, 0) + auxv(i, j, 0, 0);

			if (final(i, j, 0, 0) < 0 || final(i, j, 0, 0) > 255) final(i, j, 0, 0) = 255;
		}
	}
	final.save("final.jpg");
}


void init(){	
	int i, j;
	unsigned char r,g,b;
	unsigned char gr1 = 0;
	unsigned char gr2 = 0;
	for (i = 0; i < width; ++i)
	{
		for (j = 0; j < height; ++j)
		{
			r = image(i,j,0,0); // First channel RED
			g = image(i,j,0,1); // Second channel GREEN
			b = image(i,j,0,2); // Third channel BLUE
			gr1 = round(0.299*((double)r) + 0.587*((double)g) + 0.114*((double)b));
			gray(i,j,0,0) = gr1;
		}
	}
	gray.save("gray.bmp");
}


void display(){
	(image,gray,final).display("RGB to Grayscale");
}