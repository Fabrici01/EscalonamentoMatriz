#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

float iteracaoGJ(float **A, float *B, int tamanho, float *xAnterior, float *xAtual){
    float *d = (float *)malloc(tamanho * sizeof(float));
    if (d == NULL) {
        fprintf(stderr, "Erro de alocação de memória em iteracaoGJ\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++)
    {
        xAtual[i] = B[i];
        for (int j = 0; j < tamanho; j++)
        {
            if (i != j)
            {
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
    float *xAnterior = (float *)malloc(tamanho * sizeof(float));
    float *xAtual = (float *)malloc(tamanho * sizeof(float));
    if (!xAnterior || !xAtual) {
        fprintf(stderr, "Erro de alocação de memória em gaussJacobi\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        xAnterior[i] = 0.0f;
    }
    float erro;
    do {
        erro = iteracaoGJ(A, B, tamanho, xAnterior, xAtual);
        for (int i = 0; i < tamanho; i++) {
            xAnterior[i] = xAtual[i];
        }
    } while (erro > E);
    printf("\nSolucao:\n");
    for (int i = 0; i < tamanho; i++)
    {
        printf("X%d : %f\n", i+1, xAtual[i]);
    }
    free(xAnterior);
    free(xAtual);
}