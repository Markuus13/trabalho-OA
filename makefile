compiler = clang
name = my_disk.cpp
dir = modules/
mode = -std=c99
flags = -Wall -g
#mode = -ansi

all: remove logic_drive.o hard_drive.o
	$(compiler) $(flags) $(mode) $(dir)main.c logic_drive.o hard_drive.o -o $(name)
	./$(name)

logic_drive.o:
	$(compiler) -c $(dir)logic_drive.c

hard_drive.o:
	$(compiler) -c $(dir)hard_drive.c

remove:
	rm *.o
