#include "stdio.h"
#include "stdlib.h"
#include "cuda_runtime.h"
#include "cufft.h"
#include "device_functions.h"
#include "device_launch_parameters.h"
#include <chrono>
#include <time.h>
#include <math.h>
#include <helper_cuda.h>
#include <helper_functions.h>

const int M = 16384;
const int N = 16;
const int S = 24;

//const char *file_C = "shujv.dat";
//const char *file_B = "temp_data.txt";
cufftDoubleComplex *C;  // 16384 * 16
cufftDoubleComplex *B;  // 16 * 24
cufftDoubleComplex *X;  // 16384 * 24

/*
const int TILE_DIM = 32;
const int BLOCK_ROWS = 8;
*/
/*
cufftDoubleComplex cuCadd (cufftDoubleComplex a, cufftDoubleComplex b) {
    cufftDoubleComplex temp;
    temp.x = a.x + b.x;
    temp.y = a.y + b.y;
    return temp;
}

cufftDoubleComplex cuCmul (cufftDoubleComplex a, cufftDoubleComplex b) {
    cuFloatComplex temp;
    temp.x = a.x * b.x - a.y * b.y;
    temp.y = a.x * b.y + a.y * b.x;
    return temp;
}
*/

void CPUMatMultiply(const cufftDoubleComplex * a,const cufftDoubleComplex * b, cufftDoubleComplex *result,const int M,const int N,const int S);
void cpuMatrTrans(cufftDoubleComplex *matrB, cufftDoubleComplex *matrA, const int width, const int height);
void compare_right(cufftDoubleComplex *T,cufftDoubleComplex *R);
void test_FFT(cufftDoubleComplex *data);
void cpuDotMul(cufftDoubleComplex *data, const int bi);

// main function
void read_B_data(cufftDoubleComplex *C);
void read_S_data(cufftDoubleComplex *C);
__global__ void gpuMatMultAndTransWithSharedKernel(const cufftDoubleComplex *a, const cufftDoubleComplex *b, cufftDoubleComplex *result, const int M, const int N, const int S);
//__global__ void gpuMatMultAndTransWithTextureKernel(int * result, const int M, const int N, const int S);
//__global__ void gpuDotMulWithTextureKernel(cufftDoubleComplex * result, const int M, const int S);
cudaError_t mulAndTransWithCudaShare(const cufftDoubleComplex *a, const cufftDoubleComplex *b, cufftDoubleComplex *result, const int M, const int N, const int S);
//cudaError_t mulAndTransWithCudaTex(const cufftDoubleComplex *a, const cufftDoubleComplex *b, cufftDoubleComplex *result, const int M, const int N, const int S);
cudaError_t gpuCuFFt(cufftDoubleComplex *data, const int M, const int S);
//cudaError_t DotMulWithTextureKernel(cufftDoubleComplex *data, const int M, const int S, const int bi);

/*__global__ void notSoNaivaTransKernel(cufftDoubleComplex *matrB, cufftDoubleComplex *matrA, const int width, const int height);
cudaError_t matrMagicCuda(cufftDoubleComplex *matrB, cufftDoubleComplex *matrA, const int width, const int height);*/

int main() {
    C = (cufftDoubleComplex*)malloc(M*N*sizeof(cufftDoubleComplex));
    B = (cufftDoubleComplex*)malloc(N*S*sizeof(cufftDoubleComplex));
	X = (cufftDoubleComplex*)malloc(M*S*sizeof(cufftDoubleComplex));
	// read data
    read_B_data(C);
	read_S_data(B);
	
	//gpu mul & trans
	//mulAndTransWithCudaTex(C,B,X,M,N,S); // X 24(S)*16384(M)
	mulAndTransWithCudaShare(C,B,X,M,N,S);

	// cpu mul & trans
	cufftDoubleComplex *T;
	T = (cufftDoubleComplex*)malloc(M*S*sizeof(cufftDoubleComplex));
	CPUMatMultiply(C,B,T,M,N,S);
	cufftDoubleComplex *trans_T;
	trans_T = (cufftDoubleComplex*)malloc(M*S*sizeof(cufftDoubleComplex));
	cpuMatrTrans(trans_T,T,S,M);
	compare_right(trans_T,X);

	//gpu fft
	//gpuCuFFt(X,M,S);

	//test FFT
	/*test_FFT(trans_T);
	compare_right(trans_T,X);*/

	// DotMul
	//DotMulWithTextureKernel(X,M,S,0);
	//cpuDotMul(trans_T,0);
	//compare_right(trans_T,X);
}

