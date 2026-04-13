.PHONY: all clean

all:
	c++ -std=c++17 -c lambda.cpp -o lambda.o
	c++ -std=c++11 -c template.cpp -o template.o

clean:
	rm -f *.o
