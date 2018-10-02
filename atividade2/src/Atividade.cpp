#include "Atividade.h"
#include <cmath>
#include <sys/time.h>

#define MAX_MAT 12





Atividade::Atividade(Mat &src, Mat &output){
	this->src = src;
    this->output = output;
}

void Atividade::getGray(){
	uint8_t *origin 	= (uint8_t*)src.data;
	uint8_t *destino 	= (uint8_t*)output.data;
	int cont = 0;
	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
	        int valor	  =  	0.2125 * origin[i*src.cols*src.channels() + j*src.channels() + 2] +
								0.7154 * origin[i*src.cols*src.channels() + j*src.channels() + 1] +
								0.0732 * origin[i*src.cols*src.channels() + j*src.channels() ];
			destino[cont++] = valor;
		}
	}
}


void Atividade::getRed(){
	uint8_t *origin 	= (uint8_t*) src.data;
	uint8_t *destino 	= (uint8_t*) output.data;
	for(int i = 0; i < src.rows; i++){
		for(int j = 0; j < src.cols; j++){
	       destino[i*output.cols*src.channels() + j*src.channels() + 2] = origin[i*src.cols*src.channels() + j*src.channels() + 2];
		}
	}
}

void Atividade::getBlue(){
	

}
void Atividade::getGreen(){

}
