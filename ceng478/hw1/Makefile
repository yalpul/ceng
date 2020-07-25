CC=mpicc
OUT=summer
SOURCES=hw1.c

all:
	$(CC) -O3 -Wall -o $(OUT) $(SOURCES)
	strip $(OUT)

job:
	sbatch submit.sh
