all:
	g++ -std=c++0x main.cpp CMatrix.h CMatrix.cpp -o matrix
clean:
	rm matrix




