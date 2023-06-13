#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Labirinto *alocarLabirinto(int *linhas, int *colunas)
{
    Labirinto *labirinto = (Labirinto *)malloc(sizeof(Labirinto));
    if (labirinto == NULL)
    {
        printf("Erro na alocação de memória em alocarLabirinto().\n");
        return labirinto;
    }
    labirinto->linhas = *linhas;
    labirinto->colunas = *colunas;
    labirinto->maze = (char **)malloc(*linhas * sizeof(char *));
    for (int i = 0; i < *linhas; i++)
        labirinto->maze[i] = (char *)malloc(*colunas * sizeof(char));
    return labirinto;
}

void desalocarLabirinto(Labirinto **labirinto)
{
    for (int i = 0; i < (*labirinto)->linhas; i++)
    {
        free((*labirinto)->maze[i]);
    }
    free((*labirinto)->maze);
    free(*labirinto);
}

void leLabirinto(Labirinto **labirinto)
{
    getchar();
    for (int i = 0; i < (*labirinto)->linhas; i++)
    {
        for (int j = 0; j < (*labirinto)->colunas; j++)
            scanf("%c", &(*labirinto)->maze[i][j]);
        scanf(" ");
    }
}

void imprimePercursoNoLabirinto(Labirinto **labirinto, char opImpressao, Percurso **percurso)
{
    if (opImpressao == 'p')
    {
        for (int i = 0; i < (*labirinto)->linhas; i++)
        {
            for (int j = 0; j < (*labirinto)->colunas; j++)
                printf("%c", (*labirinto)->maze[i][j]);
            printf("\n");
        }
    }
    // imprimindo caminho por coordenadas
    else if (opImpressao == 'c')
    {
        int comprimento = (*percurso)->compDoPercurso;
        printf("%d\n", comprimento);

        int j = 0;
        while (j < comprimento)
        {
            printf("%d, %d\n", (*percurso)->posicao[j].x, (*percurso)->posicao[j].y);
            j++;
        }
    }
}

void imprimeCoordenadas()
{
    printf("entrou");
}

void acharSaida(Labirinto **Labirinto, char opImpressao)
{
    Posicao *pPossivel;
    Posicao *pAtual;
    Percurso *percurso;

    int TAM = contEspaco(Labirinto);
    // printf("EspacoVazio: %d", TAM);

    percurso = (Percurso *)malloc(sizeof(Percurso));
    percurso->posicao = malloc(TAM * sizeof(Posicao));
    percurso->compDoPercurso = 0;
    if (percurso == NULL)
    {
        printf("Erro na alocação movimentaRato()");
    }

    encontraRato(Labirinto, &pAtual);
    encontraCaminho(Labirinto, &pPossivel, pAtual);
    movimentaRato(Labirinto, &pPossivel, pAtual, &percurso);
    //  imprimePercursoNoLabirinto(Labirinto, opImpressao, &percurso);
    sleep(2);
    // system("clear");

    encontraRato(Labirinto, &pAtual);
    encontraCaminho(Labirinto, &pPossivel, pAtual);
    movimentaRato(Labirinto, &pPossivel, pAtual, &percurso);
    // imprimePercursoNoLabirinto(Labirinto, opImpressao, &percurso);
    sleep(2);
    // system("clear");

    encontraRato(Labirinto, &pAtual);
    encontraCaminho(Labirinto, &pPossivel, pAtual);
    movimentaRato(Labirinto, &pPossivel, pAtual, &percurso);
    imprimePercursoNoLabirinto(Labirinto, opImpressao, &percurso);
    // sleep(2);
    // system("clear");

    // pAtual = encontraRato(Labirinto);
    // encontraCaminho(Labirinto, &pPossivel, pAtual);
    // movimentaRato(Labirinto, pAtual, pPossivel, &percurso);
    // imprimePercursoNoLabirinto(Labirinto);
    // free(pAtual);
    // system("clear");

    // pAtual = encontraRato(Labirinto);
    // encontraCaminho(Labirinto, &pPossivel, pAtual);
    // movimentaRato(Labirinto, pAtual, pPossivel, &percurso);
    // imprimePercursoNoLabirinto(Labirinto);
    // free(pAtual);

    // printf("Comprimento: %d\n", percurso->compDoPercurso);
    // for (int i = 0; i < percurso->compDoPercurso; i++)
    //     printf("%d, %d", percurso[i].posicao->x, percurso[i].posicao->y);
    free((*percurso).posicao);
    free(percurso);
}

