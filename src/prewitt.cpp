#include "prewitt.h"
#include <time.h>
#include <omp.h>


int i, j;
int n_threads = 2;
CImg<unsigned char> image("images/lena.tif");
int width = image.width();
int height = image.height();
int depth = image.depth();
CImg<unsigned char> ghost(width+2,height+2,1,1);
CImg<unsigned char> final(width,height,1,1);
char *filename;

const int MH[3][3] = {-1,-1,-1, 0,0,0, 1,1,1}, MV[3][3] = {-1,0,1, -1,0,1, -1,0,1};
int gb[5][5] = {1, 4, 7, 4, 1,
								4, 16, 26, 16, 4,
								7, 26, 41, 26, 7,
								4, 16, 26, 16, 4,
								1, 4, 7, 4, 1};





// void run(){
// 	gauss_blur();
// 	prewitt_parallel_v2();
// 	prewitt();
// 	// display();
// }




double prewitt_parallel_v2(){	
	double start_t, end_t;
	double cpu_time_used;
	start_t = omp_get_wtime();
	#pragma omp parallel num_threads(n_threads)
	{
		int ii, iend, jj=height-1, jend=1, sum=1;
		int h, v, t;
		int nt = omp_get_thread_num();
		int start = ((width/omp_get_num_threads())*nt)+1;
		int end = start+(width/omp_get_num_threads());
		for (ii = start; ii < end; ++ii)
		{
			jj = height-1;
			jend = 1;
			sum = -1;
			if (!(ii % 2)) {
				jj = 1;
				jend = height-1;
				sum = 1;
			} 
			while (jj != jend) //for (jj = 1; jj < height; ++jj)
			{
				// printf("%d:%d\n", ii, jj );
				h =  ghost(ii-1, jj-1, 0, 0)	*	MH[0][0];
				h += ghost(ii-1, jj,   0, 0)	*	MH[0][1];
				h += ghost(ii-1, jj+1, 0, 0)	*	MH[0][2];
				h += ghost(ii,   jj-1, 0, 0)	*	MH[1][0];
				h += ghost(ii,   jj,   0, 0)	*	MH[1][1];
				h += ghost(ii,   jj+1, 0, 0)	*	MH[1][2];
				h += ghost(ii+1, jj-1, 0, 0)	*	MH[2][0];
				h += ghost(ii+1, jj,   0, 0)	*	MH[2][1];
				h += ghost(ii+1, jj+1, 0, 0)	*	MH[2][2];

				v =  ghost(ii-1, jj-1, 0, 0)	*	MV[0][0];
				v += ghost(ii-1, jj,   0, 0)	*	MV[0][1];
				v += ghost(ii-1, jj+1, 0, 0)	*	MV[0][2];
				v += ghost(ii,   jj-1, 0, 0)	*	MV[1][0];
				v += ghost(ii,   jj,   0, 0)	*	MV[1][1];
				v += ghost(ii,   jj+1, 0, 0)	*	MV[1][2];
				v += ghost(ii+1, jj-1, 0, 0)	*	MV[2][0];
				v += ghost(ii+1, jj,   0, 0)	*	MV[2][1];
				v += ghost(ii+1, jj+1, 0, 0)	*	MV[2][2];

				if (h + v < 0){
					final(ii, jj, 0, 0) = 0;
				} else if (h + v > 255) {
					final(ii, jj, 0, 0) = 255;
				} else {
		    	final(ii, jj, 0, 0) = h + v;	
		    }
		    jj += sum;
			}
		}
	}
	end_t = omp_get_wtime();
	cpu_time_used = ( (end_t - start_t));
	final.save("images/prewitt.jpg");
	shuffle_final();
	return cpu_time_used;
}

double prewitt_parallel_v1(){	
	double start_t, end_t;
	double cpu_time_used;
	start_t = omp_get_wtime();
	#pragma omp parallel num_threads(n_threads)
	{
		int ii, jj;
		int h, v;
		int nt = omp_get_thread_num();
		int start = ((width/omp_get_num_threads())*nt)+1;
		int end = start+(width/omp_get_num_threads());
		for (ii = start; ii < end; ++ii)
		{
			for (jj = 1; jj < height; ++jj)
			{
				h =  ghost(ii-1, jj-1, 0, 0)	*	MH[0][0];
		    h += ghost(ii-1, jj,   0, 0)	*	MH[0][1];
		    h += ghost(ii-1, jj+1, 0, 0)	*	MH[0][2];
		    h += ghost(ii,   jj-1, 0, 0)	*	MH[1][0];
		    h += ghost(ii,   jj,   0, 0)	*	MH[1][1];
		    h += ghost(ii,   jj+1, 0, 0)	*	MH[1][2];
		    h += ghost(ii+1, jj-1, 0, 0)	*	MH[2][0];
		    h += ghost(ii+1, jj,   0, 0)	*	MH[2][1];
		    h += ghost(ii+1, jj+1, 0, 0)	*	MH[2][2];

				v =  ghost(ii-1, jj-1, 0, 0)	*	MV[0][0];
		    v += ghost(ii-1, jj,   0, 0)	*	MV[0][1];
		    v += ghost(ii-1, jj+1, 0, 0)	*	MV[0][2];
		    v += ghost(ii,   jj-1, 0, 0)	*	MV[1][0];
		    v += ghost(ii,   jj,   0, 0)	*	MV[1][1];
		    v += ghost(ii,   jj+1, 0, 0)	*	MV[1][2];
		    v += ghost(ii+1, jj-1, 0, 0)	*	MV[2][0];
		    v += ghost(ii+1, jj,   0, 0)	*	MV[2][1];
		    v += ghost(ii+1, jj+1, 0, 0)	*	MV[2][2];

				if (h + v < 0){
					final(ii, jj, 0, 0) = 0;
				} else if (h + v > 255) {
					final(ii, jj, 0, 0) = 0;
				} else {
		    	final(ii, jj, 0, 0) = h + v;
		    }
			}
		}
	}
	end_t = omp_get_wtime();
	cpu_time_used = ( (end_t - start_t));
	// final.save("images/prewitt.jpg");
	shuffle_final();
	return cpu_time_used;
}





