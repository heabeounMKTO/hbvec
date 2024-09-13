SSE:= -msse -msse2 -msse3

test:
	gcc ${SSE} -march=native test.c vec.c -O3 -ffast-math -lm -o build/test && ./build/test
