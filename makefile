compiler = gcc
name = my_disk
dir = modules/
flags = -Wall -g
mode = -ansi

all: logic_drive.o hard_drive.o
	$(compiler) $(flags) $(mode) $(dir)main.c $(dir)hard_drive.c $(dir)logic_drive.c -o $(name)
	./$(name)

logic_drive.o:
	$(compiler) -c $(dir)logic_drive.c

hard_drive.o:
	$(compiler) -c $(dir)hard_drive.c

remove:
	rm *.o