double prewitt(){
	int h, v;
	clock_t start_t, end_t;
	double cpu_time_used;
	start_t = clock();
	for (i = 1; i < width; ++i)
	{
		for (j = 1; j < height; ++j)
		{
			h =  ghost(i-1, j-1, 0, 0)	*	MH[0][0];
	    h += ghost(i-1, j,   0, 0)	*	MH[0][1];
	    h += ghost(i-1, j+1, 0, 0)	*	MH[0][2];
	    h += ghost(i,   j-1, 0, 0)	*	MH[1][0];
	    h += ghost(i,   j,   0, 0)	*	MH[1][1];
	    h += ghost(i,   j+1, 0, 0)	*	MH[1][2];
	    h += ghost(i+1, j-1, 0, 0)	*	MH[2][0];
	    h += ghost(i+1, j,   0, 0)	*	MH[2][1];
	    h += ghost(i+1, j+1, 0, 0)	*	MH[2][2];

			v =  ghost(i-1, j-1, 0, 0)	*	MV[0][0];
	    v += ghost(i-1, j,   0, 0)	*	MV[0][1];
	    v += ghost(i-1, j+1, 0, 0)	*	MV[0][2];
	    v += ghost(i,   j-1, 0, 0)	*	MV[1][0];
	    v += ghost(i,   j,   0, 0)	*	MV[1][1];
	    v += ghost(i,   j+1, 0, 0)	*	MV[1][2];
	    v += ghost(i+1, j-1, 0, 0)	*	MV[2][0];
	    v += ghost(i+1, j,   0, 0)	*	MV[2][1];
	    v += ghost(i+1, j+1, 0, 0)	*	MV[2][2];

			if (h + v < 0){
				final(i, j, 0, 0) = 0;
			} else if (h + v > 255) {
				final(i, j, 0, 0) = 0;
			} else {
	    	final(i, j, 0, 0) = h + v;
	    }
		}
	}
	end_t = clock();
	cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
	// final.save("images/prewitt.jpg");
	shuffle_final();
	return cpu_time_used;
}




void init(char *file, int threads){	
	//
	n_threads = threads;
	CImg<unsigned char> img(file);
	filename = file;
	image = img;
	width = image.width();
	height = image.height();
	depth = image.depth();
	CImg<unsigned char> gst(width+2,height+2,1,1);
	ghost = gst;
	CImg<unsigned char> fnl(width,height,1,1);
	final = fnl;
	//
	unsigned char r,g,b;
	unsigned char gr1 = 0;
	unsigned char gr2 = 0;
	for (i = 0; i < width+1; ++i)
	{
		for (j = 0; j < height+1; ++j)
		{
			if (i == 0){
				ghost(0, j, 0, 0) = 0;
			} else if (i == width) {
				ghost(width+1, j, 0, 0) = 0;
			} else if (j == 0){
				ghost(i, 0, 0, 0) = 0;
			} else if (j == height) {
				ghost(i, height+1, 0, 0) = 0;
			} else {
				r = image(i,j,0,0); // First channel RED
				g = image(i,j,0,1); // Second channel GREEN
				b = image(i,j,0,2); // Third channel BLUE
				gr1 = round((((double)r) + ((double)g) + ((double)b))/3);
				ghost(i, j, 0, 0) = gr1;
			}
		}
	}
}


void display(){
	(image,ghost,final).display("Prewitt");
}



void gauss_blur() {
	CImg<unsigned char> aux(width+2,height+2,1,1);

	#pragma omp parallel for
	for (i = 2; i < width-1; ++i)
	{
		for (j = 2; j < height-1; ++j)
		{
			aux(i, j, 0, 0) = convolve_one_pixel(i-2, j-2, 5);
		}
	}
	ghost = aux;
	// ghost.save("images/blur.jpg");
}

int convolve_one_pixel(int k, int l, int win_size) {
	int sum = 0;
	int ii, jj;
	for (ii = 0; ii < win_size; ++ii)
	{
		for (jj = 0; jj < win_size; ++jj)
		{
			sum += ghost(k+ii, l+jj, 0, 0)*gb[ii][jj];
		}
	}
	sum = (int) sum/273;
	return sum;
}

void set_threads(int threads) {
	n_threads = threads;
}

void print(char *mode, double time) {
	printf("%s, image size: [%d x %d]\n", filename, width, height);
	printf("%s, %d threads\n", mode, n_threads);
	cout << "CPU Time: " << time << " seconds\n\n";	
}

void shuffle_final() {
	CImg<unsigned char> fnl(width,height,1,1);
	final = fnl;
}
