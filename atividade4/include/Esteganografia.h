#ifndef ESTEGANOGRAFIA_H

#define ESTEGANOGRAFIA_H

#include <opencv2/opencv.hpp>
#include "Common.h"

#define MAX_BIT 8

using namespace cv;
using namespace std;


class Esteganografia {

public:
    static void bitTransfere(Mat& src1, Mat& src2, int layers);
    static void splitLayers(Mat& src);

private:
	Esteganografia();
	~Esteganografia();
};

#endif