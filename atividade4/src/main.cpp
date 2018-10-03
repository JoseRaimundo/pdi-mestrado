#include "Atividade.h"
#include <stdio.h>
#include <bitset>
#include <iostream>
//Color out

using namespace std;

int main(int argc, char const *argv[]){
	bitset<16> valor = 360;
	bitset<16> invert_valor;
	for (int i = 16; i >= 0; i--){
		invert_valor[i-1] = valor[16-i];
	}
	cout << valor << endl; 			//0000000101101000
	cout << invert_valor << endl;	//0010110100000000
	return 0;
}