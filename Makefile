SSE:= -msse -msse2 -msse3
AVX:= -mavx

test:
	mkdir -p build/bin
	gcc -march=native test.c vec.c -O3 -ffast-math -lm -o build/test && ./build/bin/test

test_compare: test_scalar test_simd

test_scalar:
	mkdir -p build/bin
	gcc -march=native -DHB_VEC_SCALAR=1 test_scalar.c vec.c -O3 -ffast-math -lm -o build/bin/test_scalar && ./build/bin/test_scalar

test_simd:
	mkdir -p build/bin
	gcc -march=native test_simd.c vec.c -O3 -ffast-math -lm  -o build/bin/test_simd && ./build/bin/test_simd

test_d:
	mkdir -p build/bin
	gcc -march=native test_doub.c vec.c -O3 -ffast-math -lm -o build/bin/testdoub && ./build/bin/testdoub

debug:
	mkdir -p build/bin 
	gcc -march=native test.c vec.c -O3 -ffast-math -lm -S build/test 

obj:
	mkdir -p build/obj 
	gcc -shared -DHB_VEC_SHARED -march=native -o build/obj/libhbvec.so -fPIC vec.c -lm -ffast-math 

test_arm:
	mkdir -p build/bin
	clang -o build/bin/test_arm vec.c test_arm.c  && ./build/bin/test_arm
