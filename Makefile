CC=g++

make: determinant.cpp
	$(CC) -std=c++11 -o determinant determinant.cpp

clean:
	rm determinant