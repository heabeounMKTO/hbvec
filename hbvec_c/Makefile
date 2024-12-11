SRC_DIR=.
CC = gcc
NVCC = nvcc
BIN_DIR=bin
AR = ar

CPU_SRC = $(SRC_DIR)/vec.c
GPU_SRC = $(SRC_DIR)/vec_gpu.cu
MAIN_SRC = $(SRC_DIR)/main.c
OBJ_DIR = obj

CPU_OBJ = $(OBJ_DIR)/vec.o
GPU_OBJ = $(OBJ_DIR)/vec_gpu.o
MAIN_OBJ = $(OBJ_DIR)/main.o

STATIC_LIB = $(BIN_DIR)/libvec_gpu.a
OUTPUT = $(BIN_DIR)/program


CFLAGS = -I$(SRC_DIR)
LDFLAGS = 


# Compile CPU vector operations

# Compile GPU vector operations (optional)
hbvec_cuda: $(GPU_SRC) $(SRC_DIR)/vec_gpu.h
	mkdir -p ${OBJ_DIR}
	$(NVCC) -c ${GPU_SRC} -o ${GPU_OBJ} 

hbvec_gpu_static: hbvec_cuda 
	mkdir -p $(BIN_DIR)
	$(AR) rcs ${STATIC_LIB} ${GPU_OBJ} 

test_scalar:
	gcc test.c -o test -lm

# ayyy
# hbvec_gpu:
# 	mkdir -p libs
# 	nvcc -c vec_gpu.cu -o libs/vecgpu.o
# 	ar rcs libs/libhbvecgpu.a libs/vecgpu.o

test_cuda: hbvec_gpu
	gcc -DHBVEC_USE_CUDA test_cuda.c -L libs/ -lhbvecgpu -lcudart -lm -o test_cuda
	./test_cuda
