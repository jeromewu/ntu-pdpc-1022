all: mpi.hello mpi.msg.hello mpi.tag mpi.status mpi.count mpi.reduce mpi.allreduce mpi.bcast mpi.time mpi.barrier

mpi.hello:
	mpicc mpi.hello.c -o bin/mpi.hello

mpi.msg.hello:
	mpicc mpi.msg.hello.c -o bin/mpi.msg.hello

mpi.tag:
	mpicc mpi.tag.c -o bin/mpi.tag

mpi.status:
	mpicc mpi.status.c -o bin/mpi.status

mpi.count:
	mpicc mpi.count.c -o bin/mpi.count

mpi.reduce:
	mpicc mpi.reduce.c -o bin/mpi.reduce

mpi.bcast:
	mpicc mpi.bcast.c -o bin/mpi.bcast

mpi.allreduce:
	mpicc mpi.allreduce.c -o bin/mpi.allreduce

mpi.time:
	mpicc mpi.time.c -o bin/mpi.time

mpi.barrier:
	mpicc mpi.barrier.c -o bin/mpi.barrier

clean:
	rm bin/*
