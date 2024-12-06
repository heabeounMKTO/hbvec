#include <cuda_runtime.h>
#include <math.h>

__global__  void vectorAddKernel(double *a, double *b, double *result, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        result[tid] = a[tid] + b[tid];
    }
}

__global__  void vectorSubtractKernel(double *a, double *b, double *result, int size) {
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
