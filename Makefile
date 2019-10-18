all:main
main:main.o file.o findAlgorithm.o
	g++ -g ~/CProject/test_c/main.o file.o findAlgorithm.o -o  ~/CProject/test_c/main

main.o:main.cpp
	g++ -g -c  ~/CProject/test_c/main.cpp -o ~/CProject/test_c/main.o

file.o:file.cpp
	g++ -g -c  ~/CProject/test_c/file.cpp -o ~/CProject/test_c/file.o

findAlgorithm.o:findAlgorithm.cpp
	g++ -g -c  ~/CProject/test_c/findAlgorithm.cpp -o ~/CProject/test_c/findAlgorithm.o
	
clean:
		rm -f ~/CProject/test_c/*.o ~/CProject/test_c/main
