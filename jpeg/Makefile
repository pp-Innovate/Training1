CC=gcc
LD=gcc

CFLAGS=-g -Wall -O2

#下面两行分别是jpeglib.h和libjpeg.so所在的路径，请根据实际修改
INCDIR=/usr/include/
LIBDIR=/usr/lib/arm-linux-gnueabihf/
LIBS=-ljpeg

demo:main.o imgFile.o imgProcess.o
	$(LD) -o $@ $^ $(CFLAGS) -L$(LIBDIR) $(LIBS)

main.o:main.c imgFile.h imgProcess.h
	$(CC) -c -o $@ main.c $(CFLAGS) -I$(INCDIR) 	

imgFile.o:imgFile.c imgFile.h
	$(CC) -c -o $@ imgFile.c $(CFLAGS) -I$(INCDIR)

imgProcess.o:imgProcess.c imgProcess.h
	$(CC) -c -o $@ imgProcess.c $(CFLAGS) -I$(INCDIR)

clean:
	rm -rf *.o demo
