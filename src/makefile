CC = g++
LIBS = -lceledsexporter -lceleds -lmalaes -lcellml

all: main

main: cellml2c.cpp
	$(CC) cellml2c.cpp $(LIBS) -o ../bin/cellml2c

clean:
	rm ../bin/cellml2c