void read_B_data(cufftDoubleComplex *C) {
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

void read_S_data(cufftDoubleComplex *C) {
    FILE * fp;

    if((fp = fopen("Weight_Final.txt","rb")) == NULL){
        printf("file can not oepn!\n");
        exit(0);
    }

    unsigned int line = 0;
    while(line < N) { 
        int i;
        for(i = 0; i < S; i++) {
            fscanf(fp,"%lf",&C[line * S + i].x);
            fscanf(fp,"%lf",&C[line * S + i].y);
			//printf("%f + %fi\n",C[line * S + i].x,C[line * S + i].y);
        }
        line++;
    }

    fclose(fp);
}

/* gpuMatMultWithSharedKernel：GPU下使用shared内存的矩阵乘法
*  a:第一个矩阵指针，表示a[M][N]
*  b:第二个矩阵指针，表示b[N][S]
*  result:结果矩阵，表示result[S][M]
*/
template<int BLOCK_SIZE>
__global__ void gpuMatMultAndTransWithSharedKernel(const cufftDoubleComplex *a, const cufftDoubleComplex *b, cufftDoubleComplex *result, const int M, const int N, const int S) {
	int block_x = blockIdx.x;
	int block_y = blockIdx.y;
	int thread_x = threadIdx.x;
	int thread_y = threadIdx.y;

	if ((thread_y + block_y * blockDim.y) * S + block_x * blockDim.x + thread_x >= M * S)
	{
		return;
	}

	const int begin_a = block_y * blockDim.y * N;
	const int end_a = begin_a + N - 1;
	const int step_a = blockDim.x;

	const int begin_b = block_x * blockDim.x;
	const int step_b = blockDim.y * S;

	cufftDoubleComplex result_temp;
	result_temp.x = 0;
	result_temp.y = 0;

	int index_a,index_b;
	for (index_a = begin_a, index_b = begin_b;
		index_a < end_a; index_a += step_a, index_b += step_b)
	{
		__shared__ cufftDoubleComplex SubMat_A[BLOCK_SIZE][BLOCK_SIZE];
		__shared__ cufftDoubleComplex SubMat_B[BLOCK_SIZE][BLOCK_SIZE];

		SubMat_A[thread_y][thread_x].x = a[index_a + thread_y * N + thread_x].x;
		SubMat_A[thread_y][thread_x].y = a[index_a + thread_y * N + thread_x].y;
		SubMat_B[thread_y][thread_x].x = b[index_b + thread_y * S + thread_x].x;
		SubMat_B[thread_y][thread_x].y = b[index_b + thread_y * S + thread_x].y;

		__syncthreads();

		for (int i = 0; i < BLOCK_SIZE; i++)
		{	
			cufftDoubleComplex temp;
			temp.x = SubMat_A[thread_y][i].x * SubMat_B[i][thread_x].x - SubMat_A[thread_y][i].y * SubMat_B[i][thread_x].y;
			temp.y = SubMat_A[thread_y][i].x * SubMat_B[i][thread_x].y + SubMat_A[thread_y][i].y * SubMat_B[i][thread_x].x;
			
			result_temp.x += temp.x;
			result_temp.y += temp.y;
		}

		__syncthreads();
	}

	int offset = (block_y * blockDim.y * S + begin_b) + thread_y * S + thread_x;
	int row = offset / S;
	int col = offset % S;
	result[col * M + row] = result_temp;
}

/* gpuMatMultWithTextureKernel：GPU下使用texture内存的矩阵乘法，并将结果存在转置后对应的位置
*  result：结果矩阵，表示为result[M][S];
*  M：表示为矩阵A与矩阵result的行数
*  N：表示矩阵A的列数，矩阵B的行数
*  S：表示矩阵B和矩阵result的列数
*/
/*texture<cufftDoubleComplex> texA;
texture<cufftDoubleComplex> texB;
__global__ void gpuMatMultAndTransWithTextureKernel(cufftDoubleComplex * result, const int M, const int N, const int S) {
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;

	if (offset < M * S)
	{
		cufftDoubleComplex a,b;
        cufftDoubleComplex temp_result;
        temp_result.x = 0;
        temp_result.y = 0;
		for (int i = 0; i < N; i++)
		{
            a.x = tex1Dfetch(texA, y * N + i).x;
            a.y = tex1Dfetch(texA, y * N + i).y;
            b.x = tex1Dfetch(texB, i * S + x).x;
            b.y = tex1Dfetch(texB, i * S + x).y;

            cufftDoubleComplex temp;
            temp.x = a.x * b.x - a.y * b.y;
            temp.y = a.x * b.y + a.y * b.x;

			temp_result.x += temp.x;
            temp_result.y += temp.y;
        }
		//result[offset] = temp_result;
		result[x*M + y] = temp_result;
	}
}*/

cudaError_t mulAndTransWithCudaShare(const cufftDoubleComplex *a, const cufftDoubleComplex *b, cufftDoubleComplex *result, const int M, const int N, const int S) {
	cufftDoubleComplex *dev_a;
	cufftDoubleComplex *dev_b;
	cufftDoubleComplex *dev_result;
	const int BLOCK_SIZE = 8;
	dim3 block(BLOCK_SIZE, BLOCK_SIZE);
	dim3 grid((S + BLOCK_SIZE - 1) / BLOCK_SIZE, (M + BLOCK_SIZE - 1) / BLOCK_SIZE);
	cudaError_t cudaStatus;

	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed! Do you have a CUDA-capable GPU installed?\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_a, M * N * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_b, N * S * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_b failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_result, S * M * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_result failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_a, a, M * N * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudamemcpy dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_b, b, N * S * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy dev_b failed!\n");
		goto Error;
	}

	cudaEvent_t gpuStart, gpuFinish;
	float elapsedTime;
	cudaEventCreate(&gpuStart);
	cudaEventCreate(&gpuFinish);
	cudaEventRecord(gpuStart, 0);

	gpuMatMultAndTransWithSharedKernel<16> << <grid, block >> >(dev_a, dev_b, dev_result, M, N, S);

	cudaEventRecord(gpuFinish, 0);
	cudaEventSynchronize(gpuFinish);
	cudaEventElapsedTime(&elapsedTime, gpuStart, gpuFinish);
	printf("\nThe runing time of GPU on Mat Multiply is %f seconds.\n", elapsedTime / 1000.0);

	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "MulKernel launch failed: %s!\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaDeviceSynchronize return Error code %d after Kernel launched!\n", cudaStatus);
		goto Error;
	}

	cudaStatus = cudaMemcpy(result, dev_result, M * S * sizeof(cufftDoubleComplex), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy result failed!\n");
		goto Error;
	}

