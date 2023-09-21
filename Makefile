# for Opengl
CCGL=g++
GL_CFLAGS = -O2 -DSHM -DHZ=100
XLIBS = -lXext -lXmu -lXi -lX11
CYG_OpenGL = -lglut -lGLU -lGL
LINUX_OpenGL =  -lglut -lGLU -lGL $(XLIBS) 
GL_LIBS += $(CYG_OpenGL) -lm 
INC_FILES= $(wildcard *.cpp) $(wildcard *.o)

all: main

main: main.c 
	$(CCGL) $(GL_CFLAGS) $^ $(GL_LIBS) -o $@ 

clean:
	rm -rf *.exe

start:
	startxwin ./main.exe -- -nowgl