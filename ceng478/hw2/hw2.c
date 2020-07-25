#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

double timer;


int world_rank;
int world_size;
int *buffer;
int *numbers;

int basic_tournament(int *buffer, int n);
int simulate_game();

void master_routine();
void worker_routine();
int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
	MPI_Status stat;

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	srand(time(NULL)+world_rank);
	int num = 1 << atoi(argv[1]);
	int each = num / world_size;
	if (world_rank == 0) {
		buffer = malloc(sizeof(int)*num);
		for (int i = 0; i < num; i++)
			buffer[i] = i;
	}
	if (world_size > 1){
		numbers = malloc(each * sizeof(int));
		MPI_Scatter(buffer, each, MPI_INT, numbers, each, MPI_INT, 0, MPI_COMM_WORLD);
		timer = MPI_Wtime();
		basic_tournament(numbers, each);
	}
	else{
		timer = MPI_Wtime();
		numbers = buffer;
		buffer = NULL;
		basic_tournament(numbers, num);
	}

	for (int current = world_size, stride = 1; current > 1; current /= 2, stride *= 2)
		if (world_rank % stride == 0){
			if (world_rank % (2*stride))
				MPI_Send(&numbers[0], 1, MPI_INT, world_rank-stride, 0, MPI_COMM_WORLD);
			else{
				int other;
				MPI_Recv(&other, 1, MPI_INT, world_rank+stride, 0, MPI_COMM_WORLD, &stat);
				int result = simulate_game();
				if (!result)
					numbers[0] = other;
			}
		}

	if (world_rank == 0){
		printf("The_Winner %d\n", numbers[0]);
		printf("Total_Time %.6f\n", MPI_Wtime()-timer);
		free(buffer);
	}

	free(numbers);
    // Finalize the MPI environment.
    MPI_Finalize();
}

int simulate_game() {
	usleep(10);
	return rand()%2;
}

int basic_tournament(int *buffer, int n)
{
    for (int stride = 1; stride < n; stride *= 2) {
        for (int i = 0; i < n; i+=2*stride) {
            int result = simulate_game();
            if (!result)
              buffer[i] = buffer[i+stride];
        }
    }
    return buffer[0];
}
