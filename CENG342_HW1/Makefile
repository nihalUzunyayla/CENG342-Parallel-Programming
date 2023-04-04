CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: 19050111018.o hellofunc.o 
	$(CC) -o 19050111018 19050111018.o hellofunc.o 	
	
