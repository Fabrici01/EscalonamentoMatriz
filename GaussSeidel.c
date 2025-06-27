#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./header/GaussJacobi.h"
#include "./header/GaussSeidel.h"

float iteracaoGS(float **A, float *B, int tamanho, float *x) {
    float *d = malloc(tamanho * sizeof(float));
    if (!d) {
        fprintf(stderr, "Erro de alocacao em iteracaoGS\n");
        exit(EXIT_FAILURE);
    }

    float xi;
    for (int i = 0; i < tamanho; i++) {
        xi = B[i];
        for (int j = 0; j < tamanho; j++) {
            if (i != j) {
                xi -= A[i][j] * x[j];
            }
        }
        float novo = xi / A[i][i];
        d[i] = fabsf(novo - x[i]);
        x[i] = novo;
    }

    float erro = maximoModulo(d, tamanho) / maximoModulo(x, tamanho);
    free(d);
    return erro;
}

void gaussSeidel(float **A, float *B, int tamanho, float E){
    float *x = calloc(tamanho, sizeof(float));
    if (!x) {
        fprintf(stderr, "Erro de alocacao em gaussSeidel\n");
        exit(EXIT_FAILURE);
    }

    float erro;
    do {
        erro = iteracaoGS(A, B, tamanho, x);
    } while (erro > E);

    printf("Solucao:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("X%d = %.6f\n", i + 1, x[i]);
    }

    free(x);
}
