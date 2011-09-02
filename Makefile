
test: fast_strtox.h test.cpp
	g++ -O3 test.cpp -o test
	./test

benchmark: fast_strtox.h benchmark.cpp
	g++ -O3 benchmark.cpp -o benchmark
	./benchmark
	clang++ -O3 benchmark.cpp -o benchmark
	./benchmark

