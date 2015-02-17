CC = g++
LIBS = -lceledsexporter -lceleds -lmalaes -lcellml

all: main

main: cellml2c.cpp
	$(CC) cellml2c.cpp $(LIBS) -o ../bin/cellml2c
	cp C.xml ../bin/
clean:
	rm ../bin/*
