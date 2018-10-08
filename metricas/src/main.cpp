#include "Atividade.h"
#include <stdio.h>
#include <bitset>
#include <iostream>

using namespace std;



Scalar calcSSIM( const Mat& i1, const Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d = CV_32F;
    Mat I1, I2;
    i1.convertTo(I1, d);            // cannot calculate on one byte large values
    i2.convertTo(I2, d);
    Mat I2_2   = I2.mul(I2);        // I2^2
    Mat I1_2   = I1.mul(I1);        // I1^2
    Mat I1_I2  = I1.mul(I2);        // I1 * I2
    /*************************** END INITS **********************************/
    Mat mu1, mu2;                   // PRELIMINARY COMPUTING
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);
    Mat mu1_2   =   mu1.mul(mu1);
    Mat mu2_2   =   mu2.mul(mu2);
    Mat mu1_mu2 =   mu1.mul(mu2);
    Mat sigma1_2, sigma2_2, sigma12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;
    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;
    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);                 // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);                 // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
    Mat ssim_map;
    divide(t3, t1, ssim_map);        // ssim_map =  t3./t1;
    Scalar mssim = mean(ssim_map);   // mssim = average of ssim map
    return mssim;
}


double calcPSNR(const Mat& I1, const Mat& I2)
{
    Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2
    Scalar s = sum(s1);         // sum elements per channel
    double sse 	= 	s.val[0] + s.val[1] + s.val[2]; // sum channels
	double mse 	=	sse /(double)(I1.channels() * I1.total());
	double psnr =	10.0*log10((255*255)/mse);
	return psnr;
}




void displayFrame(std::string winName, cv::Mat& frame) {
	cv::imshow(winName, frame);
	cv::waitKey(1);
}

double calcSI(cv::Mat& frame) {
	Mat grad_x, grad_y, abs_grad_x, abs_grad_y, grad;
	Scalar mean, stddev;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	Sobel(frame, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
	Sobel(frame, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	meanStdDev(grad, mean, stddev);

	//displayFrame("gradient magnitude", grad);
	return stddev(0);
}

int main(int argc, char const *argv[]){
	
	if( argc < 2)  {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

	// cv::Mat frame1(height, width, CV_8UC1);
	// cv::Mat frame2(height, width, CV_8UC1);

	// cMat	uframe1, uframe2;
	// cMat maskValidSobel(frame1.size(), CV_8UC1);
	// maskValidSobel(cv::Rect(1,1,width-1,height-1)) = 1;

    Mat src, eva;
    src = imread(argv[1], CV_LOAD_IMAGE_COLOR);  

    if (argc == 2) {
        cout << "SI:   " <<calcSI(src) <<endl;
        return 0;
    }
    eva = imread(argv[2], CV_LOAD_IMAGE_COLOR);  
    

    if(! src.data )  {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	cout << "SI:   " <<calcSI(src) <<endl;
	
	cout << "PSNR: " << calcPSNR(src, eva) << endl;
	cout << "ssim: " << calcSSIM(src, eva) << endl;
	// imshow( "Display eva", src);
	// imshow( "Display src", eva );
	
	//waitKey(0);       


 
	return 0;
}