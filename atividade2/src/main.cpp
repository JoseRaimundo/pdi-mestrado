#include "Atividade.h"
#include <stdio.h>
#include <iostream>
//Color out

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"

using namespace std;

int main(int argc, char const *argv[]){

	if( argc != 2)  {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat src, gray;
    src = imread(argv[1], 1);

	if(src.empty())
		cerr << "Error: Loading image" << endl;

	Mat hsi(src.rows, src.cols, src.type());
	gray = Mat(src.rows, src.cols, 0);

	uint8_t *cinza 	= 	(uint8_t*)gray.data;
	uint8_t *input	= (uint8_t*)src.data;


	double r, g, b;
	double h, s, in;
	int cont = 0;

	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
			b = src.at<Vec3b>(i, j)[0];
			g = src.at<Vec3b>(i, j)[1];
			r = src.at<Vec3b>(i, j)[2];

			in = (b + g + r) / 3;
			in =  in/255;
			in = in * 100;

			int min_val = 0;
			min_val = std::min(r, std::min(b,g));

			s = 1 - 3.0/(b + g + r)*min_val;
			if(s < 0.00001){
					s = 0;
			}else if(s > 0.99999){
					s = 1;
			}

			if(s != 0){
				if(b <= g){
					// h = 0.5 * ((r - g) + (r - b)) / sqrt(((r - g)*(r - g)) + ((r - b)*(g - b)));
					// h = acos(h);
					h = acos((((r-g)+(r-b))/2.0)/(sqrt((r-g)*(r-g) + (r-b)*(g-b))));
				} else{
					//h = ((360 * 3.14159265) / 180.0) - h;
					h = 2*3.14159265 - acos((((r-g)+(r-b))/2.0)/(sqrt((r-g)*(r-g) + (r-b)*(g-b))));
				}
			}else{
				// cout << h << " - " << (s*100) << " - " << in << endl;
				h = 0.0;
			}
			h = (h * 180) / 3.14159265;
			s = s * 100;

			
			if (h < 0) {
				h = 0.0;
			}
			

			// h = h / 360.0;
			// h = h * 255;
			hsi.at<Vec3b>(i, j)[0] = h;
			hsi.at<Vec3b>(i, j)[1] = s;
			hsi.at<Vec3b>(i, j)[2] = in;


			cinza[cont++] = int(h);

				cout << r << " "
				<< g  << " "
				<< b << " "
				<< int(h) << " "
				//" - " << int(s) <<
				//" - " << int(in)
				<< endl;

				if(h >= 255 || h < 0){
					cout << "=========== XXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
				}

		}
	}

	namedWindow("RGB image", CV_WINDOW_AUTOSIZE);
	namedWindow("HSI image", CV_WINDOW_AUTOSIZE);

	imshow("RGB image", src);
	imshow("HSI image", gray);

	waitKey(0);
	return 0;
}