Error:
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_result);

	return cudaStatus;
}

//调用CUDA运行GPU矩阵乘法核函数
//将矩阵A与矩阵B绑定到纹理内存中
/*
cudaError_t mulAndTransWithCudaTex(const cufftDoubleComplex *a, const cufftDoubleComplex *b, cufftDoubleComplex *result, const int M, const int N, const int S)
{
	cufftDoubleComplex * dev_a;
	cufftDoubleComplex * dev_b;
	cufftDoubleComplex * dev_result;
    const int BLOCK_SIZE = 8;
    dim3 block(BLOCK_SIZE, BLOCK_SIZE);
	dim3 grid(S / BLOCK_SIZE, M / BLOCK_SIZE);
	cudaError_t cudaStatus;
	cudaChannelFormatDesc desc = cudaCreateChannelDesc<cufftDoubleComplex>();

	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed! Do you have a CUDA_capable GPU installed?\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_a, M * N * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_b, N * S * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_b failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_result, M * S * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_result failed!\n");
		goto Error;
	}

	cudaStatus = cudaBindTexture(NULL, texA, dev_a, desc, M * N * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texA failed!\n");
		goto Error;
	}

	cudaStatus = cudaBindTexture(NULL, texB, dev_b, desc, N * S * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texB failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_a, a, M * N * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudamemcpy dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_b, b, N * S * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy dev_b failed!\n");
		goto Error;
	}

	cudaEvent_t gpuStart, gpuFinish;
	float elapsedTime;
	cudaEventCreate(&gpuStart);
	cudaEventCreate(&gpuFinish);
	cudaEventRecord(gpuStart, 0);

	if ((M % BLOCK_SIZE != 0) && (S % BLOCK_SIZE != 0))
	{
		fprintf(stderr, "M or S can't be dividen by 16!\n");
		goto Error;
	}

	gpuMatMultAndTransWithTextureKernel << <grid, block >> >(dev_result, M, N, S);

	cudaEventRecord(gpuFinish, 0);
	cudaEventSynchronize(gpuFinish);
	cudaEventElapsedTime(&elapsedTime, gpuStart, gpuFinish);
	printf("\nThe runing time of GPU on Mat Multiply & trans is %f seconds.\n", elapsedTime / 1000.0);

	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "MulKernel launch failed: %s!\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaDeviceSynchronize return Error code %d after Kernel launched!\n", cudaStatus);
		goto Error;
	}

	cudaStatus = cudaMemcpy(result, dev_result, M * S * sizeof(cufftDoubleComplex), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy result failed!\n");
		goto Error;
	}

Error:
	cudaUnbindTexture(texA);
	cudaUnbindTexture(texB);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_result);

	return cudaStatus;
}
*/

