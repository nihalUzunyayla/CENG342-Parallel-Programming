
CC = mpicc
CFLAGS = -I.
DEPS = hellofunc.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

19050111018: 19050111018.o hellofunc.o
	$(CC) -o 19050111018 19050111018.o hellofunc.o

clean:
	rm -f *.o 19050111018	

	
