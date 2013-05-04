#include "CImg.h"

using namespace cimg_library;

int main() {
  CImg<unsigned char> src("arial_0.bmp");
  int i, j, c;
  int width = src.width();
  int height = src.height();
  printf("%d\t%d\n", width, height);
  for (i = 0; i < width; ++i)
  {
    for (j = 0; j < height; ++j)
    {
      c = (int) 0.3*src(i,j,0,0) + 0.59*src(i,j,0,1), 0.11*src(i,j,0,2);
    }
    printf("\n");
  }
  return 0;
}

