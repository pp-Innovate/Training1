CC=gcc
LD=gcc

CFLAGS=-g -Wall -O2

INCDIR=
LIBDIR=
LIBS=

demo:main.o imgFile.o imgProcess.o
	$(LD) -o $@ $^ $(CFLAGS) 

main.o:main.c imgFile.h imgProcess.h
	$(CC) -c -o $@ main.c $(CFLAGS) 	

imgFile.o:imgFile.c imgFile.h
	$(CC) -c -o $@ imgFile.c $(CFLAGS)

imgProcess.o:imgProcess.c imgProcess.h
	$(CC) -c -o $@ imgProcess.c $(CFLAGS)

clean:
	rm -rf *.o demo
