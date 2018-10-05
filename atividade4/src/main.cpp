#include "Atividade.h"
#include <stdio.h>
#include <bitset>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
	
	if( argc != 2)  {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat src, output;
    src = imread(argv[1], CV_LOAD_IMAGE_COLOR);  

    if(! src.data )  {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

	output = Mat(src.rows, src.cols, CV_8UC3);  

	uint8_t *origin 	= (uint8_t*)src.data;
	uint8_t *destino 	= (uint8_t*)output.data;


	bitset<8> byte_in, byte_out;
	// bitset<16> invert_valor;
	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
			byte_in = origin[i*src.cols*src.channels() + j*src.channels() + 0];
			
			for(int k = 7; k >= 4; k--){
				byte_out[k] = byte_in[k];
			}
			destino[i*output.cols*src.channels() + j*src.channels() + 0] = byte_out.to_ulong();
			
			// cout <<"Origin: 	" << byte_in << endl; 

			// cout <<"Destino: 	" << byte_out << endl; 

			//blue
			//destino[i*output.cols*src.channels() + j*src.channels() + 0] = origin[i*src.cols*src.channels() + j*src.channels() + 0];
			//green
			//destino[i*output.cols*src.channels() + j*src.channels() + 1] = origin[i*src.cols*src.channels() + j*src.channels() + 1];
			//red
			//destino[i*output.cols*src.channels() + j*src.channels() + 2] = origin[i*src.cols*src.channels() + j*src.channels() + 2];
		}
	}

		
	// cout << byte_in << endl;	//0010110100000000

   imshow( "Display window", output );                   // Show our image inside it.


	waitKey(0);     
	return 0;
}