#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
    if( argc != 2){
     cout <<"use: ./bin/main imagem_qualquer.png" << endl;
     return -1;
    }

	// Declarando variáveis
	double 	avg 	= 0, 
			si 		= 0, 
			stand 	= 0;

    Mat original, sobel_masc;

	// Mapeando a imagem em uma mat
    original = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! original.data ){
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	
	// Consegue sobel da original, onde está a informação
	Sobel(original, sobel_masc, -1, 1, 1);

	// Pega a média de informação espacial
	for(int i=0; i<original.rows; i++){
		for(int j=0; j<original.cols; j++){
			avg += int(sobel_masc.at<uint8_t>(i, j));
		}		
	}

	avg /= (original.rows*original.cols);

	// Desvio padrão
	for(int i=0; i<original.rows; i++){
		for(int j=0; j<original.cols; j++){
				stand += pow( int(sobel_masc.at<uint8_t>(i, j)) - avg, 2 );
		}		
	}

	// Computar SI
	si = sqrt(stand/(original.rows*original.cols-1));

	cout << "SI :" << si << endl;

    // namedWindow( "Sobel", WINDOW_AUTOSIZE );// Create a window for display.
    // imshow( "Display sobel", sobel_masc.getUMat(0) );                   // Show our image inside it.

    // waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}