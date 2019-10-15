all:main
main.o:main.cpp
		g++ -g -c  ~/CProject/test_c/main.cpp -o ~/CProject/test_c/main.o
main:main.o
		g++ -g ~/CProject/test_c/main.o -o  ~/CProject/test_c/main
clean:
		rm -f ~/CProject/test_c/*.o ~/CProject/test_c/main
