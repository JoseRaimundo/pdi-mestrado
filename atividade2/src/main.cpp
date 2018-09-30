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

    Mat image, saida;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);  

    if(! image.data )  {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	
	int img_origin[image.rows][image.cols];

	saida = Mat(image.rows, image.cols,CV_8UC3);

	uint8_t *origin 	= (uint8_t*)image.data;
	uint8_t *destino 	= (uint8_t*)saida.data;

	
	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){
			destino[i*saida.cols*image.channels() + j*image.channels() + 2] = origin[i*image.cols*image.channels() + j*image.channels() + 2];
			// destino[i+image.rows * image.channels() + j+image.cols* image.channels()] = (uint8_t)origin[i+image.rows * image.channels() + j+image.cols* image.channels()];
			// avg[0] += origin[k*frame.cols*channels + l*channels]; 
			// avg[1] += origin[k*frame.cols*channels + l*channels + 1];
			// avg[2] += origin[k*frame.cols*channels + l*channels + 2];
		 
		}
	}

    // namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    // imshow( "Display window", saida );                   // Show our image inside it.

    
	imwrite( "saida3.jpg", saida );
	waitKey(0);                                          // Wait for a keystroke in the window


    return 0;


    
	return 0;
}