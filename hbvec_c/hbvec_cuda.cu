#include "vec.h"
#include "cuda_runtime.h"

__global__ void vectorAdd(Vec3 *A, Vec3 *B, Vec3 *C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        // Add corresponding components of A and B, and store in C
        C[i].x = A[i].x + B[i].x;
        C[i].y = A[i].y + B[i].y;
        C[i].z = A[i].z + B[i].z;
    }
}



