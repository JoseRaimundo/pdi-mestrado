#include "Atividade.h"
#include <cmath>
#include <sys/time.h>

#define MAX_MAT 12





Atividade::Atividade(Mat &frame, Mat &saida, int filter, int q_lef, int q_rig, int edge_flag){
	//frame components
	this->channels  = frame.channels();
	this->cont_cols = frame.cols;
	this->cont_rows = frame.rows;
	this->filter = filter;
	this->frame = frame;
    this->saida = saida;
    this->step = frame.step;
    
    //window components
	this->q_lef = q_lef;
	this->q_rig = q_rig;
	this->q_height = frame.rows/2;

    //edge detection option
    this->edge_flag = edge_flag;
}

void Atividade::operation(){
}


// double media(int *v, int n) {
//     int soma=0;
//     for(int i = 0; i < n; i++) {
//         soma += v[i];
//     }
//     return (double)soma/n;
// }

// void Atividade::sigma(int q_lef, int q_rig, int edge_flag){
//         Mat gray, edge;;
//         if(edge_flag == 1){
//             cvtColor(frame, gray, CV_BGR2GRAY);
//             Canny(gray, edge, 10, 50, 3);
//         }

//     int block = 2, 
//         T[3],
//         limInf[3],limSup[3], 
//         contY,contCb,contCr, 
//         contx=0,conty=0,
//         valY[4], valCb[4], valCr[4], ind, bordas;
    
//     register int k,l,i,j;
    
//     double avg[3],avg_std[3];
    
//     uint8_t *origin = (uint8_t*)frame.data;
//     uint8_t *destiny = (uint8_t*)saida.data;
 
//     for(i = 0 ;i < q_height*2;i+=block){
//         conty=q_lef;
//         for(j = q_lef*2; j < q_rig*2;j+=block){       
//             if(edge_flag == 1){
//                 bordas += edge.at<uchar>(k, l);
//             }
//             avg[0] = avg[1] = avg[2] = 0;
//             avg_std[0] = avg_std[1] = avg_std[2] = 0;
            
//             for(k=i;k<i+block;k++){
//                 for(l = j;l<j+block;l++){
//                     avg[0] += origin[k*frame.cols*channels + l*channels]; 
//                     avg[1] += origin[k*frame.cols*channels + l*channels + 1];
//                     avg[2] += origin[k*frame.cols*channels + l*channels + 2];
//                 }
//             }

//             if(edge_flag == 1 && bordas == 0){
//                     destiny[contx*saida.cols*channels + conty*channels + 0] = origin[i*frame.cols*channels + j*channels];
//                     destiny[contx*saida.cols*channels + conty*channels + 1] = origin[i*frame.cols*channels + j*channels + 1];
//                     destiny[contx*saida.cols*channels + conty*channels + 2] = origin[i*frame.cols*channels + j*channels + 2];
//                     conty++;
//                     memset(valY, 0, sizeof(valY));
//                     memset(valCr, 0, sizeof(valCr));
//                     memset(valCb, 0, sizeof(valCb));

//                     continue;
//             }
//             bordas = 0;

//             avg[0] /=4;
//             avg[1] /=4;
//             avg[2] /=4;
            
//             if((avg[0]-origin[i*frame.cols*channels + j*channels + 0]) < 20) {    
//                 destiny[contx*saida.cols*channels + conty*channels + 0] = avg[0];
//                 destiny[contx*saida.cols*channels + conty*channels + 1] = avg[1];
//                 destiny[contx*saida.cols*channels + conty*channels + 2] = avg[2];
//                 conty++;
//                 continue;
//             }
//             for(k=i;k<i+block;k++){
//                 for(l = j;l<j+block;l++){
//                     avg_std[0] += pow(avg[0]-origin[k*frame.cols*channels + l*channels + 0],2);
//                     avg_std[1] += pow(avg[1]-origin[k*frame.cols*channels + l*channels + 1],2);
//                     avg_std[2] += pow(avg[2]-origin[k*frame.cols*channels + l*channels + 2],2);
                    
//                 }
//             }
            