void encontraRato(Labirinto **labirinto, Posicao **pAtual)
{
    *pAtual = malloc(sizeof(Posicao));
    if (pAtual == NULL)
    {
        printf("Erro na alocação de memória em encontraRato().\n");
    }

    for (int x = 0; x < (*labirinto)->linhas; x++)
    {
        for (int y = 0; y < (*labirinto)->colunas; y++)
        {
            if ((*labirinto)->maze[x][y] == 'M')
            {
                (*pAtual)->x = x;
                (*pAtual)->y = y;
            }
        }
    }
}

void encontraCaminho(Labirinto **labirinto, Posicao **pPossivel, Posicao *pAtual)
{
    *pPossivel = (Posicao *)malloc(4 * sizeof(Posicao));

    if (*pPossivel == NULL)
    {
        printf("Erro na alocação de memória em encontraCaminho().\n");
        return;
    }

    // verifica caminho para a direita (y + 1]) e -1 para parede
    int paraDireita = (pAtual->y < (*labirinto)->colunas && (*labirinto)->maze[pAtual->x][pAtual->y + 1] != '*');
    (*pPossivel)[0].x = paraDireita ? pAtual->x : -1;
    (*pPossivel)[0].y = paraDireita ? pAtual->y + 1 : -1;

    // verifica caminho para a esquerda (y - 1) e -1 para parede
    int paraEsquerda = (pAtual->y > 0 && (*labirinto)->maze[pAtual->x][pAtual->y - 1] != '*');
    (*pPossivel)[2].x = paraEsquerda ? pAtual->x : -1;
    (*pPossivel)[2].y = paraEsquerda ? pAtual->y - 1 : -1;

    // verifica caminho para baixo (x + 1) e -1 para parede
    int paraBaixo = (pAtual->x < (*labirinto)->linhas && (*labirinto)->maze[pAtual->x + 1][pAtual->y] != '*');
    (*pPossivel)[1].x = paraBaixo ? pAtual->x + 1 : -1;
    (*pPossivel)[1].y = paraBaixo ? pAtual->y : -1;

    // verifica caminho para cima (x - 1) e -1 para parede
    int paraCima = (pAtual->x > 0 && (*labirinto)->maze[pAtual->x - 1][pAtual->y] != '*');
    (*pPossivel)[3].x = paraCima ? pAtual->x - 1 : -1;
    (*pPossivel)[3].y = paraCima ? pAtual->y : -1;
}

void movimentaRato(Labirinto **labirinto, Posicao **pPossivel, Posicao *pAtual, Percurso **percurso)
{
    int peso = 0;
    int index = 0;

    for (int i = 0; i < 4; i++)
    {
        if ((*pPossivel)[i].x != -1 && (*pPossivel)[i].y != -1)
        {
            int aux = (*pPossivel)[i].x + (*pPossivel)[i].y;

            if (peso < aux)
            {
                peso = (*pPossivel)[i].x + (*pPossivel)[i].y;
                index = i;
            }
        }
    }

    // Guarda a posição no vetor
    if ((*percurso)->compDoPercurso == 0)
    {
        (*percurso)->posicao[0].x = pAtual->x;
        (*percurso)->posicao[0].y = pAtual->y;
    }
    (*percurso)->posicao[(*percurso)->compDoPercurso].x = pAtual->x;
    (*percurso)->posicao[(*percurso)->compDoPercurso].y = pAtual->y;
    (*percurso)->compDoPercurso = (*percurso)->compDoPercurso + 1;

    // Altera a posição do Rato
    (*labirinto)->maze[pAtual->x][pAtual->y] = 'v';
    (*labirinto)->maze[(*pPossivel)[index].x][(*pPossivel)[index].y] = 'M';

    free(*pPossivel);
    free(pAtual);
}

int contEspaco(Labirinto **labirinto)
{
    int contador = 0;
    for (int x = 0; x < (*labirinto)->linhas; x++)
    {
        for (int y = 0; y < (*labirinto)->colunas; y++)
        {
            if ((*labirinto)->maze[x][y] == ' ')
                ++contador;
        }
    }
    return contador;
}

/*int MEtodoresult(int maxLinha, int maxColuna, int linhapAtual, int colunapAtual)//posicao atual do arato
{
    char result;
    if ((linhapAtual > maxLinha) || (linhapAtual < 0) || (colunapAtual > maxColuna) || (colunapAtual < 0))
    {
        result = false;
    }
    else if ((matriz[pLinhaAtua][pColunaAtual] == '*') || (matriz[pLinhaAtua][pColunaAtual] == 'v'))
    {
        result = false;
    }
    else if (matriz[pLinhaAtua][pColunaAtual] == pPossivel)
    {
        movimentaRato();
        result = encontraCaminho();
    }
    if (result == true)
    {
        printf(linhapAtual, colunapAtual);
        Metodoresult(linhapAtual, colunapAtual);
    }
    return result;
}*/