#include <stdio.h>
#include <stdlib.h>
#include "./header/EliminacaoGauss.h"

void resolverEliminacaoGauss(float** matriz, float* termo, int tamanho){
    float m=0.0,vetorTemp[tamanho],termoTemp=0.0,resultado[tamanho];
    int indiceMaior=0;

    //Eliminação de Gauss em matrizU
    for(int k=0;k<tamanho;k++){
        indiceMaior = k;
        for(int i=k;i<tamanho;i++){
            if(matriz[i][k]>matriz[indiceMaior][k]) indiceMaior = i;
        }
        if(matriz[indiceMaior][k]==0){
            printf("Matriz sem solucao definida!\n");
            exit(1);
        }
        for(int x=0;x<tamanho;x++){
            vetorTemp[x] = matriz[k][x];
            matriz[k][x] = matriz[indiceMaior][x];
            matriz[indiceMaior][x] = vetorTemp[x];
        }
            termoTemp = termo[k];
            termo[k] = termo[indiceMaior];
            termo[indiceMaior] = termoTemp;
        for(int l=k+1;l<tamanho;l++){
            m = matriz[l][k]/matriz[k][k];
            for(int x=k;x<tamanho;x++){
                matriz[l][x] = matriz[l][x] - (m * matriz[k][x]);
            }
            termo[l] = termo[l] - (m * termo[k]);
        }
    }//-------------------

    //Substituição
    float total=0.0;
    for(int x=tamanho-1;x>=0;x--){
        total=0.0;
        for(int y=tamanho-1;y>x;y--){
            total += matriz[x][y] * resultado[y];
        }
        resultado[x] = (termo[x]-total)/matriz[x][x];
    }//-----------

    printf("\nSolucao:\n");
    for(int x=0;x<tamanho;x++){
        printf("X%i = %f\n",x+1,resultado[x]);
    }
}