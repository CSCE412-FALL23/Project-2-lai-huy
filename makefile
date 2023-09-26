CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o main.out

all: run

run: clean
	$(CXX) $(CXXFLAGS) ./main.cpp
	./main.out

memory_errors:
	$(CXX) $(CXXFLAGS) ./main.cpp
	valgrind --show-leak-kinds=all --leak-check=full -s ./main.out

clean: 
	rm -f *.gcov *.gcda *.gcno *.out

documentation:
	rm -rf ./docs
	doxygen Doxyfile