//             avg_std[0] = sqrt(avg_std[0]/3);
//             avg_std[1] = sqrt(avg_std[1]/3);
//             avg_std[2] = sqrt(avg_std[2]/3); 
            
//             T[0] = (uchar) 2*avg_std[0];
//             T[1] = (uchar) 2*avg_std[1];
//             T[2] = (uchar) 2*avg_std[2];
            
//             limInf[0] = avg[0]-T[0];
//             limInf[1] = avg[1]-T[1];
//             limInf[2] = avg[2]-T[2];
//             limSup[0] = avg[0]+T[0];
//             limSup[1] = avg[1]+T[1];
//             limSup[2] = avg[2]+T[2];
            
//             for(int n= 0;n<3;n++){
//                 limInf[n]<0?0:limInf[n];
//                 limSup[n]>255?255:limSup[n];
//             }
            
//             contY=contCb=contCr=0;
//             for(k=i;k<i+block;k++){
//                 for(l = j;l<j+block;l++){

//                     if(origin[k*frame.cols*channels + l*channels + 0]>limInf[0] && origin[k*frame.cols*channels + l*channels + 0]<limSup[0]){
//                         valY[contY] = origin[k*frame.cols*channels + l*channels + 0];
//                         contY++;
                                            
//                     }
//                     if(origin[k*frame.cols*channels + l*channels + 1]>limInf[1] && origin[k*frame.cols*channels + l*channels + 1]<limSup[1]){
//                         valCr[contCr] = origin[k*frame.cols*channels + l*channels + 1];
//                         contCr++;               
//                     }
//                     if(origin[k*frame.cols*channels + l*channels + 2]>limInf[2] && origin[k*frame.cols*channels + l*channels + 2]<limSup[2]){
//                         valCb[contCb] = origin[k*frame.cols*channels + l*channels + 2];
//                         contCb++;                               
//                     }   
//                 }
                
//             }
//             destiny[contx*saida.cols*channels + conty*channels + 0] = (contY!=0? media(valY,contY):origin[i*frame.cols*channels + j*channels + 0]);
//             destiny[contx*saida.cols*channels + conty*channels + 1] = (contCr!=0? media(valCr,contCr):origin[i*frame.cols*channels + j*channels + 1]);
//             destiny[contx*saida.cols*channels + conty*channels + 2] = (contCb!=0? media(valCb,contCb):origin[i*frame.cols*channels + j*channels + 2]);
            
//             contY=0;
//             contCb=0;
//             contCr=0;
//             conty++;
//         }
//         contx++;                
//     }
// }





// void Atividade::operation(int q_lef, int q_rig, int edge_flag){

//     Mat gray, edge;;
//     if(edge_flag == 1){
//         cvtColor(frame, gray, CV_BGR2GRAY);
//         Canny(gray, edge, 10, 50, 3);
//     }

// 	uint8_t* origin = (uint8_t*) frame.data;
//     uint8_t* destiny = (uint8_t*) saida.data;

//     int imageStep = step,
//         newWidth  = cont_cols/2, 
//         newHeight = cont_rows/2,
//         new_pixel,
//         index, bordas = 0, block = 2, x, y;
//     int A, B, C, D;

//     register int i,j,k,l;

//     float dx,
//           dy,
//           tx = ((float) (cont_cols)) / ((float)newWidth),
//           ty = ((float) (cont_rows)) / ((float)newHeight),
//           temp;

//     for(i = 0; i < q_height; i++){
//         for( j = q_lef; j <  q_rig; j++){
//             x = (tx*j); //x_ratio
//             y = (ty*i); //y_ratio
//             dx = (tx*j)-(int)x + 0.01;
//             dy = (ty*i)-(int)y + 0.01; 

//             if(edge_flag == 1){
//                 for(k=y;k<y+block;k++){
//                     for(l = x;l<x+block;l++){
//                         bordas += edge.at<uchar>(k, l);
//                     }
//                 }
//             }
                
//             if(edge_flag == 1 && bordas == 0){
//                 for(k = 0; k < 3; k++){
//                     destiny[i*saida.step +j*channels +k] =  origin[y*frame.cols*channels + x*channels + k];
//                 }

