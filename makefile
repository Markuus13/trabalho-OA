name = my_disk.cpp
dir = modules/
mode = -std=c99
#mode = -ansi

all:
	gcc -Wall $(mode) $(dir)main.c -o $(name)
	#./$(name)

remove:
	rm *.o
