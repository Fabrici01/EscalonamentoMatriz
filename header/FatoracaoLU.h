#ifndef FATORACAOLU_H
#define FATORACAOLU_H

float** calcularMatrizL(float** matrizU, int tamanho);

void resolverSistemaLU(float** matrizU,float** matrizL,float* termos, int tamanho);

#endif // FATORACAOLU_H