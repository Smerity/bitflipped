all: bitflip

bitflip: bitflip.c
	$(CC) -O3 -Wall -W -pedantic -std=c99 -o bitflip bitflip.c

clean:
	rm bitflip
