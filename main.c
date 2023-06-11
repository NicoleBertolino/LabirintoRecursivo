#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    int linhas, colunas;
    char opImpressao;

    // Inicializa a semente de geração de números aleatórios
    srand(time(NULL));

    // lendo o numero de linhas, colunas e a opcao de impressao
    scanf("%d %d\n", &linhas, &colunas);
    scanf("%c", &opImpressao);

    // aloca o labirinto e le suas informacoes da entrada
    Labirinto *labirinto = alocarLabirinto(&linhas, &colunas);
    leLabirinto(&labirinto);

    // funcao que encontra a saida mais rapida
    acharSaida(&labirinto);
    


    desalocarLabirinto(&labirinto);

    return 0;
}