# cs335 group project
# to compile your project, type make and press enter

#all: main

main: main.cpp davis.cpp mario.cpp julia.cpp 
	g++ main.cpp davis.cpp mario.cpp julia.cpp libggfonts.a -Wall -omain -lX11 -lGL -lGLU -lm
clean:
	rm -f main
	rm -f *.o
