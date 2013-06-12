#ifndef PREWITT_H_INCLUDED
#define PREWITT_H_INCLUDED

#include "CImg.h"
#include "prewitt.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <omp.h>


using namespace cimg_library;
using namespace std;


void init(char *file, int threads);
void ghost_image();
void print(char *mode, double time);
double prewitt();
double prewitt_parallel_v1();
double prewitt_parallel_v2();
int convolve_one_pixel(int k, int l, int border_len);
void gauss_blur();
void soma();
void sature();
void display();
void set_threads(int threads);


#endif
