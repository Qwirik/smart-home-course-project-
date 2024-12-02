all: main.c login.c hash.c
	gcc -o program main.c login.c hash.c

clear: rm program
	clear
