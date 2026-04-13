CXX = c++

all: lambda.o template.o

lambda.o: lambda.cpp
	$(CXX) -std=c++17 -c $< -o $@

template.o: template.cpp
	$(CXX) -std=c++11 -c $< -o $@

clean:
	rm -f lambda.o template.o
