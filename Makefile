CC=gcc
CFLAGS= -g -std=c11 -pedantic -Wall -Wextra -O2
CFLAGS-I= -g -std=c11 -pedantic -Wall -Wextra -O2 -DUSE_INLINE

all: primes primes-i steg-decode

run: primes primes-i
	./primes
	./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -lm primes.o eratosthenes.o error.o -o primes

primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $(CFLAGS-I) -lm primes-i.o eratosthenes-i.o error.o -o primes-i

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o
	$(CC) $(CFLAGS) -lm steg-decode.o ppm.o error.o eratosthenes.o -o steg-decode

primes.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -o primes.o

primes-i.o: primes.c
	$(CC) $(CFLAGS-I) -c primes.c -o primes-i.o

eratosthenes.o: eratosthenes.c
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c
	$(CC) $(CFLAGS-I) -c eratosthenes.c -o eratosthenes-i.o

error.o: error.c
	$(CC) $(CFLAGS) -c error.c -o error.o

steg-decode.o: steg-decode.c
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o

ppm.o: ppm.c
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

clean:
	rm *.o primes primes-i steg-decode
