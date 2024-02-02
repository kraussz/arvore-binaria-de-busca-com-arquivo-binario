#ifndef ARVORE_H
#define ARVORE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int posCabeca;  // Posição da cabeça/raiz
    int posTopo;    // Próxima posição disponível
    int posLivre;   // Lista de nós livres
} Cabecalho;


//FILE* initializeBinaryFile(char *arqName);
FILE* initializeBinaryFile(char* file_name);
void escreverCabecalho(FILE* fb, Cabecalho* cab);
Cabecalho* lerCabecalho(FILE* fb);
void inicializarArvore(FILE* fb);
int vaziaArvore(Cabecalho* cab);

#endif  // ARVORE_H
