#include <stdio.h>
#include <stdlib.h>
#include "./header/EliminacaoGauss.h"

void resolverEliminacaoGauss(float** matriz, float* termo, int tamanho){
    float m=0.0,vetorTemp[tamanho],termoTemp=0.0,resultado[tamanho];
    int i=0;
    for(int k=0;k<tamanho;k++){
        if(matriz[k][k]==0){
            i = k+1;
            while(i<tamanho&&matriz[i][k]==0)i++;
            if(i<tamanho){
                for(int x=0;x<tamanho;x++){
                    vetorTemp[x] = matriz[k][x];
                    matriz[k][x] = matriz[i][x];
                    matriz[i][x] = vetorTemp[x];
                }
                termoTemp = termo[k];
                termo[k] = termo[i];
                termo[i] = termoTemp;
            }else{
                printf("Matriz sem solucao definida!\n");
                exit(0);
            }
        }
        for(int l=k+1;l<tamanho;l++){
            m = matriz[l][k]/matriz[k][k];
            for(int x=k;x<tamanho;x++){
                matriz[l][x] = matriz[l][x] - (m * matriz[k][x]);
            }
            termo[l] = termo[l] - (m * termo[k]);
        }
    }

    float total=0.0;
    for(int x=tamanho-1;x>=0;x--){
        total=0.0;
        for(int y=tamanho-1;y>x;y--){
            total += matriz[x][y] * resultado[y];
        }
        resultado[x] = (termo[x]-total)/matriz[x][x];
    }

    printf("\nSolucao:\n");
    for(int x=0;x<tamanho;x++){
        printf("X%i = %f\n",x+1,resultado[x]);
    }
}