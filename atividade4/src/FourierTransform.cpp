#include "Common.h"



//https://www.docs.opencv.org/2.4/doc/tutorials/core/discrete_fourier_transform/discrete_fourier_transform.html
void discreteFourierTransform(cv::Mat& src){
	Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( src.rows );
    int n = getOptimalDFTSize( src.cols ); // on the border add zero values
    copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(src))^2 + Im(DFT(src))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(src), planes[1] = Im(DFT(src))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    // imshow("Input Image"       , src   );    // Show the result
    imshow("output.jpg", magI);
	// imwrite("output.jpeg", magI);
    waitKey();


}

// int main(int argc, char const *argv[]){

	
// 	if( argc < 2)  {
//      cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
//      return -1;
//     }

//     // Mat src1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);  
// 	//transformada de fourie discreta
// 	Mat src1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); 

//     if(!src1.data )  {
//         cout <<  "Could not open or find the image" << std::endl ;
//         return -1;
//     }

	
// 	// //transfere os bits
// 	// Mat src2 = imread(argv[2], CV_LOAD_IMAGE_COLOR); 
// 	// int layers = atoi(argv[3]);
// 	// bitTransfere(src1, src2, layers);
	
// 	// //separa as camadas de bits
// 	// getLayers(src);

	 
// 	discreteFourierTransform(src1);
    
//     return 0;
// }

int height;

int dft_M, dft_N;

float MAX = 100.0;
float yl = 0;
float max_yl = 100;
int yl_slider = 0;

int d0_slider = 0;
float max_d0 = 256;
float d0 = 0;

float yh = 0;
float max_yh = 100;
int yh_slider = 0;


Mat image, imageDft, padded;

char TrackbarName[50];

// troca os quadrantes da imagem da DFT
void deslocaDFT(Mat& image ){
    Mat tmp, A, B, C, D;

    // se a imagem tiver tamanho impar, recorta a regiao para
    // evitar cÃ³pias de tamanho desigual
    image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
    int cx = image.cols/2;
    int cy = image.rows/2;

    // reorganiza os quadrantes da transformada
    // A B   ->  D C
    // C D       B A
    A = image(Rect(0, 0, cx, cy));
    B = image(Rect(cx, 0, cx, cy));
    C = image(Rect(0, cy, cx, cy));
    D = image(Rect(cx, cy, cx, cy));

    // A <-> D
    A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);

    // C <-> B
    C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
}

void calcHomomorphicFilter() {
    Mat filter = Mat(padded.size(), CV_32FC2, Scalar(0));
    Mat tmp = Mat(dft_M, dft_N, CV_32F);

    for (int i = 0; i < dft_M; i++) {
        for (int j = 0; j < dft_N; j++) {
            float d2 = pow(i - dft_M/2.0, 2) + pow(j - dft_N/2.0, 2);
            float exp = - (d2/pow(d0, 2));
            float valor = (yh - yl)*(1 - expf(exp) ) + yl;
            tmp.at<float> (i,j) = valor;
        }
    }

    Mat comps[] = {tmp, tmp};
    merge(comps, 2, filter);

    Mat dftClone = imageDft.clone();

    mulSpectrums(dftClone,filter,dftClone,0);

    deslocaDFT(dftClone);

    idft(dftClone, dftClone);

    vector<Mat> planos;

    split (dftClone, planos);

    normalize(planos[0], planos[0], 0, 1, CV_MINMAX);

    char bufferd0[20], bufferyh[20], bufferyl[20];
    // sprintf(bufferd0, "D0: %f", d0);
    // sprintf(bufferyh, "Yh: %f", yh);
    // sprintf(bufferyl, "Yl: %f", yl);
    // putText(planos[0], bufferd0,cv::Point(0,10), CV_FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255),1,8,false);
    // putText(planos[0], bufferyh,cv::Point(0,20), CV_FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255),1,8,false);
    // putText(planos[0], bufferyl,cv::Point(0,30), CV_FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255),1,8,false);
    imshow("Filtro Homomorfico", planos[0]);
    imshow("Original", image);
}

void on_trackbar_yl(int, void*){
    yl = (float) yl_slider;
    yl = max_yl*yl/MAX;
    calcHomomorphicFilter();
}

void on_trackbar_d0(int, void *){
    d0 = d0_slider*max_d0/MAX;
    calcHomomorphicFilter();
}

void on_trackbar_yh(int, void*) {
    yh = yh_slider*max_yh/MAX;

    calcHomomorphicFilter();
}

int main(int argvc, char** argv){
    image = imread(argv[1]);
    cvtColor(image, image, CV_BGR2GRAY);

    height = image.size().height;

    // identifica os tamanhos otimos para
    // calculo do FFT
    dft_M = getOptimalDFTSize(image.rows);
    dft_N = getOptimalDFTSize(image.cols);

    // realiza o padding da imagem
    Mat_<float> zeros;
    copyMakeBorder(image, padded, 0,
                   dft_M - image.rows, 0,
                   dft_N - image.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    // parte imaginaria da matriz complexa (preenchida com zeros)
    zeros = Mat_<float>::zeros(padded.size());

    // prepara a matriz complexa para ser preenchida
    imageDft = Mat(padded.size(), CV_32FC2, Scalar(0));

    copyMakeBorder(image, padded, 0,
                   dft_M - image.rows, 0,
                   dft_N - image.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    Mat_<float> realInput = Mat_<float>(padded);

    // insere as duas componentes no array de matrizes
    vector<Mat> planos;
    planos.push_back(realInput);
    planos.push_back(zeros);

    // combina o array de matrizes em uma unica
    // componente complexa
    merge(planos, imageDft);

    // calcula o dft
    dft(imageDft, imageDft);
    deslocaDFT(imageDft);

    namedWindow("Filtro Homomorfico", 1);

    sprintf( TrackbarName, "Yh");
    createTrackbar( TrackbarName, "Filtro Homomorfico",
                    &yh_slider,
                    MAX,
                    on_trackbar_yh);

    sprintf( TrackbarName, "YL");
    createTrackbar( TrackbarName, "Filtro Homomorfico",
                    &yl_slider,
                    MAX,
                    on_trackbar_yl);

    sprintf( TrackbarName, "D0");
    createTrackbar( TrackbarName, "Filtro Homomorfico",
                    &d0_slider,
                    MAX,
                    on_trackbar_d0 );
    calcHomomorphicFilter();
    waitKey(0);

    return 0;
}