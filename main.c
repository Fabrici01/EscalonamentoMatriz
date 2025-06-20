#include <stdio.h>
#include <stdlib.h>

int main()
{
    int quantidade=0,tamanho=0;
    float e=0.0;

    FILE *arquivo = fopen("arquivo.txt", "r");
    fscanf(arquivo, "%i %i %f",&quantidade,&tamanho,&e);
    float matriz[tamanho][tamanho],valores[tamanho];

    /*Ler Matriz dos Coeficientes*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            fscanf(arquivo,"%f",&matriz[x][y]);
        }
    }

    /*Ler Vetor dos Termos Independentes*/
    for(int x=0;x<tamanho;x++){
        fscanf(arquivo,"%f",&valores[x]);
    }

    /**Print de Teste*/
    for(int x=0;x<tamanho;x++){
        for(int y=0;y<tamanho;y++){
            printf("%.3f ",matriz[x][y]);
        }
        printf("= %f\n",valores[x]);
    }


    return 0;
}
