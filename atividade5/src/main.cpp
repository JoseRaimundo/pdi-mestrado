#include "Common.h"

void show_histogram(std::string const& name, cv::Mat1b const& image){
    // Set histogram bins count
    int bins = 256;
    int histSize[] = {bins};
    // Set ranges for histogram bins
    float lranges[] = {0, 256};
    const float* ranges[] = {lranges};
    // create matrix for histogram
    cv::Mat hist;
    int channels[] = {0};

    // create matrix for histogram visualization
    int const hist_height = 256;
    cv::Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);

    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

    double max_val=0;
    minMaxLoc(hist, 0, &max_val);

    // visualize each bin
    for(int b = 0; b < bins; b++) {
        float const binVal = hist.at<float>(b);
        int   const height = cvRound(binVal*hist_height/max_val);
        cv::line
            ( hist_image
            , cv::Point(b, hist_height-height), cv::Point(b, hist_height)
            , cv::Scalar::all(255)
            );
    }
    cv::imshow(name, hist_image);
}

int main(int argc, char const *argv[]){
    Common::usage();

	if( argc < 2)  {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

	Mat src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); 

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
	 
	imshow("Teste1", src);
    imshow("Teste2", histImage);
    show_histogram("Teste3", src);
    waitKey(0);     
    return 0;
}

