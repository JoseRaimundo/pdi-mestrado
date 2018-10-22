#include "Common.h"


#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cout;
using std::endl;
using namespace cv;

void GammaCorrection(Mat& src, Mat& dst, float fGamma){
    unsigned char lut[256];
    for (int i = 0; i < 256; i++){
       lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
    }
    dst = src.clone();
    const int channels = dst.channels();
    switch (channels){
        case 1:  {
            MatIterator_<uchar> it, end;
            for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
            *it = lut[(*it)];
            break;
        }
        case 3:   {
            MatIterator_<Vec3b> it, end;
                for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)   {
                    (*it)[0] = lut[((*it)[0])];
                    (*it)[1] = lut[((*it)[1])];
                    (*it)[2] = lut[((*it)[2])];
                }
            break;
        }
    }
}

int main( int argc, char** argv ){

    if( argc < 2)  {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

	Mat src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); 
    Mat output = Mat(src.rows, src.cols, CV_8UC3);  
    float gamma_value = atof(argv[3]);
    int version = atoi(argv[4]);

    if(!src.data )  {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    GammaCorrection(src, output, gamma_value);

    // imwrite("linear_transform_correction.tif", src);

    string nome = "";
	std::stringstream sstm;
	sstm << "GammaCorrection" << version << ".tif";
	nome = sstm.str();
	imwrite( nome, output);
    return 0;
}