//                 continue;
//             }
//             bordas = 0;
//            // cout << (int) origin[y*frame.cols*channels + x*channels] << " ";
//             index = y* imageStep + x*channels;
//             for(k = 0; k < 3; k++){
//                     A = origin[index+k];
//                     B = origin[index+channels];
//                     C = origin[index+imageStep] ;
//                     D = origin[index+imageStep+channels];

//                     new_pixel = A * (1-dx) * (1-dy) + 
//                                 B * (dx)   * (1-dy) +
//                                 C * (dy)   * (1-dx) +
//                                 D * (dx    * dy);
//                     destiny[i*saida.step +j*channels +k] = new_pixel;
//                   //  if(k == 0){
//                   //      cout << new_pixel << endl;
//                   //  }
//             } 
//         }
//     } 
// }

// void Atividade::cubic(int q_lef, int q_rig, int edge_flag){

//     Mat gray, edge;;
//     if(edge_flag == 1){
//         cvtColor(frame, gray, CV_BGR2GRAY);
//         Canny(gray, edge, 10, 50, 3);
//     }

//     int x, y, 
//         newWidth = cont_cols/2, 
//         newHeight= cont_rows/2,
//         bordas = 0, block = 2;

//     uint8_t* origin = (uint8_t*) frame.data;
//     uint8_t* destiny = (uint8_t*) saida.data;
   
//     //int a,b,c,d,index;
//     unsigned char Ca,Cb,Cc, C[6];
    
//     int d0,d2, d3, a0, a1, a2, a3;
    
//     register int i,j,k,l;
    
//     float dx,
//           dy,
//           tx = frame.cols / newWidth,
//           ty = frame.rows / newHeight;
 
//     for(i = 0; i < q_height; i++){
//         for( j = q_lef; j < q_rig; j++){
            
//             x = (int) (tx*j);
//             y = (int) (ty*i);
            
//             dx = tx*j-x;
//             dy = ty*i-y;
            
//             if(edge_flag == 1){
//                 for(k=y;k<y+block;k++){
//                     for(l = x;l<x+block;l++){
//                         bordas += edge.at<uchar>(k, l);
//                     }
//                 }
//             }
                
//             if(edge_flag == 1 && bordas == 0){
//                 for(k = 0; k < 3; k++){
//                     destiny[i*saida.step +j*channels +k] =  origin[y*frame.cols*channels + x*channels + k];
//                 }

//              //   printf("entrou 1\n");
//                 continue;
//             }
//             bordas = 0;
//            // printf("entrou 2\n");
      
//              for(k = 0; k < 3; k++){
//                 for(l = 0; l < 3; l++){
//                     a0 = origin[labs((y-1+l)*(step) + (x)*channels +k)];
//                     d0 = origin[labs((y-1+l)*(step) + (x-1)*channels + k)] - a0;
//                     d2 = origin[labs((y-1+l)*(step) + (x+1)*channels + k)] - a0;
//                     d3 = origin[labs((y-1+l)*(step) + (x+2)*channels + k)] - a0;
                    
//                     a1 = (-1.0/3)*d0 + d2 -(1.0/6)*d3;
//                     a2 = (1.0/2)*d0 + (1.0/2)*d2;
//                     a3 = (-1.0/6)*d0 - (1.0/2)*d2 + (1.0/6)*d3;
                    
//                     C[l] = a0 + a1*dx + a2*(dx*dx) + a3*(dx*dx*dx);
                    
//                     d0 = C[0] - C[1];
//                     d2 = C[2] - C[1];
//                     d3 = C[3] - C[1];
             
//                     a0 = C[1];
                    
//                     a1 =  (-1.0/3)*d0 + d2 -(1.0/6)*d3;
//                     a2 =  (1.0/2)*d0 + (1.0/2)*d2;
//                     a3 =  (-1.0/6)*d0 - (1.0/2)*d2 + (1.0/6)*d3;
//                     Cc = a0 + a1*dy + a2*(dy*dy) + a3*(dy*dy*dy);              

//                     destiny[i*saida.step +j*channels +k ] = Cc;
//                 }
//             } 
//         } 
//     } 
// }

// Atividade::~Atividade(){
// }

