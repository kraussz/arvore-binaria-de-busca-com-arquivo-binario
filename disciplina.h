#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 51

#ifndef disciplina_h
#define disciplina_h

// Definição da estrutura para armazenar as informações do comando
typedef struct {
    int code;
    char name[51];
    int curso;
    int serie;
} DisciplineData;

// Estrutura do nó da árvore binária
typedef struct {
    DisciplineData disc;
    int esq;
    int dir;
} Arvore_Disciplina;


void escreverArvore_Disciplina(FILE* fb, Arvore_Disciplina* r, int pos);
Arvore_Disciplina* lerArvore_Disciplina(FILE* fb, int pos);
void inserir_em_lote_disc(FILE *fb,FILE* fr);
int buscarDisciplina_pos(FILE* fb,int cod, int pos);
void inserirDisciplina(FILE *fb,Arvore_Disciplina *new_node);
void inserir_semNosLivresDisc(FILE* fb,Arvore_Disciplina* root_new,int pos);
void inserir_comNosLivresDisc(FILE *fb,Arvore_Disciplina* new_node,int pos);
void imprimir_inOrdemD(FILE *fb);
void imprimir_inOrdem_recD(FILE* fb,int pos);
void freeTreeD(Arvore_Disciplina* root);
void freeTreeRecD(Arvore_Disciplina* root);
void cadastrarDisciplina(FILE* fb);

#endif