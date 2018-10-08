// #include "Atividade.h"
// #include <stdio.h>
// #include <bitset>
// #include <iostream>
// #include <string>
// #include <sstream>

// #define MAX_BIT 5

// using namespace std;


// void getLayers(cv::Mat& src){
// 	vector<Mat> layers;
// 	vector<uint8_t*> destiny;
	
// 	for(size_t i = 0; i < MAX_BIT; i++){
// 		layers.push_back(Mat(src.rows, src.cols, CV_8UC3));
// 		destiny.push_back((uint8_t*)layers[i].data);
// 	}
	
//  	uint8_t *origin 	= (uint8_t*)src.data;
	
	
// 	bitset<8> byte_in_r, byte_in_g, byte_in_b, 
// 			  byte_out_r,byte_out_g,byte_out_b ;

// 	for(int i = 0; i < src.rows; i++){
// 		for(int j = 0; j < src.cols; j++){
// 			byte_in_b = origin[i*src.cols*src.channels() + j*src.channels() + 0];
// 			byte_in_g = origin[i*src.cols*src.channels() + j*src.channels() + 1];
// 			byte_in_r = origin[i*src.cols*src.channels() + j*src.channels() + 2];
					
// 			for(size_t k = 0; k < MAX_BIT; k++){
// 				byte_out_r.reset();
// 				byte_out_g.reset();
// 				byte_out_b.reset();
// 				byte_out_r[k] = byte_in_r[k];
// 				byte_out_g[k] = byte_in_g[k];
// 				byte_out_b[k] = byte_in_b[k];
// 				destiny[k][i*layers[k].cols*src.channels() + j*src.channels() + 0] = byte_out_b.to_ulong();
// 				destiny[k][i*layers[k].cols*src.channels() + j*src.channels() + 1] = byte_out_g.to_ulong();
// 				destiny[k][i*layers[k].cols*src.channels() + j*src.channels() + 2] = byte_out_r.to_ulong();
// 			}
			
// 		}
// 	}

	
// 	for(size_t i = 0; i < MAX_BIT; i++)	{
// 		string nome = "";
// 		std::stringstream sstm;
// 		sstm << "Janela" << i << ".jpeg";
// 		nome = sstm.str();
// 		imwrite( nome, layers[i] );
// 		// imshow( nome, layers[i] );
// 	}
// }

// void bitTransfere(cv::Mat& src1, cv::Mat& src2, int layers){
// 	Mat output = Mat(src1.rows, src1.cols, CV_8UC3);
//  	uint8_t *origin1 	= (uint8_t*)src1.data;
// 	uint8_t *origin2 	= (uint8_t*)src2.data;
// 	uint8_t *destiny 	= (uint8_t*)output.data;
	
// 	bitset<8> byte_in_r1, byte_in_g1, byte_in_b1, 
// 			  byte_in_r2, byte_in_g2, byte_in_b2, 
// 			  byte_out_r,byte_out_g,byte_out_b ;

// 	for(int i = 0; i < src1.rows; i++){
// 		for(int j = 0; j < src1.cols; j++){
// 			byte_in_b1 = origin1[i*src1.cols*src1.channels() + j*src1.channels() + 0];
// 			byte_in_g1 = origin1[i*src1.cols*src1.channels() + j*src1.channels() + 1];
// 			byte_in_r1 = origin1[i*src1.cols*src1.channels() + j*src1.channels() + 2];
// 			byte_in_b2 = origin2[i*src2.cols*src2.channels() + j*src2.channels() + 0];
// 			byte_in_g2 = origin2[i*src2.cols*src2.channels() + j*src2.channels() + 1];
// 			byte_in_r2 = origin2[i*src2.cols*src2.channels() + j*src2.channels() + 2];	

// 			byte_out_r.reset();
// 			byte_out_g.reset();
// 			byte_out_b.reset();

