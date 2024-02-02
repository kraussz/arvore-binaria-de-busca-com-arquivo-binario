#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 51

#ifndef curso_h
#define curso_h

// Definição da estrutura para armazenar as informações do comando
typedef struct {
    int position;
    char name[51];
    char category;
} ComandoData;

// Estrutura do nó da árvore binária
typedef struct TreeNode {
    ComandoData data;
    int left;
    int right;
} Arvore;


void escreverArvore(FILE* fb, Arvore* r, int pos);
Arvore* lerArvore(FILE* fb, int pos);
void inserir_em_lote(FILE *fb,FILE* fr);
int buscarProduto_pos(FILE* fb,int cod, int pos);
void inserirProduto(FILE *fb,Arvore * new_node);
void inserir_semNosLivres(FILE* fb,Arvore* root_new,int pos);
void inserir_comNosLivres(FILE *fb,Arvore* new_node,int pos);
void imprimir_inOrdem(FILE *fb);
void imprimir_inOrdem_rec(FILE* fb,int pos);
void freeTree(Arvore* root);
void freeTreeRec(Arvore* root);
void ler_arq_texto(FILE* fb,FILE *fr);
void cadastrarCurso(FILE* fb);

#endif