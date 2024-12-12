test_scalar:
	gcc test.c -o test -lm


# ayyy
hbvec_gpu:
	nvcc -c vec_gpu.cu -o vec_gpu.o
	ar rcs libvec_gpu.a vec_gpu.o
	rm vec_gpu.o
	

test_gpu: hbvec_gpu
	gcc test_cuda.c -L. -lvec_gpu -lcudart -o test_gpu -lm 
	./test_gpu
