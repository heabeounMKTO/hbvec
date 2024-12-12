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
	gcc -march=native test.c -o test -lm
	./test
test_simd:
	gcc -DHB_VEC_SIMD=ON -march=native test.c -o test -lm
	./test

test_sc: test_scalar test_simd

# ayyy
cudavec:
	mkdir -p libs
	nvcc -c vec_gpu.cu -o libs/vec_gpu.o
	ar rcs libs/libhbvec_gpu.a libs/vec_gpu.o
	rm libs/vec_gpu.o

test_gpu: cudavec 
	mkdir -p build
	gcc test_cuda.c -L./libs -lhbvec_gpu -lcudart -o build/test_gpu -lm 
	./build/test_gpu
