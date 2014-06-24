CC=gcc
MPICC=mpicc
CFLAGS=-lm -g

all:
	$(CC) $(CFLAGS) test.data.gen.c -o test.data.gen.out
	$(CC) $(CFLAGS) mat.seq.c -o mat.seq.out
	$(MPICC) $(CFLAGS) mat.mpi.c -o mat.mpi.out

clean:
	rm -rf *.out
