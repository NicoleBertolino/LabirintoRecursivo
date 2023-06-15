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
    if (opImpressao == 'p' || opImpressao == 'P')
    {
        for (int i = 0; i < (*labirinto)->linhas; i++)
        {
            for (int j = 0; j < (*labirinto)->colunas; j++)
                printf("%c", (*labirinto)->maze[i][j]);
            printf("\n");
        }
    }
    // imprimindo caminho por coordenadas
    else if (opImpressao == 'c' || opImpressao == 'C')
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

void acharSaida(Labirinto **labirinto, char opImpressao)
{
    Posicao *pPossivel;
    Posicao *pAtual;
    Percurso *percurso;
    int retorno = 0;

    int TAM = contEspaco(labirinto);
    // printf("EspacoVazio: %d", TAM);

    percurso = (Percurso *)malloc(sizeof(Percurso));
    percurso->posicao = malloc(TAM * sizeof(Posicao));
    percurso->compDoPercurso = 0;
    if (percurso == NULL)
    {
        printf("Erro na alocação movimentaRato()");
    }
    encontraRato(labirinto, &pAtual);

    encontraCaminho(labirinto, &pPossivel, &pAtual);

    andaRato(labirinto, &pAtual, &pPossivel, &retorno, &percurso, opImpressao);

    if (retorno == 1)
    {
        imprimePercursoNoLabirinto(labirinto, opImpressao, &percurso);
    }
    else if (retorno == -1)
    {
        printf("\nEPIC FAIL!\n");
    }

    free((*percurso).posicao);
    free(percurso);
}

void andaRato(Labirinto **labirinto, Posicao **pAtual, Posicao **pPossivel, int *retorno, Percurso **percurso, int opImpressao)
{
    int confere = 0;
    for (int i = 0; i < 4; i++)
    {
        if ((*pPossivel)[i].x == -1 && (*pPossivel)[i].y == -1)
        {
            confere++;
        }
    }
    if (confere == 4)
    {
        *retorno = -1;
    }
    if ((*pAtual)->x == ((*labirinto)->linhas - 2) && (*pAtual)->y == ((*labirinto)->colunas - 2))
    {
        free(*pPossivel);
        free((*pAtual));
        *retorno = 1;
    }
    else if (*retorno != -1 && *retorno != 1)
    {
        free(*pPossivel);
        free((*pAtual));
        encontraRato(labirinto, pAtual);
        encontraCaminho(labirinto, pPossivel, pAtual);
        movimentaRato(labirinto, pPossivel, pAtual, percurso);
        imprimePercursoNoLabirinto(labirinto, opImpressao, percurso);
        sleep(1);
        andaRato(labirinto, pAtual, pPossivel, retorno, percurso, opImpressao);
    }
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

// PAI NESTE METODO
void encontraCaminho(Labirinto **labirinto, Posicao **pPossivel, Posicao **pAtual)
{
    *pPossivel = (Posicao *)malloc(4 * sizeof(Posicao));

    if (*pPossivel == NULL)
    {
        printf("Erro na alocação de memória em encontraCaminho().\n");
        return;
    }

    // verifica caminho para baixo (x + 1) e -1 para parede
    int paraBaixo = ((*pAtual)->x < (*labirinto)->linhas && ((*labirinto)->maze[(*pAtual)->x + 1][(*pAtual)->y] != '*'));
    (*pPossivel)[0].x = paraBaixo ? (*pAtual)->x + 1 : -1;
    (*pPossivel)[0].y = paraBaixo ? (*pAtual)->y : -1;

    // verifica caminho para cima (x - 1) e -1 para parede
    int paraCima = ((*pAtual)->x > 0 && ((*labirinto)->maze[(*pAtual)->x - 1][(*pAtual)->y] != '*'));
    (*pPossivel)[3].x = paraCima ? (*pAtual)->x - 1 : -1;
    (*pPossivel)[3].y = paraCima ? (*pAtual)->y : -1;

    // verifica caminho para a direita (y + 1]) e -1 para parede
    int paraDireita = ((*pAtual)->y < (*labirinto)->colunas && ((*labirinto)->maze[(*pAtual)->x][(*pAtual)->y + 1] != '*'));
    (*pPossivel)[1].x = paraDireita ? (*pAtual)->x : -1;
    (*pPossivel)[1].y = paraDireita ? (*pAtual)->y + 1 : -1;

    // verifica caminho para a esquerda (y - 1) e -1 para parede
    int paraEsquerda = ((*pAtual)->y > 0 && ((*labirinto)->maze[(*pAtual)->x][(*pAtual)->y - 1] != '*'));
    (*pPossivel)[2].x = paraEsquerda ? (*pAtual)->x : -1;
    (*pPossivel)[2].y = paraEsquerda ? (*pAtual)->y - 1 : -1;
}

int pegaMelhorCaminho(Labirinto **labirinto, Posicao **pPossivel)
{
    int index = -1, linha = -1, coluna = -1, peso = -1;

    for (int i = 0; i < 4; i++)
    {
        if ((*pPossivel)[i].x != -1 && (*pPossivel)[i].y != -1)
        {
            if ((*labirinto)->maze[(*pPossivel)[i].x][(*pPossivel)[i].y] != 'v')
            {
                int aux = (*pPossivel)[i].x + (*pPossivel)[i].y;
                linha = (*pPossivel)[i].x;
                coluna = (*pPossivel)[i].y;
                if (peso < aux && ((*labirinto)->maze[linha][coluna] != 'v'))
                {
                    peso = linha + coluna;
                    index = i;
                }
            }
        }
    }

    return index;
}

void movimentaRato(Labirinto **labirinto, Posicao **pPossivel, Posicao **pAtual, Percurso **percurso)
{
    int index = pegaMelhorCaminho(labirinto, pPossivel);

    // Guarda a posição no vetor
    if ((*percurso)->compDoPercurso == 0)
    {
        (*percurso)->posicao[0].x = (*pAtual)->x;
        (*percurso)->posicao[0].y = (*pAtual)->y;
    }

    if (index > -1)
    {
        (*percurso)->posicao[(*percurso)->compDoPercurso].x = (*pAtual)->x;
        (*percurso)->posicao[(*percurso)->compDoPercurso].y = (*pAtual)->y;
        (*percurso)->compDoPercurso = (*percurso)->compDoPercurso + 1;

        // Altera a posição do Rato
        (*labirinto)->maze[(*pAtual)->x][(*pAtual)->y] = 'v';
        (*labirinto)->maze[(*pPossivel)[index].x][(*pPossivel)[index].y] = 'M';
    }
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
