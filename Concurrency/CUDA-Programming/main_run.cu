#include "stdio.h"
#include <time.h>
#include <math.h>
#include "gpu_func.cu"
#include "cpu_func.cu"

int main() {

    C = (cufftComplex*)malloc(M*N*sizeof(cufftComplex));
    B = (cufftComplex*)malloc(N*S*sizeof(cufftComplex));
	X = (cufftComplex*)malloc(M*S*sizeof(cufftComplex));

	cufftHandle plan_NX_Many;
	int number_M[1] = { M };
	checkCudaErrors(cufftCreate(&plan_NX_Many));
	checkCudaErrors(cufftPlanMany(&plan_NX_Many, 1, number_M, NULL, 1, M, NULL, 1, M, CUFFT_C2C, S));
	
	/*
	// read data
    read_B_data(C);
	read_S_data(B);
	
	//gpu mul & trans
	mulAndTransWithCudaTex(C,B,X,M,N,S); // X 24(S)*16384(M)

	// cpu mul & trans
	cufftComplex *T;
	T = (cufftComplex*)malloc(M*S*sizeof(cufftComplex));
	CPUMatMultiply(C,B,T,M,N,S);
	cufftComplex *trans_T;
	trans_T = (cufftComplex*)malloc(M*S*sizeof(cufftComplex));
	cpuMatrTrans(trans_T,T,S,M);
	compare_right(trans_T,X);

	//gpu fft
	gpuCuFFt(X,M,S);

	//test FFT
	test_FFT(trans_T);
	compare_right(trans_T,X);

	// DotMul
	DotMulWithTextureKernel(X,M,S,0);
	cpuDotMul(trans_T,0);
	compare_right(trans_T,X);
	*/

	clock_t start,finish;
	/*
	start = clock();
	read_B_data(C);
	read_S_data(B);
	mulAndTransWithCudaTex(C,B,X,M,N,S); // X 24(S)*16384(M)
	gpuCuFFt(X,M,S);
	DotMulWithTextureKernel(X,M,S,0);
	finish = clock();
	printf("No1: total time is %lf s\n",(double)(finish-start)/CLOCKS_PER_SEC); 
	*/

	int count = 0;
	start = clock();
	//read_B_data(C);
	read_S_data(B);
	//doAll(C,B,X,M,N,S,0,plan_NX_Many);
	//finish = clock();
	//printf("total time is %lf s\n",(double)(finish-start)/CLOCKS_PER_SEC);
	while(((double)((finish = clock()) - start)/CLOCKS_PER_SEC) < 1.0) {
		read_B_data(C);
		doAll(C,B,X,M,N,S,0,plan_NX_Many);
		count++;
	}
	double total_time = (double)(finish - start) / CLOCKS_PER_SEC;
	int total_size = (count*(M*N*sizeof(float)*2) + (N*S*sizeof(float)*2)) / 1024 / 1024;
	printf("run time\tMat count\tdata size\tthoughput\n");
	printf("%lfs\t%d\t\t%dMb\t\t%lfMb/s\n",total_time,count,total_size,(double)total_size/total_time);

	cufftComplex *T;
	T = (cufftComplex*)malloc(M*S*sizeof(cufftComplex));
	CPUMatMultiply(C,B,T,M,N,S);
	cufftComplex *trans_T;
	trans_T = (cufftComplex*)malloc(M*S*sizeof(cufftComplex));
	cpuMatrTrans(trans_T,T,S,M);
	test_FFT(trans_T);
	cpuDotMul(trans_T,0);
	compare_right(trans_T,X);

	free(C);free(B);free(X);
	//free(T);free(trans_T);
}
