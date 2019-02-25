# Variable utilizada
CC=gcc

# all es usado para que compile los 3 programas
all:emisor clasifica estadistica

emisor : emisor.o
	$(CC) -o $@ $^
emisor.o : emisor.c
	$(CC) -c $^

clasifica: clasifica.o leer.o imprimir.o datos.h
	$(CC) -o $@ $< leer.o imprimir.o
clasifica.o : clasifica.c
	$(CC) -c $^
leer.o : leer.c
	$(CC) -c $^
imprimir.o : imprimir.c
		$(CC) -c $^

estadistica : estadistica.o datos.h
	$(CC) -o $@ $<
estadistica.o : estadistica.c
	$(CC) -c $^

clean:
	rm *.o
