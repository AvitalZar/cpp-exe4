CXX = g++
CXXFLAGS = -std=c++17 -Wall
HEADERS = MyContainer.hpp OrderIT.hpp ReverseOrderIT.hpp MiddleOutOrderIT.hpp

main: Demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o main
	./main

test: test.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o test
	./test


valgrind: main test
	valgrind --leak-check=full ./main
	valgrind --leak-check=full ./test

clean:
	rm -f main
