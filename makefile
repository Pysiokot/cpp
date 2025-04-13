CXX := g++
CXXFLAGS := -c -O1

0:
	$(CXX) $(CXXFLAGS) -DZERO Homework.cpp Helpers.cpp 
	 $(CXX) Homework.o Helpers.o 

0_bench:
	$(CXX) $(CXXFLAGS) -DZERO -DBENCH Homework.cpp Helpers.cpp
	$(CXX) Homework.o Helpers.o 

1:
	$(CXX) $(CXXFLAGS) -DONE Homework.cpp Helpers_1.cpp
	$(CXX) Homework.o Helpers_1.o

1_bench:
	$(CXX) $(CXXFLAGS) -DONE -DBENCH Homework.cpp Helpers_1.cpp
	$(CXX) Homework.o Helpers_1.o

2:
	$(CXX) $(CXXFLAGS) -DTWO Homework.cpp Helpers_2.cpp
	$(CXX) Homework.o Helpers_2.o

2_bench:
	$(CXX) $(CXXFLAGS) -DTWO -DBENCH Homework.cpp Helpers_2.cpp
	$(CXX) Homework.o Helpers_2.o

3:
	$(CXX) $(CXXFLAGS) -DTHREE Homework.cpp Helpers_3.cpp
	$(CXX) Homework.o Helpers_3.o

4: 
	$(CXX) $(CXXFLAGS) -DFOUR Homework.cpp Helpers_4.cpp
	$(CXX) Homework.o Helpers_4.o

4_bench: 
	$(CXX) $(CXXFLAGS) -DFOUR -DBENCH Homework.cpp Helpers_4.cpp
	$(CXX) Homework.o Helpers_4.o

5:
	$(CXX) $(CXXFLAGS) -Xpreprocessor -fopenmp -DFIVE Homework.cpp Helpers_5.cpp -I/opt/homebrew/opt/libomp/include
	$(CXX) Homework.o Helpers_5.o -L/opt/homebrew/opt/libomp/lib/ -lomp

5_bench:
	$(CXX) $(CXXFLAGS) -Xpreprocessor -fopenmp -DFIVE -DBENCH Homework.cpp Helpers_5.cpp -I/opt/homebrew/opt/libomp/include
	$(CXX) Homework.o Helpers_5.o -L/opt/homebrew/opt/libomp/lib/ -lomp

debug_simple:
	$(CXX) $(CXXFLAGS) -DDLOG *.cpp
	$(CXX) *.o

debug_all:
	$(CXX) $(CXXFLAGS) -DDLOG -DDLOG_PROCESS *.cpp
	$(CXX) *.o

run_bench:
	./a.out

run_prof: 
	# env CPUPROFILE=cpu.profile ./a.out
	# pprof --text a.out cpu.profile
	./cpu_profile a.out

clean:
	rm -f *.o
	rm -f *.out
	rm -f hw