// 			int current_bit = 0;
// 			for(int k = 0; k < layers; k++){
// 				byte_out_r[current_bit] = byte_in_r1[k];
// 				byte_out_g[current_bit] = byte_in_g1[k];
// 				byte_out_b[current_bit] = byte_in_b1[k];
// 				current_bit++;
// 			}

// 			for(int k = 0; k < (8 - layers); k++){
// 				byte_out_r[current_bit] = byte_in_r2[k];
// 				byte_out_g[current_bit] = byte_in_g2[k];
// 				byte_out_b[current_bit] = byte_in_b2[k];
// 				current_bit++;
// 			}

// 			destiny[i *output.cols*src1.channels() + j*src1.channels() + 0] = byte_out_b.to_ulong();
// 			destiny[i *output.cols*src1.channels() + j*src1.channels() + 1] = byte_out_g.to_ulong();
// 			destiny[i *output.cols*src1.channels() + j*src1.channels() + 2] = byte_out_r.to_ulong();
			
// 		}
// 	}

	

// 	//imshow( "saida", output);
	
// 	string nome = "";
// 	std::stringstream sstm;
// 	sstm << "Janela" << layers << ".jpeg";
// 	nome = sstm.str();
// 	imwrite( nome, output);
	
// 	waitKey(0);     
// }


// //https://www.docs.opencv.org/2.4/doc/tutorials/core/discrete_fourier_transform/discrete_fourier_transform.html
// void discreteFourierTransform(cv::Mat& src){
// 	Mat padded;                            //expand input image to optimal size
//     int m = getOptimalDFTSize( src.rows );
//     int n = getOptimalDFTSize( src.cols ); // on the border add zero values
//     copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));

//     Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
//     Mat complexI;
//     merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

//     dft(complexI, complexI);            // this way the result may fit in the source matrix

//     // compute the magnitude and switch to logarithmic scale
//     // => log(1 + sqrt(Re(DFT(src))^2 + Im(DFT(src))^2))
//     split(complexI, planes);                   // planes[0] = Re(DFT(src), planes[1] = Im(DFT(src))
//     magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
//     Mat magI = planes[0];

//     magI += Scalar::all(1);                    // switch to logarithmic scale
//     log(magI, magI);

//     // crop the spectrum, if it has an odd number of rows or columns
//     magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

//     // rearrange the quadrants of Fourier image  so that the origin is at the image center
//     int cx = magI.cols/2;
//     int cy = magI.rows/2;

//     Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
//     Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
//     Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
//     Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

//     Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
//     q0.copyTo(tmp);
//     q3.copyTo(q0);
//     tmp.copyTo(q3);

//     q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
//     q2.copyTo(q1);
//     tmp.copyTo(q2);

//     normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
//                                             // viewable image form (float between values 0 and 1).

//     // imshow("Input Image"       , src   );    // Show the result
//     imshow("output.jpg", magI);
// 	// imwrite("output.jpeg", magI);
//     waitKey();


// }

// // int main(int argc, char const *argv[]){

	
// // 	if( argc < 2)  {
// //      cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
// //      return -1;
// //     }

// //     // Mat src1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);  
// // 	//transformada de fourie discreta
// // 	Mat src1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); 

// //     if(!src1.data )  {
// //         cout <<  "Could not open or find the image" << std::endl ;
// //         return -1;
// //     }

	
// // 	// //transfere os bits
// // 	// Mat src2 = imread(argv[2], CV_LOAD_IMAGE_COLOR); 
// // 	// int layers = atoi(argv[3]);
// // 	// bitTransfere(src1, src2, layers);
	
// // 	// //separa as camadas de bits
// // 	// getLayers(src);

	 
// // 	discreteFourierTransform(src1);
    
// //     return 0;
// // }

// int height;

// int dft_M, dft_N;

// float MAX = 100.0;
// float yl = 0;
// float max_yl = 100;
// int yl_slider = 0;

// int d0_slider = 0;
// float max_d0 = 256;
// float d0 = 0;

// float yh = 0;
// float max_yh = 100;
// int yh_slider = 0;


// Mat image, imageDft, padded;

// char TrackbarName[50];