/* gpuCuFFt : GPU 下进行FFT
*  data:目标矩阵，S*M;
*/
cudaError_t gpuCuFFt(cufftDoubleComplex *data, const int M, const int S) {
	cufftDoubleComplex *d_fftData;
	int number_M[1] = { M };
	cudaError_t cudaStatus;

	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed! Do you have a CUDA_capable GPU installed?\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&d_fftData, S * M * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc d_fftData failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(d_fftData, data, S * M * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudamemcpy d_fftData failed!\n");
		goto Error;
	}

	cufftHandle plan_NX_Many;
	checkCudaErrors(cufftCreate(&plan_NX_Many));
	checkCudaErrors(cufftPlanMany(&plan_NX_Many, 1, number_M, NULL, 1, M, NULL, 1, M, CUFFT_C2C, S));

	cudaEvent_t gpuStart, gpuFinish;
	float elapsedTime;
	cudaEventCreate(&gpuStart);
	cudaEventCreate(&gpuFinish);
	cudaEventRecord(gpuStart, 0);

	checkCudaErrors(cufftExecZ2Z(plan_NX_Many, d_fftData, d_fftData, CUFFT_FORWARD));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cufft failed!\n");
		goto Error;
	}

	cudaEventRecord(gpuFinish, 0);
	cudaEventSynchronize(gpuFinish);
	cudaEventElapsedTime(&elapsedTime, gpuStart, gpuFinish);
	printf("\nThe runing time of GPU on FFT is %f seconds.\n", elapsedTime / 1000.0);

	cudaStatus = cudaMemcpy(data, d_fftData, S * M * sizeof(cufftDoubleComplex), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudamemcpy result failed!\n");
		goto Error;
	}

Error:
	cufftDestroy(plan_NX_Many);
	cudaFree(d_fftData);

	return cudaStatus;
}

