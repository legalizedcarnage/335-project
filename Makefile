# cs335 group project
# to compile your project, type make and press enter

#all: main

main: main.cpp davis.cpp
	g++ main.cpp davis.cpp -Wall -omain -lX11 -lGL -lGLU -lm

clean:
	rm -f main
	rm -f *.o
