.phony := all clean

PROGS := arducam-demo nocv-demo
OBJS := LibCamera.o main.o
## note: OBJS only for arducam-demo

CXXFLAGS := -Wall -O3 -std=c++17 -I/usr/local/include/libcamera
CXXLDFLAGS := -L/usr/local/lib -lcamera-base -lcamera -lopencv_core -lopencv_highgui

## no opencv version
NCVLDFLAGS := -L/usr/local/lib -lcamera-base -lcamera

all : ${PROGS}


LibCamera.o: LibCamera.cpp LibCamera.h
	g++ ${CXXFLAGS} -c -o $@ $<
main.o: main.cpp LibCamera.h
	g++ ${CXXFLAGS} -c -o $@ $<

arducam-demo: ${OBJS}
	g++ -o $@ $^ ${CXXLDFLAGS}

main_nocv.o: main_nocv.cpp LibCamera.h
	g++ ${CXXFLAGS} -c -o $@ $<

nocv-demo: main_nocv.o LibCamera.o
	g++ -o $@ $^ ${NCVLDFLAGS}

clean:
	rm -f ${PROGS} ${OBJS} main_nocv.o
