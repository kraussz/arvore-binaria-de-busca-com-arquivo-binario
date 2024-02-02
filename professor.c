#include "Arvore.h"
#include "professor.h"
#include "curso.h"

void escreverArvore_Professor(FILE* fb, Arvore_Professor* r, int pos) {
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore_Professor) * pos, SEEK_SET);
    fwrite(r, sizeof(Arvore_Professor), 1, fb);
}

Arvore_Professor* lerArvore_Professor(FILE* fb, int pos) {
    Arvore_Professor* root = (Arvore_Professor*)malloc(sizeof(Arvore_Professor));
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore_Professor) * pos, SEEK_SET);
    fread(root, sizeof(Arvore_Professor), 1, fb);
    return root;
}

void inserir_em_lote_prof(FILE* fb, FILE* arq) {
    Cabecalho* cab = lerCabecalho(fb);
    Arvore_Professor* root = (Arvore_Professor*)malloc(sizeof(Arvore_Professor));

    root->esq = root->dir = -1;

        fscanf(arq, "%d;%[^\n]", &root->prof.code, root->prof.name);
        printf("%d\n ", root->prof.code);
        printf("%s\n", root->prof.name);

        if (buscarProfessor_pos(fb, root->prof.code, cab->posCabeca) == -1)inserirProfessor(fb, root);
    

    free(cab);
    free(root);
}


int buscarProfessor_pos(FILE* fb, int cod, int pos) {
    if (pos == -1)
        return -1;
    else {
        Arvore_Professor* root = lerArvore_Professor(fb, pos);

        if (root->prof.code > cod)
            return buscarProfessor_pos(fb, cod, root->esq);
        else if (root->prof.code < cod)
            return buscarProfessor_pos(fb, cod, root->dir);
        free(root);
    }
    printf("ERRO... CODIGO JA EXISTENTE\n");
    return pos;
}

void inserirProfessor(FILE* fb, Arvore_Professor* new_node) {
    Cabecalho* cab = lerCabecalho(fb);

    if (cab->posLivre == -1)
        inserir_semNosLivresProf(fb, new_node, cab->posCabeca);
    else
        inserir_comNosLivresProf(fb, new_node, cab->posCabeca);

    free(cab);
}

void inserir_semNosLivresProf(FILE* fb, Arvore_Professor* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        if (vaziaArvore(cab))
            cab->posCabeca = 0;

        escreverArvore_Professor(fb, new_node, cab->posTopo);
        cab->posTopo++;
        escreverCabecalho(fb, cab);
    } else {
        Arvore_Professor* next_node = lerArvore_Professor(fb, pos);

        if (new_node->prof.code < next_node->prof.code) {
            if (next_node->esq == -1) {
                next_node->esq = cab->posTopo;
                escreverArvore_Professor(fb, next_node, pos);
                inserir_semNosLivresProf(fb, new_node, -1);
            } else {
                inserir_semNosLivresProf(fb, new_node, next_node->esq);
            }
        } else {
            if (new_node->prof.code > next_node->prof.code) {
                if (next_node->dir == -1) {
                    next_node->dir = cab->posTopo;
                    escreverArvore_Professor(fb, next_node, pos);
                    inserir_semNosLivresProf(fb, new_node, -1);
                } else {
                    inserir_semNosLivresProf(fb, new_node, next_node->dir);
                }
            }
        }
        free(next_node);
    }
    free(cab);
}

void inserir_comNosLivresProf(FILE* fb, Arvore_Professor* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        Arvore_Professor* free_node = lerArvore_Professor(fb, cab->posLivre);
        escreverArvore_Professor(fb, new_node, cab->posLivre);

        if (vaziaArvore(cab))
            cab->posCabeca = cab->posLivre;

        cab->posLivre = free_node->esq;
        escreverCabecalho(fb, cab);

        free(free_node);
    } else {
        Arvore_Professor* next_node = lerArvore_Professor(fb, pos);

        if (new_node->prof.code < next_node->prof.code) {
            if (next_node->esq == -1) {
                next_node->esq = cab->posLivre;
                escreverArvore_Professor(fb, next_node, pos);
                inserir_comNosLivresProf(fb, new_node, -1);
            } else {
                inserir_comNosLivresProf(fb, new_node, next_node->esq);
            }
        } else {
            if (new_node->prof.code > next_node->prof.code) {
                if (next_node->dir == -1) {
                    next_node->dir = cab->posLivre;
                    escreverArvore_Professor(fb, next_node, pos);
                    inserir_comNosLivresProf(fb, new_node, -1);
                } else {
                    inserir_comNosLivresProf(fb, new_node, next_node->dir);
                }
            }
        }
        free(next_node);
    }
    free(cab);
}

    //Descrição: Imprime a Interface e puxa a função recursiva de impressão da Arvore_Professor
    //Pré-Condição: Árvore já salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdemP(FILE* fb) {
    Cabecalho* cab = lerCabecalho(fb);

    printf("\n*Professor*\n");

   if(vaziaArvore(cab)) printf("\nNAO HA ProfessorS...\n");
    else {
        printf("\n%-11s%-55s\n", "numero", "nome");
    }
    imprimir_inOrdem_recP(fb,cab->posCabeca);

        free(cab);
   
}


    //Descrição: Monta a árvore a partir do arquivo e imprime-a do menor número ao maior
    //Pré-Condição: Árvore já existente salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdem_recP(FILE* fb,int pos){
        if(pos!=-1){
            Arvore_Professor* root=lerArvore_Professor(fb,pos);
            imprimir_inOrdem_recP(fb,root->esq);//imprime primeiro os elementos da esquerda
            printf("%-10d%-55s\n",root->prof.code,root->prof.name);//imprime a raiz
            imprimir_inOrdem_recP(fb,root->dir);//imprime então os elementos da direita
            free(root);
            
        }
    }


void cadastrarProfessor(FILE* fb){
        Cabecalho* cab=lerCabecalho(fb);
        Arvore_Professor* root=(Arvore_Professor*)malloc(sizeof(Arvore_Professor));

        root->esq=root->dir=-1;//no ainda nao possui filhos. inicializados como "null"

        printf("Digite o codigo do Professor:\n");
        scanf("%d%*c",&root->prof.code);

        

        //não permite inserir um codigo já existente
        if(buscarProfessor_pos(fb,root->prof.code,cab->posCabeca)==-1){

            printf("Digite o nome do Professor:\n");
            scanf("%[^\n]%*c",&root->prof.name);

            inserirProfessor(fb,root);//função recursiva de inserir no arquivo binario
            printf("\nProfessor INSERIDO COM SUCESSO...\n");
        }
        else printf("\nCODIGO EXISTENTE: NAO FOI POSSIVEL CONCLUIR O CADASTRO...\n");

        free(cab);
        free(root);
    }