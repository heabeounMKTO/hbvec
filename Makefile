SSE:= -msse -msse2 -msse3

test:
	mkdir -p build
	gcc ${SSE} -march=native test.c vec.c -O3 -ffast-math -lm -o build/test && ./build/test

test_arm:
	mkdir -p build
	clang -o build/test_arm vec.c test_arm.c  && ./build/test_arm
