edsac : main.o edsac.o
	gcc -o edsac main.o edsac.o

main.o : main.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c

edsac.o : edsac.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o edsac.o edsac.c