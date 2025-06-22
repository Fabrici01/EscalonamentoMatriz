#ifndef GAUSSJACOBI_H
#define GAUSSJACOBI_H

float maximoModulo(float vetor[], int tamanho);
void validarSistema(float **A, float *B, int tamanho);
float iteracaoGJ(float **A, float *B, int tamanho, float *xAnterior, float *xAtual);
void gaussJacobi(float **A, float *B, int tamanho, float E);

#endif //GAUSSJACOBI_H