#include <stdio.h>

int** createMatrix(int size){
	int** m = (int**)malloc(sizeof(int*) * size);
	for(int i=0; i < size; i++){
		m[i] = (int*)malloc(sizeof(int) * size);
		for(int j=0; j<size;j++){
			m[i][j]=0;
		}
		matrix[i][i]=1;
	}
	return m;
}

int main(){
	// 3x3 matrix
	// Made on the stack
	/*	
	int matrix[3][3];
	matrix[0][0]=1;
	matrix[0][1]=0;
	matrix[0][2]=0;
	matrix[1][0]=0;
	matrix[1][1]=1;
	matrix[1][2]=0;
	matrix[2][0]=0;
	matrix[2][1]=0;
	matrix[2][2]=1;
	return 0;
	*/

	int** m3 = createMatrix(3);
	return 0;
}
