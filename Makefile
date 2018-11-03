rand: main.o
	gcc -O2 main.o -o rand

main.o: main.c
	gcc -c main.c

.PHONY: install
install: rand
	cp rand /usr/local/bin/rand
	chmod a+x /usr/local/bin/rand

.PHONY: uninstall
uninstall:
	rm -rf /usr/local/bin/rand

.PHONY: clean
clean:
	rm main.o

.PHONY: distclean
distclean:
	rm -rf main.o rand

.PHONY: love
love:
	echo "Not war ?"