/*
__global__ void gpuDotMulWithTextureKernel(cufftDoubleComplex * result, const int M, const int S) {
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;
	int bi_index = offset % M;
	cufftDoubleComplex a,b;
	double real,imag;

	if (offset < M * S) {
		a.x = tex1Dfetch(texA, offset).x;
		a.y = tex1Dfetch(texA, offset).y;
		b.x = tex1Dfetch(texB, bi_index).x;
		b.y = tex1Dfetch(texB, bi_index).y;

        real = a.x * b.x - a.y * b.y;
		imag = a.x * b.y + a.y * b.x;
		
		result[offset].x = real;
		result[offset].y = imag;
	}
}

cudaError_t DotMulWithTextureKernel(cufftDoubleComplex *data, const int M, const int S, const int bi) {
	cufftDoubleComplex * dev_data;
	cufftDoubleComplex * dev_bi_data;
	cufftDoubleComplex * dev_result;
    const int BLOCK_SIZE = 8;
    dim3 block(BLOCK_SIZE, BLOCK_SIZE);
	dim3 grid(M / BLOCK_SIZE, S / BLOCK_SIZE);
	cudaError_t cudaStatus;
	cudaChannelFormatDesc desc = cudaCreateChannelDesc<cufftDoubleComplex>();

	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed! Do you have a CUDA_capable GPU installed?\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_data, S * M * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_bi_data, M * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_b failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_result, S * M * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_result failed!\n");
		goto Error;
	}

	cudaStatus = cudaBindTexture(NULL, texA, dev_data, desc, S * M * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texA failed!\n");
		goto Error;
	}

	cudaStatus = cudaBindTexture(NULL, texB, dev_bi_data, desc, M * sizeof(cufftDoubleComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texB failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_data, data, S * M * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudamemcpy dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_bi_data, data + bi * M, M * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy dev_b failed!\n");
		goto Error;
	}

	cudaEvent_t gpuStart, gpuFinish;
	float elapsedTime;
	cudaEventCreate(&gpuStart);
	cudaEventCreate(&gpuFinish);
	cudaEventRecord(gpuStart, 0);

	if ((M % BLOCK_SIZE != 0) && (S % BLOCK_SIZE != 0))
	{
		fprintf(stderr, "M or S can't be dividen by 16!\n");
		goto Error;
	}

	gpuDotMulWithTextureKernel << <grid, block >> >(dev_result, M, S);

	cudaEventRecord(gpuFinish, 0);
	cudaEventSynchronize(gpuFinish);
	cudaEventElapsedTime(&elapsedTime, gpuStart, gpuFinish);
	printf("\nThe runing time of GPU on Dot Multiply is %f seconds.\n", elapsedTime / 1000.0);

	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "MulKernel launch failed: %s!\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaDeviceSynchronize return Error code %d after Kernel launched!\n", cudaStatus);
		goto Error;
	}

	cudaStatus = cudaMemcpy(data, dev_result, S * M * sizeof(cufftDoubleComplex), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy result failed!\n");
		goto Error;
	}

Error:
	cudaUnbindTexture(texA);
	cudaUnbindTexture(texB);
	cudaFree(dev_data);
	cudaFree(dev_bi_data);
	cudaFree(dev_result);

	return cudaStatus;
}
*/

/* MatMultiply：CPU下矩阵乘法
*  a:第一个矩阵指针，表示a[M][N];
*  b:第二个矩阵指针，表示b[N][S];
*  result:结果矩阵，表示为result[M][S];
*/
void CPUMatMultiply(const cufftDoubleComplex * a,const cufftDoubleComplex * b, cufftDoubleComplex *result,const int M,const int N,const int S) {
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < S; j++)
		{
			int index = i * S + j;
			result[index].x = 0;
			result[index].y = 0;

			//计算每一个元素的结果
			for (int k = 0; k < N; k++)
			{
				cufftDoubleComplex temp;
				temp.x = a[i * N + k].x * b[k * S + j].x - a[i * N + k].y * b[k * S + j].y;
                temp.y = a[i * N + k].x * b[k * S + j].y + a[i * N + k].y * b[k * S + j].x;

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
void cpuMatrTrans(cufftDoubleComplex *matrB, cufftDoubleComplex *matrA, const int width, const int height) {
	int i, j;

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++) {
			matrB[j * height + i] = matrA[i * width + j];
		}
}

void compare_right(cufftDoubleComplex *T,cufftDoubleComplex *R) {
	int count = 0;
	float err = 0.00001;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < S; j++)
		{
			if (abs(T[i * S + j].x - R[i * S + j].x) > err || abs(T[i * S + j].y - R[i * S + j].y) > err)
			{
				count++;
				//printf("%d,%d:%f+%fi  %f+%fi\n",i,j,T[i * S + j].x,T[i * S + j].y,R[i * S + j].x,R[i * S + j].y);
			}
		}
	}

	printf("error count:%d\n",count);
}

