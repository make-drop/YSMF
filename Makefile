CXXFLAGS = -D NDEBUG -O3
#CXXFLAGS =
main: main.o
	g++ -std=c++0x  main.o -o main
main.o: main.cpp
	g++ -c -std=c++0x $(CXXFLAGS) main.cpp -o main.o
.PHONY: clean
clean:
	rm *.o main