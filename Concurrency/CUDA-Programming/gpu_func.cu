#include "gpu_func.h"

/* gpuMatMultWithTextureKernel：GPU下使用texture内存的矩阵乘法，并将结果存在转置后对应的位置
*  result：结果矩阵，表示为result[S][SM];
*  m：表示为矩阵A与矩阵result的行数
*  n：表示矩阵A的列数，矩阵B的行数
*  s：表示矩阵B和矩阵result的列数
*/
__global__ void gpuMatMultAndTransWithTextureKernel(cufftComplex * result, const int m, const int n, const int s) {
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;

	if (offset < m * s)
	{
		cufftComplex a,b;
        cufftComplex temp_result;
        temp_result.x = 0;
        temp_result.y = 0;
		for (int i = 0; i < n; i++)
		{
            a.x = tex1Dfetch(texA, y * n + i).x;
            a.y = tex1Dfetch(texA, y * n + i).y;
            b.x = tex1Dfetch(texB, i * s + x).x;
            b.y = tex1Dfetch(texB, i * s + x).y;

            cufftComplex temp;
            temp.x = a.x * b.x - a.y * b.y;
            temp.y = a.x * b.y + a.y * b.x;

			temp_result.x += temp.x;
            temp_result.y += temp.y;
        }
		//result[offset] = temp_result;
		result[x * m + y] = temp_result;
	}
}

/* gpuDotMulWithTextureKernel：GPU下使用texture内存的矩阵点乘，并将结果存在转置后对应的位置
*  result：结果矩阵，表示为result[S][M];
*  m：表示为矩阵A与矩阵result的列数
*  s：表示矩阵B和矩阵result的行数
*/
__global__ void gpuDotMulWithTextureKernel(cufftComplex * result, const int m, const int s) {
    int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;
	int bi_index = offset % m;
	cufftComplex a,b;
	double real,imag;

	if (offset < m * s) {
		a.x = tex1Dfetch(texA, offset).x;
		a.y = tex1Dfetch(texA, offset).y;
		b.x = tex1Dfetch(texB, bi_index).x;
		b.y = tex1Dfetch(texB, bi_index).y;

        real = (double)a.x * (double)b.x - (double)a.y * (double)b.y;
		imag = (double)a.x * (double)b.y + (double)a.y * (double)b.x;
		
		result[offset].x = real;
		result[offset].y = imag;
	}
}

/* doAll: GPU下依次调用gpuMatMultAndTransWithTextureKernel和gpuDotMulWithTextureKernel
*         完成矩阵乘、转置、FFT、点乘操作
*  a: m*n 矩阵
*  b: n*s 矩阵
*  result: s*m 矩阵
*  bi: 与第bi行做点乘 
*/
cudaError_t doAll(const cufftComplex *a, const cufftComplex *b, cufftComplex *result, const int m, const int n, const int s, const int bi,cufftHandle &plan_NX_Many) {
	cufftComplex * dev_a;
	cufftComplex * dev_b;
	cufftComplex * dev_result;
	cufftComplex * dev_bi_data;
	cudaError_t cudaStatus;
	cudaChannelFormatDesc desc = cudaCreateChannelDesc<cufftComplex>();

	//cudaEvent_t gpuStart, gpuFinish;
	//float elapsedTime;
	//cudaEventCreate(&gpuStart);
	//cudaEventCreate(&gpuFinish);
	//cudaEventRecord(gpuStart, 0);

	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaSetDevice failed! Do you have a CUDA_capable GPU installed?\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_a, m * n * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_b, n * s * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_b failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_result, m * s * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_result failed!\n");
		goto Error;
	}

	cudaStatus = cudaMalloc((void **)&dev_bi_data, m * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc dev_bi_data failed!\n");
		goto Error;
	}

	cudaStatus = cudaBindTexture(NULL, texA, dev_a, desc, m * n * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texA failed!\n");
		goto Error;
	}

	cudaStatus = cudaBindTexture(NULL, texB, dev_b, desc, n * s * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texB failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_a, a, m * n * sizeof(cufftComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudamemcpy dev_a failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_b, b, n * s * sizeof(cufftComplex), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy dev_b failed!\n");
		goto Error;
	}

	if ((m % BLOCK_SIZE != 0) && (s % BLOCK_SIZE != 0))
	{
		fprintf(stderr, "M or S can't be dividen by 16!\n");
		goto Error;
	}
	
	//Mul%Trans
	gpuMatMultAndTransWithTextureKernel << <grid, block >> >(dev_result, m, n, s);

	//FFT
	checkCudaErrors(cufftExecC2C(plan_NX_Many, dev_result, dev_result, CUFFT_FORWARD));

	//DouMul
	cudaUnbindTexture(texA);
	cudaUnbindTexture(texB);
	cudaStatus = cudaBindTexture(NULL, texA, dev_result, desc, m * s * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texA failed!\n");
		goto Error;
	}

	cudaStatus = cudaBindTexture(NULL, texB, dev_bi_data, desc, m * sizeof(cufftComplex));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaBindTexture texB failed!\n");
		goto Error;
	}

	cudaStatus = cudaMemcpy(dev_bi_data, dev_result + bi * m, m * sizeof(cufftComplex), cudaMemcpyDeviceToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy dev_b failed!\n");
		goto Error;
	}

	gpuDotMulWithTextureKernel << <grid, block >> >(dev_result, m, s);

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

	cudaStatus = cudaMemcpy(result, dev_result, m * s * sizeof(cufftComplex), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy result failed!\n");
		goto Error;
	}

	//cudaEventRecord(gpuFinish, 0);
	//cudaEventSynchronize(gpuFinish);
	//cudaEventElapsedTime(&elapsedTime, gpuStart, gpuFinish);
	//printf("\nThe time of GPU do all is %f seconds.\n", elapsedTime / 1000.0);

Error:
	cudaUnbindTexture(texA);
	cudaUnbindTexture(texB);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_result);

	return cudaStatus;
}

void test_FFT(cufftComplex *data) {
    int i;
	for(i = 0;i<24;i++){
		cufftComplex *d_fftData;
    	cudaMalloc((void**)&d_fftData,M*sizeof(cufftComplex));
    	cudaMemcpy(d_fftData,data+i*M,M*sizeof(cufftComplex),cudaMemcpyHostToDevice);

		cufftHandle plan;
		cufftPlan1d(&plan,M,CUFFT_C2C,1);
		cufftExecC2C(plan,(cufftComplex*)d_fftData,(cufftComplex*)d_fftData,CUFFT_FORWARD);
		cudaDeviceSynchronize();
		cudaMemcpy(data+i*M,d_fftData,M*sizeof(cufftComplex),cudaMemcpyDeviceToHost);
	}
}