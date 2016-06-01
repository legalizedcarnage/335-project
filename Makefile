# cs335 group project
# to compile your project, type make and press enter

#all: main

main: main.cpp elijahD.cpp marioH.cpp juliaA.cpp miguelT.cpp miguelB.cpp
	g++ main.cpp elijahD.cpp marioH.cpp juliaA.cpp miguelT.cpp miguelB.cpp ppm.cpp libggfonts.a -Wall -omain -lrt -lX11 -lGL -lGLU -lm
clean:
	rm -f main
	rm -f *.o
