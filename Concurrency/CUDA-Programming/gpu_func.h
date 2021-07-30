#ifndef GPU_FUNCTION
#define GPU_FUNCTION

#include "cufft.h"
#include "cuda_runtime.h"
#include "cufft.h"
#include "device_functions.h"
#include "device_launch_parameters.h"
#include <chrono>
#include <helper_cuda.h>
#include <helper_functions.h>

const int M = 16384;
const int N = 16;
const int S = 24;

cufftComplex *C;  // 16384 * 16
cufftComplex *B;  // 16 * 24
cufftComplex *X;  // 16384 * 24

texture<cufftComplex> texA;
texture<cufftComplex> texB;

const int BLOCK_SIZE = 8;
dim3 block(BLOCK_SIZE, BLOCK_SIZE);
dim3 grid(S / BLOCK_SIZE, M / BLOCK_SIZE);

__global__ void gpuMatMultAndTransWithTextureKernel(int * result, const int m, const int n, const int s);
__global__ void gpuDotMulWithTextureKernel(cufftComplex * result, const int m, const int s);
cudaError_t doAll(const cufftComplex *a, const cufftComplex *b, cufftComplex *result, const int m, const int n, const int s, const int bi, cufftHandle &plan_NX_Many);
void test_FFT(cufftComplex *data);

#endif