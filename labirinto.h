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
void imprimePercursoNoLabirinto(Labirinto** labirinto);
void imprimeCoordenadas();
void acharSaida(Labirinto** labirinto);
void encontraRato(Labirinto** labirinto, Posicao** pAtual);
void encontraCaminho(Labirinto **labirinto, Posicao **pPossivel, Posicao *pAtual);
void movimentaRato(Labirinto **labirinto, Posicao **pPossivel, Posicao *pAtual/* ,Percurso **percurso*/);
int contEspaco(Labirinto **labirinto);

#endif 