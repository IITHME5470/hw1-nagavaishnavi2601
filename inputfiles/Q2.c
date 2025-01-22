#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dot_prod(double *a, double *b, int n) {
    double dp = 0;
    for (int i = 0; i < n; i++) {
        dp += a[i] * b[i];
    }
    return dp;
}

double *mat_dot_prod(double **A, double *x, int n) {
    double *y = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        y[i] = dot_prod(A[i], x, n);
    }
    return y;
}

double sum_vec(double *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
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

    char m_file[100], v_file[100];
    sprintf(m_file, "mat_%06d.in", n);

    fptr = fopen(m_file, "r");
    if (!fptr) {
        perror("Error opening matrix file");
        return EXIT_FAILURE;
    }

    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fptr, "%lf,", &A[i][j]);
        }
    }
    fclose(fptr);

    double *V = (double *)malloc(n * sizeof(double));
    int vn = 1;

    while (1) {
        sprintf(v_file, "vec_%06d_%06d.in", n, vn);
        vn++;
        fptr = fopen(v_file, "r");
        if (!fptr) {
            break;
        }

        for (int i = 0; i < n; i++) {
            fscanf(fptr, "%lf,", &V[i]);
        }
        fclose(fptr);

        double *AV = mat_dot_prod(A, V, n);
        int idx = 0;
        while (idx < n && fabs(V[idx]) < 1e-10) idx++;
        if (idx == n) {
            printf("%s : Not an Eigenvector\n", v_file);
            continue;
        }
                
        double v = dot_prod(A[idx],V,n) / V[idx];

        double diff_sum = 0;
        for (int i = 0; i < n; i++) {
            diff_sum += fabs(AV[i] - v * V[i]);
        }
        free(AV);

        if (diff_sum <= 1e-6) {
            fptr = fopen(v_file, "a");
            if (fptr) {
                fprintf(fptr, "\n%lf", v);
                fclose(fptr);
            }
            printf("%s : Yes : %lf\n", v_file, v);
        } else {
            printf("%s : Not an Eigenvector\n", v_file);
        }
    }

    free(V);
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}
