#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size, N;
    N = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double MPI_Wtime(void);
    double local_start, local_finish, local_elapsed, elapsed;
    MPI_Barrier(MPI_COMM_WORLD);
    local_start = MPI_Wtime();

    // Calculate the assigned numbers for each process
    int chunk = (N + size) / size;
    int start = rank * chunk + 1;
    if (start < 2) start = 2;
    int end = (rank + 1) * chunk;
    if (end > N) end = N;

    // Mark composite numbers
    int *local_prime = (int *)malloc((N+1) * sizeof(int));
    memset(local_prime, 1, (N+1) * sizeof(int));
    int limit = (int)((N+1)/2);
    for (int p = 2; p <= limit; p++) {
        // Find the first multiple of p
        int first_multiple;
        if (p * p > start)
            first_multiple = p * p;
        else {
            if (start % p == 0)
                first_multiple = start;
            else
                first_multiple = start + (p - start % p);
        }

        // Mark all multiples of p
        for (int i = first_multiple; i <= end; i += p) {
            local_prime[i] = 0;
        }
    }

    // Collect results
    int *prime = NULL;
    if (rank == 0) {
        prime = (int *)malloc((N+1) * sizeof(int));
        memset(prime, 1, (N+1) * sizeof(int));
    }
    // MPI_Gather(local_prime, N + 1, MPI_INT, prime, N + 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(local_prime, prime, N+1, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);
    free(local_prime);

    // Collect times
    local_finish = MPI_Wtime();
    local_elapsed = local_finish - local_start;
    MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Finalize();

    if (rank == 0) {
        // Print time
        printf("Elapsed time = %e seconds\n", elapsed);

        // Store results
        char filename[20];
        snprintf(filename, sizeof(filename), "%d.txt", N);
        FILE *file = fopen(filename, "w");
        
        for (int i = 2; i <= N; i++) {
            if (prime[i]) {
                fprintf(file, "%d ", i);
            }
        }
        fclose(file);
        free(prime);
    }

    return 0;
}