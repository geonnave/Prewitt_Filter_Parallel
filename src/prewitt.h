#ifndef PREWITT_H_INCLUDED
#define PREWITT_H_INCLUDED

#include "CImg.h"
#include "prewitt.h"
#include  <iostream>
#include <math.h>


using namespace cimg_library;
using namespace std;



void init();
void ghost_image();
void run();
void convolve();
void soma();
void sature();
void display();


#endif
