#include <stdio.h>
#include <stdlib.h>

void print_to_file(int n, double **A, int format_flag) {
    char file_n[100];
    sprintf(file_n, "array_%06d_%s.out", n, format_flag == 0 ? "asc" : "bin");

    FILE *fptr = fopen(file_n, "w+");
    if (!fptr) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    if (format_flag == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(fptr, "%.15lf ", A[i][j]);
            }
            fprintf(fptr, "\n");
        }
    } else {
        for (int i = 0; i < n; i++) {
            fwrite(A[i], sizeof(double), n, fptr);
        }
    }

    fclose(fptr);
}

int main() {
    int n;
    FILE *fptr = fopen("input.in", "r");
    if (!fptr) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    fscanf(fptr, "%d", &n);
    fclose(fptr);

    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
        }
    }

    print_to_file(n, A, 0);
    print_to_file(n, A, 1);

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}
