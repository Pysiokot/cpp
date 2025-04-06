CXX := g++
CXXFLAGS := -c -std=c++20


all:
	$(CXX) $(CXXFLAGS) *.cpp
	$(CXX) *.o

run: 
	./a.out test.txt

clean:
	rm -f *.o
	rm -f *.out