void test_FFT(cufftDoubleComplex *data) {
    int i;
	for(i = 0; i < S; i++){
		cufftDoubleComplex *d_fftData;
    	cudaMalloc((void**)&d_fftData,M*sizeof(cufftDoubleComplex));
    	cudaMemcpy(d_fftData,data+i*M,M*sizeof(cufftDoubleComplex),cudaMemcpyHostToDevice);

		cufftHandle plan;
		cufftPlan1d(&plan,M,CUFFT_C2C,1);
		cufftExecZ2Z(plan,(cufftDoubleComplex*)d_fftData,(cufftDoubleComplex*)d_fftData,CUFFT_FORWARD);
		cudaDeviceSynchronize();
		cudaMemcpy(data+i*M,d_fftData,M*sizeof(cufftDoubleComplex),cudaMemcpyDeviceToHost);
	}
}

void cpuDotMul(cufftDoubleComplex *data, const int bi) {
	cufftDoubleComplex *temp_data;
	temp_data = (cufftDoubleComplex *)malloc (M * sizeof(cufftDoubleComplex));
	memcpy(temp_data,data+bi*M,M*sizeof(cufftDoubleComplex));
	cufftDoubleComplex a,b;
	double real,imag;

	int i,j;
	for(i = 0; i < S; i++){
		for(j = 0; j < M; j++) {
			int offset = i * M + j;
			a.x = data[offset].x;
			a.y = data[offset].y;
			b.x = temp_data[offset%M].x;
			b.y = temp_data[offset%M].y;

            real = a.x * b.x - a.y * b.y;
			imag = a.x * b.y + a.y * b.x;

			data[offset].x = real;
			data[offset].y = imag;
		}
	}
}

/*
__global__ void notSoNaivaTransKernel(cufftDoubleComplex *matrB, cufftDoubleComplex *matrA, const int width, const int height)
{
    __shared__ cufftDoubleComplex tile[TILE_DIM][TILE_DIM + 1];
    int ciIndex = blockIdx.x * TILE_DIM + threadIdx.x;
    int riIndex = blockIdx.y * TILE_DIM + threadIdx.y;
    int coIndex = blockIdx.y * TILE_DIM + threadIdx.x;
    int roIndex = blockIdx.x * TILE_DIM + threadIdx.y;
    int index_in = ciIndex + (riIndex)* width;
    int index_out = coIndex + (roIndex)* height;

    int i;
    for (i = 0; i < TILE_DIM; i += BLOCK_ROWS)
        if ((ciIndex<width) && (riIndex+i < height)) {
			tile[threadIdx.y + i][threadIdx.x] = matrA[index_in + i * width];
		}
    __syncthreads();

    for (i = 0; i < TILE_DIM; i += BLOCK_ROWS)
        if ((coIndex<height) && (roIndex+i < width)) {
			matrB[index_out + i*height] = tile[threadIdx.x][threadIdx.y + i];
		}
    __syncthreads();
}*/

/*
cudaError_t matrMagicCuda(cufftDoubleComplex *matrB, cufftDoubleComplex *matrA, const int width, const int height)
{
    float elapsed = 0;
    cufftDoubleComplex *dev_matrA;
    cufftDoubleComplex *dev_matrB;
    cudaError_t cudaStatus;
    dim3 dim_grid, dim_block;

    int size = width * height;

    dim_block.x = TILE_DIM;
    dim_block.y = BLOCK_ROWS;
    dim_block.z = 1;

    dim_grid.x = (width + TILE_DIM - 1) / TILE_DIM;
    dim_grid.y = (height + TILE_DIM - 1) / TILE_DIM;
    dim_grid.z = 1;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three matrix
    cudaStatus = cudaMalloc((void**)&dev_matrA, size * sizeof(cufftDoubleComplex));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_matrB, size * sizeof(cufftDoubleComplex));
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input matrix from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_matrA, matrA, size * sizeof(cufftDoubleComplex), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

	cudaEventRecord(start);
	// Launch a kernel on the GPU with one thread for each element.
	notSoNaivaTransKernel << <dim_grid, dim_block >> >(dev_matrB, dev_matrA, width, height);

	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	cudaEventElapsedTime(&elapsed, start, stop);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	
	printf("GPU Trans with SM Time: %f s\n", elapsed  / 1000.0);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "Kernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }

    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching Kernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output matrix from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(matrB, dev_matrB, size * sizeof(cufftDoubleComplex), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

Error:
    cudaFree(dev_matrB);
    cudaFree(dev_matrA);

    return cudaStatus;
}
*/
