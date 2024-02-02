#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 51

#ifndef Matricula_h
#define Matricula_h

// Definição da estrutura para armazenar as informações do comando
typedef struct {
    int tracker;
    int code;
    int ano;
    int codprof;
} MatriculaData;

// Estrutura do nó da árvore binária
typedef struct {
    MatriculaData Mat;
    int esq;
    int dir;
} Arvore_Matricula;

typedef struct no{
        int cod;//código do produto
        int h_node;//altura do nó
        struct no* prox;
    }Lista;



void escreverArvore_Matricula(FILE* fb, Arvore_Matricula* r, int pos);
Arvore_Matricula* lerArvore_Matricula(FILE* fb, int pos);
void inserir_em_lote_Mat(FILE *fb,FILE* fr);
int buscarMatricula_pos(FILE* fb,int cod, int pos);
void inserirMatricula(FILE *fb,Arvore_Matricula *new_node);
void inserir_semNosLivresMat(FILE* fb, Arvore_Matricula* new_node, int pos);
void inserir_comNosLivresMat(FILE *fb,Arvore_Matricula* new_node,int pos);
void imprimir_inOrdemM(FILE *fb);
void imprimir_inOrdem_recM(FILE* fb,int pos);
void cadastrarMatricula(FILE* fb);
 void remover_em_lote(FILE *fb,FILE *fr);
 int removerNo(FILE *fb,int pos,int code);
int maximo(FILE* fb,int pos);
int minimo(FILE* fb,int pos);
 void trocar_info(FILE* fb,int pos_dest,int pos_source);
 int inserirArvore_bin(FILE* fb, Arvore_Matricula* root);
 int inserirArvore(FILE* fb, Arvore_Matricula* new_root, int pos);
 void remover_manual(FILE* fb);
 void imprimir_nosLivres(FILE *fb,int pos);
 void imprimir_listaLivres(FILE *fb);
 int altura_arvore(FILE* fb,int pos);
 void imprimir_arvore(FILE* fb);
 Lista* percorrer_arvore(FILE* fb,Lista* l,int pos,int h_node);
 void espaco(int altura_arvore,int altura_no);
 void liberar_lista(Lista *l);
#endif