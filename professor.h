#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 51

#ifndef professor_h
#define professor_h

// Definição da estrutura para armazenar as informações do comando
typedef struct {
    int code;
    char name[51];
} ProfessorData;

// Estrutura do nó da árvore binária
typedef struct {
    ProfessorData prof;
    int esq;
    int dir;
} Arvore_Professor;


void escreverArvore_Professor(FILE* fb, Arvore_Professor* r, int pos);
Arvore_Professor* lerArvore_Professor(FILE* fb, int pos);
void inserir_em_lote_prof(FILE *fb,FILE* fr);
int buscarProfessor_pos(FILE* fb,int cod, int pos);
void inserirProfessor(FILE *fb,Arvore_Professor *new_node);
void inserir_semNosLivresProf(FILE* fb,Arvore_Professor* root_new,int pos);
void inserir_comNosLivresProf(FILE *fb,Arvore_Professor* new_node,int pos);
void imprimir_inOrdemP(FILE *fb);
void imprimir_inOrdem_recP(FILE* fb,int pos);
void freeTreeP(Arvore_Professor* root);
void freeTreeRecP(Arvore_Professor* root);
void cadastrarProfessor(FILE* fb);

#endif