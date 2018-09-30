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

    Mat image, saida, gray;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);  

    if(! image.data )  {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	
	int img_origin[image.rows][image.cols];

	saida = Mat(image.rows, image.cols, CV_8UC3);
	gray = Mat(image.rows, image.cols, 0);  

	uint8_t *origin 	= (uint8_t*)image.data;
	uint8_t *destino 	= (uint8_t*)saida.data;
	uint8_t *cinza 		= 	(uint8_t*)gray.data;
	//cvtColor(image, gray, CV_BGR2GRAY);

	int cont = 0;
	
	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){
			//blue
			//destino[i*saida.cols*image.channels() + j*image.channels() + 0] = origin[i*image.cols*image.channels() + j*image.channels() + 0];
			//green
			//destino[i*saida.cols*image.channels() + j*image.channels() + 1] = origin[i*image.cols*image.channels() + j*image.channels() + 1];
			//red
			//destino[i*saida.cols*image.channels() + j*image.channels() + 2] = origin[i*image.cols*image.channels() + j*image.channels() + 2];
			//Y ← 0.299⋅R+0.587⋅G+0.114⋅B valores sugeridos pelo opencv
	        int chave	  =  	0.2125 * origin[i*image.cols*image.channels() + j*image.channels() + 2] +
								0.7154 * origin[i*image.cols*image.channels() + j*image.channels() + 1] +
								0.0732 * origin[i*image.cols*image.channels() + j*image.channels() + 0];
			
			if (chave > 25) {
				cinza[cont++] = 255;
			}else{
				cinza[cont++] = 0;
			}
						
		}
	}

    // namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  //   imshow( "Display window", saida );                   // Show our image inside it.

    
	imwrite( "saida1.jpg", gray );
	waitKey(0);                                          // Wait for a keystroke in the window    
	return 0;
}