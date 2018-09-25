rand : main.o
	gcc -O2 main.o -o rand

main.o : main.c
	gcc -c main.c

clean :
	rm main.o
