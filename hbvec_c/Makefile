test_scalar:
	gcc test.c -o test -lm

test_cuda:
	nvcc -DHB_VEC_CUDA=ON hbvec.cu test_cuda.c -o test
