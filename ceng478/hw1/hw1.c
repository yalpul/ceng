#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

float *numbers;
float *buf;
double time;

float *read_file(char *fname, int num);

int world_rank;
int world_size;
int num;

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
	num = atoi(argv[2]);
	int each = num / world_size;
	if (world_rank == 0)
		buf = read_file(argv[1], num);
	if (world_size > 1){
		if (num % world_size == 0){
			numbers = malloc(each * sizeof(float));
			MPI_Scatter(buf, each, MPI_FLOAT, numbers, each, MPI_FLOAT, 0, MPI_COMM_WORLD);
			time = MPI_Wtime();
			for (int i = 1; i < each; i++)
				numbers[0] = MAX(numbers[0], numbers[i]);
		}
		else if (world_rank == 0)
			master_routine();
		else
			worker_routine();
	}
	else{
		numbers = buf;
		buf = NULL;
		time = MPI_Wtime();
		for (int i = 1; i < num; i++)
			numbers[0] = MAX(numbers[0], numbers[i]);
	}
	/*
	if (world_rank == 0)
		if (world_size > 1)
			master_routine(argv[1], argv[2]);
		else{
			read_file(argv[1], num);
		}
	else
		worker_routine();
		*/

	for (int current = world_size, stride = 1; current > 1; current /= 2, stride *= 2)
		if (world_rank % stride == 0){
			if (world_rank % (2*stride))
				MPI_Send(&numbers[0], 1, MPI_FLOAT, world_rank-stride, 0, MPI_COMM_WORLD);
			else{
				float other;
				MPI_Recv(&other, 1, MPI_FLOAT, world_rank+stride, 0, MPI_COMM_WORLD, &stat);
				numbers[0] = MAX(numbers[0], other);
			}
		}

	if (world_rank == 0){
		printf("Max_Value %.1f\n", numbers[0]);
		printf("Total_Time %.6f\n", MPI_Wtime()-time);
		free(buf);
	}

	free(numbers);
    // Finalize the MPI environment.
    MPI_Finalize();
}

void master_routine()
{
	int each = num / world_size;
	int num_each[world_size];
	for (int i = 0; i < world_size; i++)
		num_each[i] = each;
	int leftover = num - (each*world_size);
	for (int i = 0; i < leftover; i++)
		num_each[i]++;
	int current = num_each[0];
	for (int i = 1; i < world_size; i++){
		MPI_Send(&num_each[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		MPI_Send(numbers+current, num_each[i], MPI_FLOAT, i, 1, MPI_COMM_WORLD);
		current += num_each[i];
	}
	time = MPI_Wtime();
	for (int i = 1; i < num_each[0]; i++)
		numbers[0] = MAX(numbers[0], numbers[i]);
}

void worker_routine()
{ 
	MPI_Status stat;
	int num_to_recv;
	MPI_Recv(&num_to_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
	numbers = malloc(num_to_recv * sizeof(float));
	MPI_Recv(numbers, num_to_recv, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &stat);
	for (int i = 1; i < num_to_recv; i++)
		numbers[0] = MAX(numbers[0], numbers[i]);
}

float *read_file(char *fname, int num)
{
	FILE *num_file = fopen(fname, "r");
	int i = 0;
	float *numbers = malloc(num * sizeof(float));
	while (fscanf(num_file, "%f", &numbers[i++]) != EOF)
		;
	fclose(num_file);
	return numbers;
}