// // troca os quadrantes da imagem da DFT
// void deslocaDFT(Mat& image ){
//     Mat tmp, A, B, C, D;

//     // se a imagem tiver tamanho impar, recorta a regiao para
//     // evitar cÃ³pias de tamanho desigual
//     image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
//     int cx = image.cols/2;
//     int cy = image.rows/2;

//     // reorganiza os quadrantes da transformada
//     // A B   ->  D C
//     // C D       B A
//     A = image(Rect(0, 0, cx, cy));
//     B = image(Rect(cx, 0, cx, cy));
//     C = image(Rect(0, cy, cx, cy));
//     D = image(Rect(cx, cy, cx, cy));

//     // A <-> D
//     A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);

//     // C <-> B
//     C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
// }

// void calcHomomorphicFilter() {
//     Mat filter = Mat(padded.size(), CV_32FC2, Scalar(0));
//     Mat tmp = Mat(dft_M, dft_N, CV_32F);

//     for (int i = 0; i < dft_M; i++) {
//         for (int j = 0; j < dft_N; j++) {
//             float d2 = pow(i - dft_M/2.0, 2) + pow(j - dft_N/2.0, 2);
//             float exp = - (d2/pow(d0, 2));
//             float valor = (yh - yl)*(1 - expf(exp) ) + yl;
//             tmp.at<float> (i,j) = valor;
//         }
//     }

//     Mat comps[] = {tmp, tmp};
//     merge(comps, 2, filter);

//     Mat dftClone = imageDft.clone();

//     mulSpectrums(dftClone,filter,dftClone,0);

//     deslocaDFT(dftClone);

//     idft(dftClone, dftClone);

//     vector<Mat> planos;

//     split (dftClone, planos);

//     normalize(planos[0], planos[0], 0, 1, CV_MINMAX);

//     char bufferd0[20], bufferyh[20], bufferyl[20];
//     // sprintf(bufferd0, "D0: %f", d0);
//     // sprintf(bufferyh, "Yh: %f", yh);
//     // sprintf(bufferyl, "Yl: %f", yl);
//     // putText(planos[0], bufferd0,cv::Point(0,10), CV_FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255),1,8,false);
//     // putText(planos[0], bufferyh,cv::Point(0,20), CV_FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255),1,8,false);
//     // putText(planos[0], bufferyl,cv::Point(0,30), CV_FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255),1,8,false);
//     imshow("Filtro Homomorfico", planos[0]);
//     imshow("Original", image);
// }

// void on_trackbar_yl(int, void*){
//     yl = (float) yl_slider;
//     yl = max_yl*yl/MAX;
//     calcHomomorphicFilter();
// }

// void on_trackbar_d0(int, void *){
//     d0 = d0_slider*max_d0/MAX;
//     calcHomomorphicFilter();
// }

// void on_trackbar_yh(int, void*) {
//     yh = yh_slider*max_yh/MAX;

//     calcHomomorphicFilter();
// }

// int main(int argvc, char** argv){
//     image = imread(argv[1]);
//     cvtColor(image, image, CV_BGR2GRAY);

//     height = image.size().height;

//     // identifica os tamanhos otimos para
//     // calculo do FFT
//     dft_M = getOptimalDFTSize(image.rows);
//     dft_N = getOptimalDFTSize(image.cols);

//     // realiza o padding da imagem
//     Mat_<float> zeros;
//     copyMakeBorder(image, padded, 0,
//                    dft_M - image.rows, 0,
//                    dft_N - image.cols,
//                    BORDER_CONSTANT, Scalar::all(0));

//     // parte imaginaria da matriz complexa (preenchida com zeros)
//     zeros = Mat_<float>::zeros(padded.size());

//     // prepara a matriz complexa para ser preenchida
//     imageDft = Mat(padded.size(), CV_32FC2, Scalar(0));

//     copyMakeBorder(image, padded, 0,
//                    dft_M - image.rows, 0,
//                    dft_N - image.cols,
//                    BORDER_CONSTANT, Scalar::all(0));

