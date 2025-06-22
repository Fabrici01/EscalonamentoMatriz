#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "./header/GaussJacobi.h"

float maximoModulo(float vetor[], int tamanho) {
    float max = fabsf(vetor[0]);
    for (int i = 1; i < tamanho; i++) {
        float mod = fabsf(vetor[i]);
        if (mod > max) {
            max = mod;
        }
    }
    return max;
}

void validarSistema(float **A, float *B, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int linhaNula = 1;
        for (int j = 0; j < tamanho; j++) {
            if (A[i][j] != 0.0f) {
                linhaNula = 0;
                break;
            }
        }
        if (linhaNula) {
            if (B[i] != 0.0f) {
                printf("Linha %d e nula e B[%d] = %.2f -> sistema impossivel\n", i + 1, i + 1, B[i]);
                exit(EXIT_FAILURE);
            } else {
                printf("Linha %d e B[%d] sao nulos -> sistema indeterminado\n", i + 1, i + 1);
                exit(EXIT_FAILURE);
            }
        }
        if (A[i][i] == 0.0f) {
            printf("A[%d][%d] (diagonal principal) e zero -> divisao por zero\n", i + 1, i + 1);
            exit(EXIT_FAILURE);
        }
    }
}

float iteracaoGJ(float **A, float *B, int tamanho, float *xAnterior, float *xAtual){
    float *d = malloc(tamanho * sizeof(float));
    if (!d) {
        fprintf(stderr, "Erro de alocacao em iteracaoGJ\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamanho; i++) {
        xAtual[i] = B[i];
        for (int j = 0; j < tamanho; j++) {
            if (i != j) {
                xAtual[i] -= A[i][j] * xAnterior[j];
            }
        }
        xAtual[i] /= A[i][i];
        d[i] = fabsf(xAtual[i] - xAnterior[i]);
    }

    float erro = maximoModulo(d, tamanho) / maximoModulo(xAtual, tamanho);
    free(d);
    return erro;
}

void gaussJacobi(float **A, float *B, int tamanho, float E){
    validarSistema(A, B, tamanho);

    float *xAnterior = calloc(tamanho, sizeof(float));
    float *xAtual = malloc(tamanho * sizeof(float));
    if (!xAnterior || !xAtual) {
        fprintf(stderr, "Erro de alocacao em gaussJacobi\n");
        exit(EXIT_FAILURE);
    }

    clock_t inicio = clock();

    float erro;
    do {
        erro = iteracaoGJ(A, B, tamanho, xAnterior, xAtual);
        for (int i = 0; i < tamanho; i++) {
            xAnterior[i] = xAtual[i];
        }
    } while (erro > E);

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[Gauss-Jacobi] Tempo: %.9lf segundos\n", tempo);
    printf("Solucao:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("X%d = %.6f\n", i + 1, xAtual[i]);
    }

    free(xAnterior);
    free(xAtual);
}