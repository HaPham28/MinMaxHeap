PROJ = driver.out
CXX  = g++
CXXFLAGS = -g -ansi -Wall -std=c++11
OBJS = Proj3CensusTest.o

$(PROJ): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(PROJ) $(OBJS)

Proj3CensusTest.o: Proj3CensusTest.cpp Int4MMH.h CensusCity.h MMHeap.h QHeap.h
	$(CXX) $(CXXFLAGS) -c $<



# -f removes any error messages if the file is not present
.PHONY: clean run valgrind
clean:
	rm -rf *.o
	rm -f *.out
	
	
val:
	valgrind ./$(PROJ)
run:
	./$(PROJ)
