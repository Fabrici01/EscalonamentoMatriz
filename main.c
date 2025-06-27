#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./header/EliminacaoGauss.h"
#include "./header/FatoracaoLU.h"
#include "./header/GaussJacobi.h"
#include "./header/GaussSeidel.h"

void lerMatriz(float** matriz,int tamanho,FILE* arquivo){
    /*Ler Matriz dos Coeficientes*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            fscanf(arquivo,"%f",&matriz[x][y]);
        }
    }
}

void lerTermos(float **termos,int tamanho, int quantidade, FILE* arquivo){
    /*Ler Matriz dos Termos Independentes*/
    for (int i = 0; i < quantidade; i++)
    {
        for(int x=0;x<tamanho;x++){
            fscanf(arquivo,"%f",&termos[i][x]);
        }
    }
}

void freeMatriz(float** matriz,int tamanho){
    for(int x=0;x<tamanho;x++){
        free(matriz[x]);
    }
    free(matriz);
}

int main(int argc, char const *argv[]){
    if (argc != 2){
        printf("ERRO: excesso ou falta de argumentos!\n");
        exit(1);
    }
    
    int quantidade=0,tamanho=0;
    float e=0.0;

    FILE *arquivo = fopen(argv[1], "r");
    fscanf(arquivo, "%i %i %f",&quantidade,&tamanho,&e);

    float** matriz = (float**) malloc(tamanho*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        matriz[x] = (float*) malloc(tamanho*sizeof(float));
    }
    float** matrizFixa = (float**) malloc(tamanho*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        matrizFixa[x] = (float*) malloc(tamanho*sizeof(float));
    }
    if (!matriz||!matrizFixa)
    {
        printf("Erro na alocacao da matriz\n");
    }
    
    float **termos = (float**) malloc(quantidade*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        termos[x] = (float*) malloc(tamanho*sizeof(float));
    }
    float **termosFixos = (float**) malloc(quantidade*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        termosFixos[x] = (float*) malloc(tamanho*sizeof(float));
    }
    if (!termos||!termosFixos)
    {
        printf("Erro na alocacao dos termos\n");
    }

    lerMatriz(matriz,tamanho,arquivo);
    lerTermos(termos,tamanho, quantidade,arquivo);
    fclose(arquivo);

    float **matrizL;

    //Clonando valores para a matriz fixa
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            matrizFixa[x][y] = matriz[x][y];
        }
        for (int i = 0; i < quantidade; i++)
        {
            termosFixos[x][i] = termos[x][i];
        }
    }

    /**Print de Teste*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            printf("%.3f ",matriz[x][y]);
        }
        for (int i = 0; i < quantidade; i++)
        {
            printf("= %f\t",termos[x][i]);
        }
        printf("\n");
    }


    clock_t inicio, fim;
    double tempo;
    printf("Eliminacao de Gauss\n");
    
    inicio = clock();
    for (int i = 0; i < quantidade; i++)
    {
        printf("Sistema %d\n", i+1);
        resolverEliminacaoGauss(matriz, termos[i], tamanho);
        for(int x=0;x<tamanho;x++){
            for(int y=0;y<tamanho;y++){
                matriz[x][y] = matrizFixa[x][y];
            }
            termosFixos[i][x] = termosFixos[i][x];
        }
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo: %f\n",tempo);

    inicio = clock();
    matrizL = calcularMatrizL(matriz,tamanho);
    printf("Fatoracao LU\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("Sistema %d\n", i+1);
        resolverSistemaLU(matriz, matrizL, termos[i], tamanho);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo: %f\n",tempo);
    
    inicio = clock();
    printf("Gauss-Jacobi\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("Sistema %d\n", i+1);
        gaussJacobi(matrizFixa, termosFixos[i], tamanho, e);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo: %f\n",tempo);

    inicio = clock();
    printf("Gauss-Seidel\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("Sistema %d\n", i+1);
        gaussSeidel(matrizFixa, termosFixos[i], tamanho, e);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo: %f\n",tempo);



    freeMatriz(matriz,tamanho);
    freeMatriz(matrizL,tamanho);
    freeMatriz(termos, quantidade);
    return 0;
}
