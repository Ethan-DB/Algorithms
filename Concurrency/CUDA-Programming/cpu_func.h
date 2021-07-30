#ifndef CPU_FUNCTION
#define CPU_FUNCTION

#include "cufft.h"

void read_B_data(cufftComplex *C);
void read_S_data(cufftComplex *C);

//test func
void CPUMatMultiply(const cufftComplex * a,const cufftComplex * b, cufftComplex *result,const int M,const int N,const int S);
void cpuMatrTrans(cufftComplex *matrB, cufftComplex *matrA, const int width, const int height);
void cpuDotMul(cufftComplex *data, const int bi);
void compare_right(cufftComplex *T,cufftComplex *R);

#endif