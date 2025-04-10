CXX := g++
CXXFLAGS := -c -std=c++20

0:
	$(CXX) $(CXXFLAGS) -DZERO Homework.cpp Helpers.cpp
	$(CXX) Homework.o Helpers.o

1:
	$(CXX) $(CXXFLAGS) -DONE Homework.cpp Helpers_1.cpp
	$(CXX) Homework.o Helpers_1.o

2:
	$(CXX) $(CXXFLAGS) -DTWO Homework.cpp Helpers_2.cpp
	$(CXX) Homework.o Helpers_2.o

3:
	$(CXX) $(CXXFLAGS) -DTHREE Homework.cpp Helpers_3.cpp
	$(CXX) Homework.o Helpers_3.o

4: 
	$(CXX) $(CXXFLAGS) -DFOUR Homework.cpp Helpers_4.cpp
	$(CXX) Homework.o Helpers_4.o

debug_simple:
	$(CXX) $(CXXFLAGS) -DDLOG *.cpp
	$(CXX) *.o

debug_all:
	$(CXX) $(CXXFLAGS) -DDLOG -DDLOG_PROCESS *.cpp
	$(CXX) *.o

run: 
	./a.out test.txt

clean:
	rm -f *.o
	rm -f *.out