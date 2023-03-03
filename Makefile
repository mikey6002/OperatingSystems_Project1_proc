CC = gcc
Flags = -Wall -Werror

all: warmup1,warmup2,myps

cpuinfo:
	$(CC) warmup1.c -c $(FLAGS)


meminfo:
	$(CC) warmup2.c -c $(FLAGS)


ps:
	$(CC) myps.c -c $(FLAGS)



# https://askubuntu.com/questions/433943/how-to-clean-executable-using-make-clean

.Phony: clean
clean:
	-rm *.o $(objects) warmup1 warmup2 myps


