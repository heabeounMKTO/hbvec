#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <stdio.h>
#include "vec.h"
#include "vec_gpu.h"


// Add two Vec3_d
__device__ Vec3_d vec3d_add_device(Vec3_d v1, Vec3_d v2) {
    Vec3_d v = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return v;
}

__device__ Vec3_d vec3d_from_float_device(double f) {
  Vec3_d v = { f, f, f };
  return v;
}



__device__ Vec3_d vec3d_mul_device(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x=v1.x * v2.x , .y=v1.y * v2.y, .z=v1.z * v2.z};
  return v;
}

__device__ Vec3_d vec3d_div_device(Vec3_d v1, Vec3_d v2) {
    Vec3_d result;
    if (v2.x != 0.0f) {
        result.x = v1.x / v2.x;
    } else {
        result.x = 0.0f; // Handle division by zero as needed
    }
    if (v2.y != 0.0f) {
        result.y = v1.y / v2.y;
    } else {
        result.y = 0.0f; // Handle division by zero as needed
    }
    if (v2.z != 0.0f) {
        result.z = v1.z / v2.z;
    } else {
        result.z = 0.0f; // Handle division by zero as needed
    }
    return result;
}

__device__ double vec3d_lengthsq_device( Vec3_d v) {
  return (v.x*v.x) + (v.y * v.y) + (v.z * v.z);
}

__device__ Vec3_d vec3d_sub_device(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x=v1.x - v2.x , .y=v1.y - v2.y, .z=v1.z - v2.z};
  return v;
}

__device__  Vec3_d vec3d_scale_device(Vec3_d v, double t) {
  return (Vec3_d) { v.x * t, v.y * t, v.z * t };
}

__device__ double vec3d_dot_device(Vec3_d  v1, Vec3_d v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

__device__ double vec3d_length_device(Vec3_d v) {
  double dot_v = vec3d_dot_device(v,v);
  return sqrt(dot_v);
}

__device__ Vec3_d vec3d_cross_device(Vec3_d v1, Vec3_d v2) {
  return (Vec3_d) { .x = v1.y * v2.z - v1.z * v2.y, .y=v1.z * v2.x - v1.x * v2.z, .z=v1.x * v2.y - v1.y * v2.x };
}

__device__ Vec3_d vec3d_unit_device(Vec3_d v) {
  double len = vec3d_length_device(v);
  Vec3_d vec = {len, len,len};
  return vec3d_div_device(v, vec);
}

__device__ double vec3d_cosine_sim_device(Vec3_d v1, Vec3_d v2) {
  return vec3d_dot_device(v1, v2) / (vec3d_length_device(v1) * vec3d_length_device(v2));
}

// Kernel for adding arrays of Vec3_d
__global__ void vec3d_add_kernel(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        result[idx] = vec3d_add_device(v1[idx], v2[idx]);
    }
}

__global__ void vec3d_sub_kernel(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        result[idx] = vec3d_sub_device(v1[idx], v2[idx]);
    }
}

__global__ void vec3d_mul_kernel(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        result[idx] = vec3d_mul_device(v1[idx], v2[idx]);
    }
}

__global__ void vec3d_div_kernel(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        result[idx] = vec3d_div_device(v1[idx], v2[idx]);
    }
}

__global__ void vec3d_dot_kernel(Vec3_d *v1, Vec3_d *v2, double *result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        result[idx] = vec3d_dot_device(v1[idx], v2[idx]);
    }
}

