#ifndef LABIRINTO_H
#define LABIRINTO_H

typedef struct {
    int linhas, colunas;
    char **maze;
} Labirinto;

typedef struct {
    int x, y;
} Posicao;

typedef struct {
    Posicao *posicao;
    int compDoPercurso;
} Percurso;

Labirinto* alocarLabirinto(int* linhas, int*colunas);
void desalocarLabirinto(Labirinto** labirinto);
void leLabirinto(Labirinto** labirinto);
void imprimePercursoNoLabirinto(Labirinto **labirinto, char opImpressao, Percurso **percurso);
void imprimeCoordenadas();
void acharSaida(Labirinto** labirinto, char opImpressao);
void encontraRato(Labirinto** labirinto, Posicao** pAtual);
void encontraCaminho(Labirinto **labirinto, Posicao **pPossivel, Posicao **pAtual);
void movimentaRato(Labirinto **labirinto, Posicao **pPossivel, Posicao **pAtual, Percurso **percurso);
int contEspaco(Labirinto **labirinto);
//int andaRato(Labirinto **labirinto, Posicao *pAtual, Posicao **pPossivel, Percurso **percurso, char opImpressao);
void andaRato(Labirinto **labirinto, Posicao **pAtual, Posicao **pPossivel, int *retorno, Percurso **percurso, int opImpressao);
#endif 