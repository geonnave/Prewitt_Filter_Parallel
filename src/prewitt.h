#ifndef PREWITT_H_INCLUDED
#define PREWITT_H_INCLUDED

#include "CImg.h"
#include "prewitt.h"
#include  <iostream>
#include <math.h>


using namespace cimg_library;
using namespace std;


void init(char *file);
void ghost_image();
void run(char* file);
void prewitt();
void prewitt_parallel();
int convolve_one_pixel(int k, int l, int border_len);
void gauss_blur();
void soma();
void sature();
void display();


#endif
