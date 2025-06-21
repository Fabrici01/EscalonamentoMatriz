#include <stdio.h>
#include <stdlib.h>
#include "./header/EliminacaoGauss.h"

void lerMatriz(float** matriz,int tamanho,FILE* arquivo){
    /*Ler Matriz dos Coeficientes*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            fscanf(arquivo,"%f",&matriz[x][y]);
        }
    }
}

void lerTermos(float *termos,int tamanho,FILE* arquivo){
    /*Ler Vetor dos Termos Independentes*/
    for(int x=0;x<tamanho;x++){
        fscanf(arquivo,"%f",&termos[x]);
    }
}

void freeMatriz(float** matriz,int tamanho){
    for(int x=0;x<tamanho;x++){
        free(matriz[x]);
    }
    free(matriz);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("ERRO: excesso de argumentos!");
        exit(1);
    }
    
    int quantidade=0,tamanho=0;
    float e=0.0;

    FILE *arquivo = fopen(argv[1], "r");
    fscanf(arquivo, "%i %i %f",&quantidade,&tamanho,&e);
    float termos[tamanho];
    float matrizFixa[tamanho][tamanho], termosFixos[tamanho];
    
    float** matrizL = (float**) malloc(tamanho*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        matrizL[x] = (float*) malloc(tamanho*sizeof(float));
    }
    
    float** matriz = (float**) malloc(tamanho*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        matriz[x] = (float*) malloc(tamanho*sizeof(float));
    }

    lerMatriz(matriz,tamanho,arquivo);
    lerTermos(termos,tamanho,arquivo);

    //Clonando valores para a matriz fixa
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            matrizFixa[x][y] = matriz[x][y];
        }
        termosFixos[x] = termos[x];
    }

    /**Print de Teste*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            printf("%.3f ",matriz[x][y]);
        }
        printf("= %f\n",termos[x]);
    }

    resolverEliminacaoGauss(matriz,termos,tamanho);

    printf("\nMatriz Escalonada:\n");
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            printf("%.3f ",matriz[x][y]);
        }
        printf("= %f\n",termos[x]);
    }


    freeMatriz(matriz,tamanho);
    return 0;
}
