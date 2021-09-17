# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================

SRCS 	= matrix.C \
		  image.C \
		  light.C \
		  scene_parser.C \
		  glCanvas.C \
		  rayTree.C \
		  boundingbox.C

SRCSCPP = main.cpp \
		  sphere.cpp \
		  plane.cpp \
		  triangle.cpp \
		  transform.cpp \
		  camera.cpp \
		  group.cpp	\
		  object3d.cpp \
		  material.cpp \
		  rayTracer.cpp \
		  grid.cpp \
		  marchingInfo.cpp

# ===============================================================

LIBS    = -lm -L"D:\Develope\mingw-w64\mingw64\lib"
INCLUDE = -I"D:\Develope\mingw-w64\mingw64\include"
LDFLAGS	= -lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows
CFLAGS	= -g -DDEBUG
CC		= g++
EXE	  	= raytracer
OBJS =  $(SRCS:.C=.o) $(SRCSCPP:.cpp=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) $(INCLUDE) -E -M $(SRCS) $(SRCSCPP) > Makefile.depend

clean: 
	del *~ *bak *.o  core.* Makefile.depend $(EXE).exe /f

# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) $(INCLUDE) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

.C.o:
	$(CC) $(INCLUDE) $< -c -o $@ $(CFLAGS)

.cpp.o:
	$(CC) $(INCLUDE) $< -c -o $@ $(CFLAGS)

# ===============================================================

-include Makefile.depend