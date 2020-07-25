CC=mpicc
OUT=tournament
SOURCES=hw2.c

all:
	$(CC) -O3 -Wall -o $(OUT) $(SOURCES)
	strip $(OUT)

job:
	sbatch submit.sh
