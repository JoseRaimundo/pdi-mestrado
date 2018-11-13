#ifndef COMMON_H

#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <sys/time.h>

#include <opencv2/opencv.hpp>
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>


#define MAX_GRAY_SCALA 255
#define MAX_BIT_LAYERS 8

using namespace std;
using namespace cv;

class Common {

public:
	static void usage();

private:
	Common();
	~Common();
};

#endif