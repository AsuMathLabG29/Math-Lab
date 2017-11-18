all:
	g++ main.cpp CMatrix.h CMatrix.cpp -o matrix
clean:
	rm matrix

