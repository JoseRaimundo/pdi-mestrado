#ifndef ATIVIDADE_H

#define ATIVIDADE_H
#define MAX_MAT 12
#include <stdio.h>
#include <string.h>
#include <iostream>


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <numeric>

using namespace std;
using namespace cv;

class Atividade {

public:
	Atividade(Mat &src, Mat &output);
	~Atividade();
	void getGray();
	void getRed();
	void getBlue();
	void getGreen();

private:
	Mat src;
	Mat output;
};

#endif