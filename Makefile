test:
	gcc -msse -msse2 -msse3 test.c vec.c -o build/test && ./build/test
