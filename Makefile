EXEC= gauss imscan imscan2 interim lhermite matinv rhermite

CC=gcc
CFLAGS= -Wall -O4 -g
LDLIBS= -L/usr/local/lib -lpolylib64 -lpthread 

all: $(EXEC)

imscan: wd.o
imscan2: wd.o

clean:
	-rm -f *.o
	-rm -f a.out core
	-rm -f $(EXEC)
