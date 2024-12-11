test_scalar:
	gcc test.c -o test -lm



hbvec_gpu:
	mkdir -p libs
	nvcc -c vec_gpu.cu -o libs/vecgpu.o
	ar rcs libs/libhbvecgpu.a libs/vecgpu.o

test_cuda: hbvec_gpu
	gcc test_cuda.c -L libs/ -lhbvecgpu -lcudart -lm -o test_cuda
