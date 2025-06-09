CXX = g++
CXXFLAGS = -std=c++17 -Wall
HEADERS = MyContainer.hpp OrderIT.hpp ReverseOrderIT.hpp MiddleOutOrderIT.hpp

main: Demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o main
	./main

valgrind: main
	valgrind --leak-check=full ./main

clean:
	rm -f main
