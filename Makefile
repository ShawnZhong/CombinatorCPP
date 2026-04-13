CXX = c++

all: main template

main: main.cpp
	$(CXX) -std=c++17 $< -o $@

template: template.cpp
	$(CXX) -std=c++11 -c $< -o $@

clean:
	rm -f main template
