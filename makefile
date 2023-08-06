CC = g++
CFLAGS = -c
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: app

app: main.o pipe.o
	$(CC) main.o pipe.o -o app $(LDFLAGS)

pipe.o: pipe.cpp pipe.hpp
	$(CC) $(CFLAGS) pipe.cpp

main.o: main.cpp pipe.hpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f *.o app
