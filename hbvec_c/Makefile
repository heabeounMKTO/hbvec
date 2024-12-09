test_scalar:
	gcc -march=native test.c -o test -lm
	./test
test_simd:
	gcc -DHB_VEC_SIMD=ON -march=native test.c -o test -lm
	./test

test_sc: test_scalar test_simd

test_cuda:
	nvcc -DHB_VEC_CUDA=ON hbvec.cu test_cuda.c -o test
