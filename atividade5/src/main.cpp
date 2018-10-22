#include "Common.h"


int main(int argc, char const *argv[]){
    Common::usage();

	if( argc < 2)  {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

	Mat src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); 
    int version = atoi(argv[2]);

    if(!src.data )  {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    int histSize = 256;
    float range[] = { 0, 256 }; 
    const float* histRange = { range };
    Mat hist;
    calcHist( &src, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false );

    int hist_w = 512, hist_h = 400;
    
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 255,255,255) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ ) {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
              Scalar( 255), 2, 8, 0  );
    }
	 
    string nome = "";
	std::stringstream sstm;
	sstm << "histogram" << version << ".jpeg";
	nome = sstm.str();
	imwrite( nome, histImage);

//   waitKey(0);     
    return 0;
}

