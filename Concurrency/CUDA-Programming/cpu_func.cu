#include <stdlib.h>
#include "gpu_func.h"
#include "cpu_func.h"

void read_B_data(cufftComplex *C) {
    FILE * fp;

    if((fp = fopen("shujv.dat","rb")) == NULL){
        printf("file can not oepn!\n");
        exit(0);
    }

    unsigned char real[N];
    unsigned int line = 0;
    while((fread(real, sizeof(char), N, fp) > 0) & line < M * 2) { 
        unsigned char imag[N];
        fread(imag, sizeof(char), N, fp);

        int i;
        for(i = 0; i < N; i++) {
            C[(line/2) * N + i].x = real[i];
			C[(line/2) * N + i].y = imag[i];
			//printf("%f + %fi\n",C[(line/2) * N + i].x,C[(line/2) * N + i].y);
        }

        line += 2;
    }

    fclose(fp);
}

void read_S_data(cufftComplex *C) {
    FILE * fp;

    if((fp = fopen("Weight_Final.txt","rb")) == NULL){
        printf("file can not oepn!\n");
        exit(0);
    }

    unsigned int line = 0;
    while(line < N) { 
        int i;
        for(i = 0; i < S; i++) {
            fscanf(fp,"%f",&C[line * S + i].x);
            fscanf(fp,"%f",&C[line * S + i].y);
			//printf("%f + %fi\n",C[line * S + i].x,C[line * S + i].y);
        }
        line++;
    }

    fclose(fp);
}

/* MatMultiply：CPU下矩阵乘法
*  a:第一个矩阵指针，表示a[m][n];
*  b:第二个矩阵指针，表示b[n][s];
*  result:结果矩阵，表示为result[m][s];
*/
void CPUMatMultiply(const cufftComplex * a,const cufftComplex * b, cufftComplex *result,const int m,const int n,const int s) {
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < s; j++)
		{
			int index = i * s + j;
			result[index].x = 0;
			result[index].y = 0;

			//计算每一个元素的结果
			for (int k = 0; k < n; k++)
			{
				cufftComplex temp;
				temp.x = a[i * n + k].x * b[k * s + j].x - a[i * n + k].y * b[k * s + j].y;
                temp.y = a[i * n + k].x * b[k * s + j].y + a[i * n + k].y * b[k * s + j].x;

				result[index].x += temp.x;
				result[index].y += temp.y;
            }
		}
	}
}

/* MatrTrans：CPU下矩阵转置
*  matrB: 转置完成的矩阵;
*  matrA: 需要转置的矩阵;
*/
void cpuMatrTrans(cufftComplex *matrB, cufftComplex *matrA, const int width, const int height) {
	int i, j;

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++) {
			matrB[j * height + i] = matrA[i * width + j];
		}
}

void compare_right(cufftComplex *T, cufftComplex *R) {
	int count = 0;
	float err = 0.00001;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < S; j++)
		{
			if (abs(T[i * S + j].x - R[i * S + j].x) > err || abs(T[i * S + j].y - R[i * S + j].y) > err)
			{
				count++;
				printf("%d,%d:%f+%fi  %f+%fi\n",i,j,T[i * S + j].x,T[i * S + j].y,R[i * S + j].x,R[i * S + j].y);
				return;
			}
		}
	}

	printf("error count:%d\n",count);
}

void cpuDotMul(cufftComplex *data, const int bi) {
	cufftComplex *temp_data;
	temp_data = (cufftComplex *)malloc (M * sizeof(cufftComplex));
	memcpy(temp_data,data+bi*M,M*sizeof(cufftComplex));
	cufftComplex a,b;
	double real,imag;

	int i,j;
	for(i = 0; i < S; i++){
		for(j = 0; j < M; j++) {
			int offset = i*M + j;
			a.x = data[offset].x;
			a.y = data[offset].y;
			b.x = temp_data[offset%M].x;
			b.y = temp_data[offset%M].y;

            real = (double)a.x * (double)b.x - (double)a.y * (double)b.y;
			imag = (double)a.x * (double)b.y + (double)a.y * (double)b.x;

			data[offset].x = real;
			data[offset].y = imag;
		}
	}
}