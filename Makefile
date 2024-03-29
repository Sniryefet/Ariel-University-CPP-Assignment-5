#!make -f

all: demo
	./$<

demo:  demo.o 
	clang++-5.0 -std=c++17 $^ -o demo

test:  test.o 
	clang++-5.0 -std=c++17 $^ -o test

%.o: %.cpp range.hpp chain.hpp powerset.hpp product.hpp zip.hpp
	clang++-5.0 -std=c++17 --compile $< -o $@

clean:
	rm -f *.o demo test
