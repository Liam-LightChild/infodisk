all: 
	@cp src/*.c .
	make *.o
	@gcc -g -o infodisk *.o
	@rm -f *.o *.c

install: all
	@sudo echo -n
	@if [ -d /usr/lib/infodisk ]; then sudo rm -r /usr/lib/infodisk; fi
	sudo mkdir /usr/lib/infodisk
	sudo cp infodisk /usr/lib/infodisk/BINARY.BIN
	sudo rm -f /usr/bin/infodisk
	sudo ln /usr/lib/infodisk/BINARY.BIN /usr/bin/infodisk