//     Mat_<float> realInput = Mat_<float>(padded);

//     // insere as duas componentes no array de matrizes
//     vector<Mat> planos;
//     planos.push_back(realInput);
//     planos.push_back(zeros);

//     // combina o array de matrizes em uma unica
//     // componente complexa
//     merge(planos, imageDft);

//     // calcula o dft
//     dft(imageDft, imageDft);
//     deslocaDFT(imageDft);

//     namedWindow("Filtro Homomorfico", 1);

//     sprintf( TrackbarName, "Yh");
//     createTrackbar( TrackbarName, "Filtro Homomorfico",
//                     &yh_slider,
//                     MAX,
//                     on_trackbar_yh);

//     sprintf( TrackbarName, "YL");
//     createTrackbar( TrackbarName, "Filtro Homomorfico",
//                     &yl_slider,
//                     MAX,
//                     on_trackbar_yl);

//     sprintf( TrackbarName, "D0");
//     createTrackbar( TrackbarName, "Filtro Homomorfico",
//                     &d0_slider,
//                     MAX,
//                     on_trackbar_d0 );
//     calcHomomorphicFilter();
//     waitKey(0);

//     return 0;
// }

#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cout;
using std::endl;
using namespace cv;

namespace
{
/** Global Variables */
int alpha = 100;
int beta = 100;
int gamma_cor = 100;
Mat img_original, img_corrected, img_gamma_corrected;

void basicLinearTransform(const Mat &img, const double alpha_, const int beta_)
{
    Mat res;
    img.convertTo(res, -1, alpha_, beta_);

    hconcat(img, res, img_corrected);
    imshow("Brightness and contrast adjustments", img_corrected);
}

void gammaCorrection(const Mat &img, const double gamma_)
{
    CV_Assert(gamma_ >= 0);
    //! [changing-contrast-brightness-gamma-correction]
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);

    Mat res = img.clone();
    LUT(img, lookUpTable, res);
    //! [changing-contrast-brightness-gamma-correction]

    hconcat(img, res, img_gamma_corrected);
    imshow("Gamma correction", img_gamma_corrected);
}

void on_linear_transform_alpha_trackbar(int, void *)
{
    double alpha_value = alpha / 100.0;
    int beta_value = beta - 100;
    basicLinearTransform(img_original, alpha_value, beta_value);
}

void on_linear_transform_beta_trackbar(int, void *)
{
    double alpha_value = alpha / 100.0;
    int beta_value = beta - 100;
    basicLinearTransform(img_original, alpha_value, beta_value);
}

void on_gamma_correction_trackbar(int, void *)
{
    double gamma_value = gamma_cor / 100.0;
    gammaCorrection(img_original, gamma_value);
}
}

int main( int argc, char** argv )
{
    CommandLineParser parser( argc, argv, "{@input | ../data/lena.jpg | input image}" );
    img_original = imread( parser.get<String>( "@input" ) );
    if( img_original.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }

    img_corrected = Mat(img_original.rows, img_original.cols*2, img_original.type());
    img_gamma_corrected = Mat(img_original.rows, img_original.cols*2, img_original.type());

    hconcat(img_original, img_original, img_corrected);
    hconcat(img_original, img_original, img_gamma_corrected);

    namedWindow("Brightness and contrast adjustments");
    namedWindow("Gamma correction");

    createTrackbar("Alpha gain (contrast)", "Brightness and contrast adjustments", &alpha, 500, on_linear_transform_alpha_trackbar);
    createTrackbar("Beta bias (brightness)", "Brightness and contrast adjustments", &beta, 200, on_linear_transform_beta_trackbar);
    createTrackbar("Gamma correction", "Gamma correction", &gamma_cor, 200, on_gamma_correction_trackbar);

    on_linear_transform_alpha_trackbar(0, 0);
    on_gamma_correction_trackbar(0, 0);

    waitKey();

    imwrite("linear_transform_correction.png", img_corrected);
    imwrite("gamma_correction.png", img_gamma_corrected);

    return 0;
}