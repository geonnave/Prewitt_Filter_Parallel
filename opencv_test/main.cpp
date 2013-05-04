#include <opencv2/opencv.hpp>

using namespace cv;
 
int main()
{
 
    Mat img = imread("test.jpg",CV_LOAD_IMAGE_COLOR);
    imshow("opencvtest",img);
    waitKey(0);
 
    return 0;
}