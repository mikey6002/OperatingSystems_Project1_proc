CC = gcc
Flags = -Wall -Werror

all: warmup1,warmup2

cpuinfo:
	$(CC) warmup1.c -c $(FLAGS)


meminfo:
	$(CC) warmup2.c -c $(FLAGS)



clean:
	rm -rf *.o


