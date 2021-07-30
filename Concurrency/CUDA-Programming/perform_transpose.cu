#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TILE_WIDTH 100 // for shared kernel
#define TILE_DIM 100

// NAIVE APPROACH - each threads pass one enrty of the matrix its corresponding place.
__global__ void transpose(float* M, float* R, int dim1, int dim2){

	int tile_size = blockDim.x ;
	int column = tile_size * blockIdx.x + threadIdx.x;
	int row = tile_size * blockIdx.y + threadIdx.y;

	if(column < dim2 && row < dim1){
		R[column*dim2 + row] = M[column + row*dim2];
	}
}

// SHARED MEM APROACH - use shared memory
__global__ void sharedMem_transpose(float* M, float* R, int dim1, int dim2){

	// fill data into shared memory
	__shared__ float M_Shared[TILE_WIDTH][TILE_WIDTH];

	int tile_size =TILE_WIDTH;
	int column = tile_size * blockIdx.x + threadIdx.x;
	int row = tile_size * blockIdx.y + threadIdx.y;
	int index_in = row*dim2 + column;
	int index_out = column*dim2 + row;


	if(row < dim1 && column < dim2 && index_in < dim1*dim2){
		M_Shared[threadIdx.y][threadIdx.x] = M[index_in];
	}
	__syncthreads(); // wait all other threads to go further.

	if(row < dim1 && column < dim2 && index_out < dim1*dim2){
		R[index_out] = M_Shared[threadIdx.y][threadIdx.x];
	}
}


__global__ void transposeCoalesced(float *idata, float *odata,
		int height, int width)
{
	__shared__ float tile[TILE_DIM][TILE_DIM];
	int xIndex = blockIdx.x * TILE_DIM + threadIdx.x;
	int yIndex = blockIdx.y * TILE_DIM + threadIdx.y;
	int index_in = xIndex + (yIndex)*width;
	xIndex = blockIdx.y * TILE_DIM + threadIdx.x;
	yIndex = blockIdx.x * TILE_DIM + threadIdx.y;
	int index_out = xIndex + (yIndex)*height;
	tile[threadIdx.y][threadIdx.x] = idata[index_in];
	__syncthreads();
	odata[index_out] = tile[threadIdx.x][threadIdx.y];
}

int main(void){
	int const tile_size = 100; // for naive approach
	int const dim1 = 3000;
	int const dim2 = 3000;

	float *M_h;
	float *R_h;
	float *M_d;
	float *R_d;

	size_t size = dim1*dim2*sizeof(float);

	cudaMallocHost((float**)&M_h,size); //page locked host mem allocation
	R_h = (float*)malloc(size);
	cudaMalloc((float **)&M_d, size);


	// init matrix
	for (int i = 0; i < dim1*dim2; ++i) {
		M_h[i]=i;
	}

	cudaMemcpyAsync(M_d,M_h,size,cudaMemcpyHostToDevice);
	cudaMalloc((float**)&R_d,size);
	cudaMemset(R_d,0,size);

	//	for (int i = 0; i < dim1; ++i) {
	//		for (int j = 0; j < dim2; ++j) {
	//			float num = M_h[i*dim2 + j];
	//			printf(" %4.2f ",num);
	//		}
	//		printf("\n");
	//	}
	printf("*******************\n");

	// init kernel
	int threadNumX = tile_size;
	int threadNumY = tile_size;
	int blockNumX = dim1 / tile_size + (dim1%tile_size == 0 ? 0 : 1 );
	int blockNumY = dim2 / tile_size + (dim2%tile_size == 0 ? 0 : 1 );

	dim3 blockSize(threadNumX,threadNumY);
	dim3 gridSize(blockNumX, blockNumY);

	// CUDA TIMER to Measure the performance
	cudaEvent_t start_naive, start_shared,start_book, stop_naive, stop_shared, stop_book;
	float elapsedTime1, elapsedTime2, elapsedTime3;
	cudaEventCreate(&start_naive);
	cudaEventCreate(&stop_naive);
	cudaEventCreate(&start_shared);
	cudaEventCreate(&stop_shared);
	cudaEventCreate(&start_book);
	cudaEventCreate(&stop_book);

	cudaEventRecord(start_naive, 0);

	transpose<<<gridSize,blockSize>>>(M_d,R_d,dim1,dim2);

	cudaEventRecord(stop_naive, 0);
	cudaEventSynchronize(stop_naive);
	cudaEventElapsedTime(&elapsedTime1, start_naive, stop_naive);

	cudaEventRecord(start_shared,0);

	sharedMem_transpose<<<gridSize,blockSize>>>(M_d,R_d,dim1,dim2);

	cudaEventRecord(stop_shared, 0);
	cudaEventSynchronize(stop_shared);
	cudaEventElapsedTime(&elapsedTime2, start_shared, stop_shared);

	cudaEventRecord(stop_naive, 0);
	cudaEventSynchronize(stop_naive);
	cudaEventElapsedTime(&elapsedTime1, start_naive, stop_naive);

	cudaEventRecord(start_book,0);

	transposeCoalesced<<<gridSize,blockSize>>>(M_d,R_d,dim1,dim2);

	cudaEventRecord(stop_book, 0);
	cudaEventSynchronize(stop_book);
	cudaEventElapsedTime(&elapsedTime3, start_book, stop_book);

	cudaMemcpy(R_h,R_d,size,cudaMemcpyDeviceToHost);

	//	for (int i = 0; i < dim1; ++i) {
	//		for (int j = 0; j < dim2; ++j) {
	//			float num = R_h[i*dim2 + j];
	//			printf(" %4.2f ",num);
	//		}
	//		printf("\n");
	//	}

	printf ("Time for the NAIVE kernel: %f ms\n", elapsedTime1);
	printf ("Time for the SHARED kernel: %f ms\n", elapsedTime2);
	printf ("Time for the BOOK's kernel: %f ms\n", elapsedTime3);

	free(M_h);
	free(R_h);
	cudaFree(R_d);
	cudaFree(M_d);
	return 0;
}
