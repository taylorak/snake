# Makefile

CC =gcc
DEBUG=-g
CFLAGS=-Wall $(DEBUG)
LIBS=-lcurses
OBJS=snake.o item.o main.o
EXE=snake 

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE) $(LIBS)

main.o: main.c snake.h item.h
	$(CC) $(CFLAGS) -c  main.c

snake.o: snake.c snake.h item.h
	$(CC) $(CFLAGS) -c  snake.c 

item.o: item.c item.h snake.h
	$(CC) $(CFLAGS) -c  item.c

run: $(EXE) 
	./$(EXE) 

clean:
	rm *.o
	rm $(EXE)
