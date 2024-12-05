#include <cuda_runtime.h>
#include <math.h>
#include <stdio.h>


__global__ static inline void vectorAddKernel(double *a, double *b, double *result, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        result[tid] = a[tid] + b[tid];
    }
}

__global__ static inline void vectorSubtractKernel(double *a, double *b, double *result, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        result[tid] = a[tid] - b[tid];
    }
}

__global__ void scalarMultiplyKernel(double *vec, double scalar, double *result, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        result[tid] = vec[tid] * scalar;
    }
}

__global__ void scalarDivisionKernel(double *vec, double scalar, double *result, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        result[tid] = vec[tid] / scalar;
    }
}
