EXE	= project3

all: project3

project3: main.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -rf ${EXE}