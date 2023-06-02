CXX ?= g++

fileserver: main.cpp server.cpp pool.cpp event.cpp utils.cpp
	$(CXX) -std=c++11  $^ -lpthread  -o main

clean:
	rm  -r main
