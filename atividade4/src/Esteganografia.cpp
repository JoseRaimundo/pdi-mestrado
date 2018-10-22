#include "Esteganografia.h"


void Esteganografia::splitLayers(cv::Mat& src){
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
		sstm << "Janela" << i << ".jpeg";
		nome = sstm.str();
		imwrite( nome, layers[i] );
		// imshow( nome, layers[i] );
	}
}

void Esteganografia::bitTransfere(cv::Mat& src1, cv::Mat& src2, int layers){
	Mat output = Mat(src1.rows, src1.cols, CV_8UC3);
 	uint8_t *origin1 	= (uint8_t*)src1.data;
	uint8_t *origin2 	= (uint8_t*)src2.data;
	uint8_t *destiny 	= (uint8_t*)output.data;
	
	bitset<8> byte_in_r1, byte_in_g1, byte_in_b1, 
			  byte_in_r2, byte_in_g2, byte_in_b2, 
			  byte_out_r,byte_out_g,byte_out_b ;

	for(int i = 0; i < src1.rows; i++){
		for(int j = 0; j < src1.cols; j++){
			byte_in_b1 = origin1[i*src1.cols*src1.channels() + j*src1.channels() + 0];
			byte_in_g1 = origin1[i*src1.cols*src1.channels() + j*src1.channels() + 1];
			byte_in_r1 = origin1[i*src1.cols*src1.channels() + j*src1.channels() + 2];
			byte_in_b2 = origin2[i*src2.cols*src2.channels() + j*src2.channels() + 0];
			byte_in_g2 = origin2[i*src2.cols*src2.channels() + j*src2.channels() + 1];
			byte_in_r2 = origin2[i*src2.cols*src2.channels() + j*src2.channels() + 2];	

			byte_out_r.reset();
			byte_out_g.reset();
			byte_out_b.reset();

			int current_bit = 0;
			for(int k = 0; k < layers; k++){
				byte_out_r[current_bit] = byte_in_r1[k];
				byte_out_g[current_bit] = byte_in_g1[k];
				byte_out_b[current_bit] = byte_in_b1[k];
				current_bit++;
			}

			for(int k = 0; k < (8 - layers); k++){
				byte_out_r[current_bit] = byte_in_r2[k];
				byte_out_g[current_bit] = byte_in_g2[k];
				byte_out_b[current_bit] = byte_in_b2[k];
				current_bit++;
			}

			destiny[i *output.cols*src1.channels() + j*src1.channels() + 0] = byte_out_b.to_ulong();
			destiny[i *output.cols*src1.channels() + j*src1.channels() + 1] = byte_out_g.to_ulong();
			destiny[i *output.cols*src1.channels() + j*src1.channels() + 2] = byte_out_r.to_ulong();
			
		}
	}

	

	//imshow( "saida", output);
	
	string nome = "";
	std::stringstream sstm;
	sstm << "Janela" << layers << ".jpeg";
	nome = sstm.str();
	imwrite( nome, output);
	
	waitKey(0);     
}


Esteganografia::Esteganografia(){
}

Esteganografia::~Esteganografia(){
}