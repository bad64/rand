rand: main.o
	gcc -O2 main.o -o rand

main.o: main.c
	gcc -c main.c

.PHONY: install
install: rand
	cp rand /usr/bin/rand
	chmod a+x /usr/bin/rand

.PHONY: uninstall
uninstall:
	rm -rf /usr/bin/rand

.PHONY: clean
clean :
	rm main.o
