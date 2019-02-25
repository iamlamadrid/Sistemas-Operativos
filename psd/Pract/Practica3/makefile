# Variable utilizada
CC=gcc
hilos : hilos.o
	$(CC) -o hilos hilos.o -lpthread
hilos.o : hilos.c datos.h
	$(CC) -c hilos.c
clean:
	rm hilos *.o
