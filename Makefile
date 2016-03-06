EXEFILE = myprogram
LIBS = -lglfw -lGLU -lGL
LIBDIRS += -L/usr/X11R6/lib -L/usr/X11R6/lib64 -L/usr/local/lib
INCDIRS += -I/usr/include -I/usr/local/include -I/usr/include/GL
CFLAGS = -std=c++11

$(EXEFILE): main.cpp program.cpp bspline.cpp nurbs.cpp
	g++ -o $(EXEFILE) $(LIBDIRS) $(INCDIRS) $(LIBS) $(CFLAGS)  main.cpp program.cpp bspline.cpp nurbs.cpp

clean:
	rm $(EXEFILE)
