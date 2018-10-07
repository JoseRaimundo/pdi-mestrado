#include "Atividade.h"
#include <stdio.h>
#include <bitset>
#include <iostream>
#include <string>
#include <sstream>

#define MAX_BIT 8

using namespace std;

int main(int argc, char const *argv[]){
	
	if( argc < 2)  {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat src;
	
    src = imread(argv[1], CV_LOAD_IMAGE_COLOR);  

    if(! src.data )  {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

	//carregando camadas
	vector<Mat> layers;
	vector<uint8_t*> destiny;
	
	for(size_t i = 0; i < MAX_BIT; i++){
		layers.push_back(Mat(src.rows, src.cols, CV_8UC3));
		destiny.push_back((uint8_t*)layers[i].data);
	}
	
 	uint8_t *origin 	= (uint8_t*)src.data;
	
	
	bitset<8> byte_in_r, byte_in_g, byte_in_b, 
			  byte_out_r,byte_out_g,byte_out_b ;

	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
			byte_in_b = origin[i*src.cols*src.channels() + j*src.channels() + 0];
			byte_in_g = origin[i*src.cols*src.channels() + j*src.channels() + 1];
			byte_in_r = origin[i*src.cols*src.channels() + j*src.channels() + 2];
					
			for(size_t k = 0; k < MAX_BIT; k++){
				byte_out_r.reset();
				byte_out_g.reset();
				byte_out_b.reset();
				byte_out_r[k] = byte_in_r[k];
				byte_out_g[k] = byte_in_g[k];
				byte_out_b[k] = byte_in_b[k];
				destiny[k][i*layers[k].cols*src.channels() + j*src.channels() + 0] = byte_out_b.to_ulong();
				destiny[k][i*layers[k].cols*src.channels() + j*src.channels() + 1] = byte_out_g.to_ulong();
				destiny[k][i*layers[k].cols*src.channels() + j*src.channels() + 2] = byte_out_r.to_ulong();
			}
			
		}
	}

	
	for(size_t i = 0; i < MAX_BIT; i++)	{
		string nome = "";
		std::stringstream sstm;
		sstm << "Janela" << i;
		nome = sstm.str();

		imshow( nome, layers[i] );
	}
	
	waitKey(0);     
	return 0;
}