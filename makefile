CC = g++
CFLAGS = -c
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: app

app: main.o
	$(CC) main.o -o app $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f *.o app
