
.PHONY: all prepare compile link clean

CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
INCLUDES=-Iinclude
EXECUTABLE=lab-01_makefile

SOURCES = main.c io.c util.c algorithm.c


.PHONY :prepare compile link clean

all :  prepare compile link clean

prepare:
	if [ ! -d obj ]; then mkdir obj; fi

compile : main.o util.o io.o algorithm.o

main.o : src/main.c
	gcc $(CFLAGS) $(INCLUDES)  src/main.c -o obj/main.o

util.o : src/util.c
	gcc $(CFLAGS) $(INCLUDES) src/util.c -o obj/util.o

io.o : src/io.c
	gcc $(CFLAGS) $(INCLUDES) src/io.c -o obj/io.o

algorithm.o : src/algorithm.c
	gcc $(CFLAGS) $(INCLUDES) src/algorithm.c -o obj/algorithm.o


link:
	gcc obj/*.o -o $(EXECUTABLE)

clean:
	#rm -rf obj/*.o $(EXECUTABLE)
	rm -rf obj

