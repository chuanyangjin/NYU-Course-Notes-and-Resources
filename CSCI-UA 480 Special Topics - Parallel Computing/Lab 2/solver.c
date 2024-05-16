#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char **argv) {
    const char *filename = argv[1];
    int num_threads = atoi(argv[2]);

    // Read input file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int n;
    double error;
    fscanf(file, "%d", &n);
    fscanf(file, "%lf", &error);

    double *x = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf", &x[i]);
    }

    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc((n + 1) * sizeof(double));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }
    fclose(file);


    // Use iterations to calculate all Xs
    double *x_new = (double *)malloc(n * sizeof(double));
    double max_error = error + 1;
    int iteration = 0;
    double start_time = omp_get_wtime();
    while (max_error > error) {
        // Calculate new Xs
        #pragma omp parallel for num_threads(num_threads)
        for (int i = 0; i < n; i++) {
            double sum = matrix[i][n];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum -= matrix[i][j] * x[j];
                }
            }
            x_new[i] = sum / matrix[i][i];
        }

        // Calculate relative errors
        max_error = 0.0;
        for (int i = 0; i < n; i++) {
            double current_error = fabs((x_new[i] - x[i]) / x_new[i]) * 100.0;
            if (current_error > max_error) {
                max_error = current_error;
            }
            x[i] = x_new[i];
        }
        iteration++;
    }
    double end_time = omp_get_wtime();

    printf("total number of iterations: %d\n", iteration);
    printf("Elapsed time = %f seconds\n", end_time - start_time);

    // Store results
    char out_filename[50];
    sprintf(out_filename, "%d.sol", n);
    FILE *outfile = fopen(out_filename, "w");
    for (int i = 0; i < n; i++) {
        fprintf(outfile, "%.6f\n", x[i]);
    }
    fclose(outfile);

    // Cleanup
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(x);
    free(x_new);

    return 0;
}