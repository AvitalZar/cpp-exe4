#tchykzr@gamil.com
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -Icontainer -Itests
HEADERS = $(wildcard container/*)

main: Demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o main
	./main

test: tests/test.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o test
	./test


valgrind: main test
	valgrind --leak-check=full ./main
	valgrind --leak-check=full ./test

clean:
	rm -f main test
