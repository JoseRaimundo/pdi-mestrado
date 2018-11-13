#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
//sobel
int main(int argc, char** argv)
{
	Mat src, src_gray;
	Mat grad;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	src = imread(argv[1]);
	if(!src.data)
	{
		return -1;
	}
	GaussianBlur(src, src, Size(3,3) , 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);

	namedWindow("sobel1", CV_WINDOW_AUTOSIZE);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	Scharr(src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
//	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	Scharr(src_gray, grad_y, ddepth, 0, 1,scale, delta, BORDER_DEFAULT);
//	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, .5, 0, grad);
	// imshow("sobel", grad);
    imwrite( "saida.png", grad);
	waitKey(0);

	return 0;

}