#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
 
using namespace cv;
using namespace std;




void getRed(Mat &src, Mat &output){
	uint8_t *origin 	= (uint8_t*) src.data;
	uint8_t *destino 	= (uint8_t*) output.data;
  int cont = 0;
	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
      if(int(origin[i*src.cols*src.channels() + j*src.channels() + 2]) > 220 && int(origin[i*src.cols*src.channels() + j*src.channels() + 1]) < 150 &&  int(origin[i*src.cols*src.channels() + j*src.channels() + 0]) < 150 ){
          destino[cont++] = origin[i*src.cols*src.channels() + j*src.channels() + 2];
      }else{
          destino[cont++] = 0;
      }
      // cout << int(origin[i*src.cols*src.channels() + j*src.channels() + 2]) << endl;   
		}
	}
}
 
int main()
{
  Mat src, gray, red, green;

  src = imread( "teste.jpg", 1 );//resize(src,src,Size(640,480));
  cvtColor( src, gray, CV_BGR2GRAY );
  cvtColor( src, red, CV_BGR2GRAY );

  getRed(src, gray);
 
  // Reduce the noise so we avoid false circle detection
  GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
 
  vector<Vec3f> circles;
 
  // Apply the Hough Transform to find the circles
  HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 50, 20, 50, 0, 0 );
 
  // Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);     
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );// circle center     
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );// circle outline
      cout << "center : " << center << "\nradius : " << radius << endl;
   }
 
  // Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );

  imshow( "Hough Circle Transform red", gray );
   imshow( "Hough Circle Transform Demo", src );
  waitKey(0);
  return 0;
}







// void classificaCores(Mat &src, Mat &output){

//   Mat samples(src.rows * src.cols, 3, CV_32F);
//   for( int y = 0; y < src.rows; y++ )
//     for( int x = 0; x < src.cols; x++ )
//       for( int z = 0; z < 3; z++)
//         samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];


//   int clusterCount = 8;
//   Mat labels;
//   int attempts = 5;
//   Mat centers;
//   kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );


//   // Mat new_image( src.size(), src.type() );
//   for( int y = 0; y < src.rows; y++ )
//     for( int x = 0; x < src.cols; x++ )
//     { 
//       int cluster_idx = labels.at<int>(y + x*src.rows,0);
//       output.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
//       output.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
//       output.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
//     }
//   imshow( "clustered image", output );
//   waitKey( 0 );
// }