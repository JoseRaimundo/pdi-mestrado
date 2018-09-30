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
	Atividade(Mat &frame, Mat &saida, int filter, int q_lef, int q_rig, int edge_flag);
	~Atividade();
	void operation();

private:
	int channels; 
	int cont_cols;
	int cont_rows;
	int step;
	Mat frame;
	Mat saida;
	int filter, edge_flag;
	
	int q_lef, q_rig, q_height; //quadrant dimensions
	
	/*
		 q_lef <--------> q_rig
	0	  +-----------------+
	^	  |				    |
	|	  |					|
    |     |		Quadrant	|
	|	  |					|
	v	  | 				|
 q_height +-----------------+
		
	*/
	

	
};

#endif