__global__ void vec3d_cosine_similarity_kernel(Vec3_d *v1, Vec3_d *v2, double *result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        result[idx] = vec3d_cosine_sim_device(v1[idx], v2[idx]);
    }
}
__global__ void vec3d_cross_kernel(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        result[idx] = vec3d_cross_device(v1[idx], v2[idx]);
    }
}
void vec3d_add_cuda(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int batch_size) {
  size_t vec_memsize = batch_size * sizeof(Vec3_d);
  Vec3_d *d_a, *d_b, *d_c;
      if (cudaMalloc(&d_a, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_b, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_c, vec_memsize) != cudaSuccess) {
        fprintf(stderr, "CUDA memory allocation failed\n");
    }
    if (cudaMemcpy(d_a, v1, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess ||
        cudaMemcpy(d_b, v2, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to device failed\n");
    }
    int threadsPerBlock = 256;
    int blocksPerGrid = (batch_size + threadsPerBlock - 1) / threadsPerBlock;
    vec3d_add_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, batch_size);
    cudaError_t kernelError = cudaGetLastError();
    if (kernelError != cudaSuccess) {
        fprintf(stderr, "Kernel launch error: %s\n", cudaGetErrorString(kernelError));
    }
    if (cudaMemcpy(result, d_c, vec_memsize, cudaMemcpyDeviceToHost) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to host failed\n");
    }
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
} 

void vec3d_sub_cuda(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int batch_size) {
  size_t vec_memsize = batch_size * sizeof(Vec3_d);
  Vec3_d *d_a, *d_b, *d_c;
      if (cudaMalloc(&d_a, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_b, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_c, vec_memsize) != cudaSuccess) {
        fprintf(stderr, "CUDA memory allocation failed\n");
    }
    if (cudaMemcpy(d_a, v1, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess ||
        cudaMemcpy(d_b, v2, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to device failed\n");
    }
    int threadsPerBlock = 256;
    int blocksPerGrid = (batch_size + threadsPerBlock - 1) / threadsPerBlock;
    vec3d_sub_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, batch_size);
    cudaError_t kernelError = cudaGetLastError();
    if (kernelError != cudaSuccess) {
        fprintf(stderr, "Kernel launch error: %s\n", cudaGetErrorString(kernelError));
    }
    if (cudaMemcpy(result, d_c, vec_memsize, cudaMemcpyDeviceToHost) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to host failed\n");
    }
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
} 

void vec3d_dot_cuda(Vec3_d *v1, Vec3_d *v2, double *result, int batch_size) {
  size_t vec_memsize = batch_size * sizeof(Vec3_d);
  size_t double_memsize = batch_size * sizeof(double);
  Vec3_d *d_a, *d_b;
  double *d_c;
      if (cudaMalloc(&d_a, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_b, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_c, double_memsize) != cudaSuccess) {
        fprintf(stderr, "CUDA memory allocation failed\n");
    }
    if (cudaMemcpy(d_a, v1, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess ||
        cudaMemcpy(d_b, v2, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to device failed\n");
    }
    int threadsPerBlock = 256;
    int blocksPerGrid = (batch_size + threadsPerBlock - 1) / threadsPerBlock;
    vec3d_dot_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, batch_size);
    cudaError_t kernelError = cudaGetLastError();
    if (kernelError != cudaSuccess) {
        fprintf(stderr, "Kernel launch error: %s\n", cudaGetErrorString(kernelError));
    }
    if (cudaMemcpy(result, d_c, double_memsize, cudaMemcpyDeviceToHost) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to host failed\n");
    }

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

}
void vec3d_mul_cuda(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int batch_size) {
  size_t vec_memsize = batch_size * sizeof(Vec3_d);
  Vec3_d *d_a, *d_b, *d_c;
      if (cudaMalloc(&d_a, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_b, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_c, vec_memsize) != cudaSuccess) {
        fprintf(stderr, "CUDA memory allocation failed\n");
    }
    if (cudaMemcpy(d_a, v1, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess ||
        cudaMemcpy(d_b, v2, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to device failed\n");
    }
    int threadsPerBlock = 256;
    int blocksPerGrid = (batch_size + threadsPerBlock - 1) / threadsPerBlock;
    vec3d_mul_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, batch_size);
    cudaError_t kernelError = cudaGetLastError();
    if (kernelError != cudaSuccess) {
        fprintf(stderr, "Kernel launch error: %s\n", cudaGetErrorString(kernelError));
    }
    if (cudaMemcpy(result, d_c, vec_memsize, cudaMemcpyDeviceToHost) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to host failed\n");
    }

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
} 

void vec3d_cross_cuda(Vec3_d *v1, Vec3_d *v2, Vec3_d *result, int batch_size) {
  size_t vec_memsize = batch_size * sizeof(Vec3_d);
  Vec3_d *d_a, *d_b, *d_c;
      if (cudaMalloc(&d_a, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_b, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_c, vec_memsize) != cudaSuccess) {
        fprintf(stderr, "CUDA memory allocation failed\n");
    }
    if (cudaMemcpy(d_a, v1, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess ||
        cudaMemcpy(d_b, v2, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to device failed\n");
    }
    int threadsPerBlock = 256;
    int blocksPerGrid = (batch_size + threadsPerBlock - 1) / threadsPerBlock;
    vec3d_cross_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, batch_size);
    cudaError_t kernelError = cudaGetLastError();
    if (kernelError != cudaSuccess) {
        fprintf(stderr, "Kernel launch error: %s\n", cudaGetErrorString(kernelError));
    }
    if (cudaMemcpy(result, d_c, vec_memsize, cudaMemcpyDeviceToHost) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to host failed\n");
    }
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
} 



void vec3d_cosine_similarity_cuda(Vec3_d *v1, Vec3_d *v2, double *result, int batch_size) {
  size_t vec_memsize = batch_size * sizeof(Vec3_d);
  size_t double_memsize = batch_size * sizeof(double);
  Vec3_d *d_a, *d_b;
  double *d_c;
      if (cudaMalloc(&d_a, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_b, vec_memsize) != cudaSuccess ||
        cudaMalloc(&d_c, double_memsize) != cudaSuccess) {
        fprintf(stderr, "CUDA memory allocation failed\n");
    }
    if (cudaMemcpy(d_a, v1, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess ||
        cudaMemcpy(d_b, v2, vec_memsize, cudaMemcpyHostToDevice) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to device failed\n");
    }
    int threadsPerBlock = 256;
    int blocksPerGrid = (batch_size + threadsPerBlock - 1) / threadsPerBlock;
    vec3d_cosine_similarity_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, batch_size);
    cudaError_t kernelError = cudaGetLastError();
    if (kernelError != cudaSuccess) {
        fprintf(stderr, "Kernel launch error: %s\n", cudaGetErrorString(kernelError));
    }
    if (cudaMemcpy(result, d_c, double_memsize, cudaMemcpyDeviceToHost) != cudaSuccess) {
        fprintf(stderr, "CUDA memory copy to host failed\n");
    }

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

}

