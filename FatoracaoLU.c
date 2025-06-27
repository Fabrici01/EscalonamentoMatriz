#include <stdio.h>
#include <stdlib.h>
#include "./header/FatoracaoLU.h"

float** calcularMatrizL(float** matrizU, int tamanho){
    float** matrizL = (float**) malloc(tamanho*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        matrizL[x] = (float*) calloc(tamanho, sizeof(float));
        matrizL[x][x] = 1; //Diagonal principal igual a 1
    }

    //Eliminação de Gauss em matrizU
    float m=0.0,vetorTemp[tamanho];
    int i=0;
    for(int k=0;k<tamanho;k++){
        if(matrizU[k][k]==0){
            i = k+1;
            while(i<tamanho&&matrizU[i][k]==0)i++;
            if(i<tamanho){
                for(int x=0;x<tamanho;x++){
                    vetorTemp[x] = matrizU[k][x];
                    matrizU[k][x] = matrizU[i][x];
                    matrizU[i][x] = vetorTemp[x];
                }
            }else{
                printf("Matriz sem solucao definida!\n");
                exit(0);
            }
        }
        for(int l=k+1;l<tamanho;l++){
            m = matrizU[l][k]/matrizU[k][k];
            
            //Põe valor m em matrizL
            matrizL[l][k] = m;

            for(int x=k;x<tamanho;x++){
                matrizU[l][x] = matrizU[l][x] - (m * matrizU[k][x]);
            }
        }
    }//-----------------


    //Print Valores:
    printf("\nMatriz L:\n");
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            printf("%f ",matrizL[x][y]);
        }
        printf("\n");
    }

    printf("\nMatriz U:\n");
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            printf("%f ",matrizU[x][y]);
        }
        printf("\n");
    }

    return matrizL;
}

void resolverSistemaLU(float** matrizU,float** matrizL,float* termo, int tamanho){
    float total=0.0;
    
    //Substituição para achar Y
    for(int x=0;x<tamanho;x++){
        total=0.0;
        for(int y=0;y<x;y++){
            total += matrizL[x][y] * termo[y];
        }
        termo[x] = (termo[x]-total)/matrizL[x][x];
    }

    printf("\nValores Y:\n");
    for(int x=0;x<tamanho;x++){
        printf("Y%i = %f\n",x+1,termo[x]);
    }
    //-----------------

    //Substituição para achar X
    for(int x=tamanho-1;x>=0;x--){
        total=0.0;
        for(int y=tamanho-1;y>x;y--){
            total += matrizU[x][y] * termo[y];
        }
        termo[x] = (termo[x]-total)/matrizU[x][x];
    }

    printf("\nValores X:\n");
    for(int x=0;x<tamanho;x++){
        printf("X%i = %f\n",x+1,termo[x]);
    }
    //-----------------
}