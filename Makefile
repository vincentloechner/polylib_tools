
# specify the right location here, if it's not a standard location:
POLYLIB_LOC= /home/vincent/polylib

EXEC= gauss imscan2 interim lhermite matinv rhermite
CFLAGS= -I${POLYLIB_LOC}/include -Wall -O3 -g
LDLIBS= -L${POLYLIB_LOC}/lib -lpolylib64 -lpthread

all: $(EXEC)

imscan: wd.o
imscan2: wd.o

clean:
	-rm -f *.o
	-rm -f a.out core
	-rm -f $(EXEC)
