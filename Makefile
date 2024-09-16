SSE:= -msse -msse2 -msse3
OPEN_CL:=-lOpenCL
CL_TARGET_OPENCL_VERSION:=100 

test:
	mkdir -p build
	gcc ${SSE} -march=native test.c vec.c -O3 -ffast-math -lm -o build/test && ./build/test

test_gpu:
	mkdir -p build
	gcc -DHB_VEC_GPU -march=native test_gpu.c vec_gpu.c -O3 -ffast-math ${OPEN_CL} -lm -o  build/test_gpu && ./build/test_gpu


test_arm:
	mkdir -p build
	clang -o build/test_arm vec.c test_arm.c  && ./build/test_arm
