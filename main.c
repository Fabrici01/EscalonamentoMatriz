#include <stdio.h>
#include <stdlib.h>

void lerMatriz(float** matriz,float *termos,int tamanho,FILE* arquivo){
    /*Ler Matriz dos Coeficientes*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            fscanf(arquivo,"%f",&matriz[x][y]);
        }
    }

    /*Ler Vetor dos Termos Independentes*/
    for(int x=0;x<tamanho;x++){
        fscanf(arquivo,"%f",&termos[x]);
    }
}

int main()
{
    int quantidade=0,tamanho=0;
    float e=0.0;

    FILE *arquivo = fopen("arquivo.txt", "r");
    fscanf(arquivo, "%i %i %f",&quantidade,&tamanho,&e);
    float termos[tamanho];
    float** matriz = (float**) malloc(tamanho*sizeof(float*));
    for(int x=0;x<tamanho;x++){
        matriz[x] = (float*) malloc(tamanho*sizeof(float));
    }

    lerMatriz(matriz,termos,tamanho,arquivo);

    /**Print de Teste*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            printf("%.3f ",matriz[x][y]);
        }
        printf("= %f\n",termos[x]);
    }

    return 0;
}
