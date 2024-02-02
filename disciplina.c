#include "Arvore.h"
#include "disciplina.h"
#include "curso.h"

void escreverArvore_Disciplina(FILE* fb, Arvore_Disciplina* r, int pos) {
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore_Disciplina) * pos, SEEK_SET);
    fwrite(r, sizeof(Arvore_Disciplina), 1, fb);
}

Arvore_Disciplina* lerArvore_Disciplina(FILE* fb, int pos) {
    Arvore_Disciplina* root = (Arvore_Disciplina*)malloc(sizeof(Arvore_Disciplina));
    fseek(fb, sizeof(Cabecalho) + sizeof(Arvore_Disciplina) * pos, SEEK_SET);
    fread(root, sizeof(Arvore_Disciplina), 1, fb);
    return root;
}

void inserir_em_lote_disc(FILE* fb, FILE* arq) {
    Cabecalho* cab = lerCabecalho(fb);
    Arvore_Disciplina* root = (Arvore_Disciplina*)malloc(sizeof(Arvore_Disciplina));

    root->esq = root->dir = -1;

        fscanf(arq, "%d;%[^;]%*c%d%*c%d\n", &root->disc.code, root->disc.name, &root->disc.curso, &root->disc.serie);
        printf("%d ", root->disc.code);
        printf("%s ", root->disc.name);
        printf("%d ", root->disc.curso);
        printf("%d\n", root->disc.serie);

        if (buscarDisciplina_pos(fb, root->disc.code, cab->posCabeca) == -1)inserirDisciplina(fb, root);
    

    free(cab);
    free(root);
}


int buscarDisciplina_pos(FILE* fb, int cod, int pos) {
    if (pos == -1)
        return -1;
    else {
        Arvore_Disciplina* root = lerArvore_Disciplina(fb, pos);

        if (root->disc.code > cod)
            return buscarDisciplina_pos(fb, cod, root->esq);
        else if (root->disc.code < cod)
            return buscarDisciplina_pos(fb, cod, root->dir);
        free(root);
    }
    printf("ERRO... CODIGO JA EXISTENTE\n");
    return pos;
}

void inserirDisciplina(FILE* fb, Arvore_Disciplina* new_node) {
    Cabecalho* cab = lerCabecalho(fb);

    if (cab->posLivre == -1)
        inserir_semNosLivresDisc(fb, new_node, cab->posCabeca);
    else
        inserir_comNosLivresDisc(fb, new_node, cab->posCabeca);

    free(cab);
}

void inserir_semNosLivresDisc(FILE* fb, Arvore_Disciplina* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        if (vaziaArvore(cab))
            cab->posCabeca = 0;

        escreverArvore_Disciplina(fb, new_node, cab->posTopo);
        cab->posTopo++;
        escreverCabecalho(fb, cab);
    } else {
        Arvore_Disciplina* next_node = lerArvore_Disciplina(fb, pos);

        if (new_node->disc.code < next_node->disc.code) {
            if (next_node->esq == -1) {
                next_node->esq = cab->posTopo;
                escreverArvore_Disciplina(fb, next_node, pos);
                inserir_semNosLivresDisc(fb, new_node, -1);
            } else {
                inserir_semNosLivresDisc(fb, new_node, next_node->esq);
            }
        } else {
            if (new_node->disc.code > next_node->disc.code) {
                if (next_node->dir == -1) {
                    next_node->dir = cab->posTopo;
                    escreverArvore_Disciplina(fb, next_node, pos);
                    inserir_semNosLivresDisc(fb, new_node, -1);
                } else {
                    inserir_semNosLivresDisc(fb, new_node, next_node->dir);
                }
            }
        }
        free(next_node);
    }
    free(cab);
}

void inserir_comNosLivresDisc(FILE* fb, Arvore_Disciplina* new_node, int pos) {
    Cabecalho* cab = lerCabecalho(fb);

    if (pos == -1) {
        Arvore_Disciplina* free_node = lerArvore_Disciplina(fb, cab->posLivre);
        escreverArvore_Disciplina(fb, new_node, cab->posLivre);

        if (vaziaArvore(cab))
            cab->posCabeca = cab->posLivre;

        cab->posLivre = free_node->esq;
        escreverCabecalho(fb, cab);

        free(free_node);
    } else {
        Arvore_Disciplina* next_node = lerArvore_Disciplina(fb, pos);

        if (new_node->disc.code < next_node->disc.code) {
            if (next_node->esq == -1) {
                next_node->esq = cab->posLivre;
                escreverArvore_Disciplina(fb, next_node, pos);
                inserir_comNosLivresDisc(fb, new_node, -1);
            } else {
                inserir_comNosLivresDisc(fb, new_node, next_node->esq);
            }
        } else {
            if (new_node->disc.code > next_node->disc.code) {
                if (next_node->dir == -1) {
                    next_node->dir = cab->posLivre;
                    escreverArvore_Disciplina(fb, next_node, pos);
                    inserir_comNosLivresDisc(fb, new_node, -1);
                } else {
                    inserir_comNosLivresDisc(fb, new_node, next_node->dir);
                }
            }
        }
        free(next_node);
    }
    free(cab);
}

    //Descrição: Imprime a Interface e puxa a função recursiva de impressão da Arvore_Disciplina
    //Pré-Condição: Árvore já salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdemD(FILE* fb) {
    Cabecalho* cab = lerCabecalho(fb);

    printf("\n*Disciplina*\n");

   if(vaziaArvore(cab)) printf("\nNAO HA DisciplinaS...\n");
    else {
        printf("\n%-11s%-55s%-11s%-11s\n", "numero", "nome", "curso", "serie");
    }
    imprimir_inOrdem_recD(fb,cab->posCabeca);

        free(cab);
   
}


    //Descrição: Monta a árvore a partir do arquivo e imprime-a do menor número ao maior
    //Pré-Condição: Árvore já existente salva no arquivo binário
    //Pós-Condição: -----------

void imprimir_inOrdem_recD(FILE* fb,int pos){
        if(pos!=-1){
            Arvore_Disciplina* root=lerArvore_Disciplina(fb,pos);
            imprimir_inOrdem_recD(fb,root->esq);//imprime primeiro os elementos da esquerda
            printf("%-10d%-55s%-11d%-11d\n",root->disc.code,root->disc.name,root->disc.curso, root->disc.serie);//imprime a raiz
            imprimir_inOrdem_recD(fb,root->dir);//imprime então os elementos da direita
            free(root);
            
        }
    }


void cadastrarDisciplina(FILE* fb){
        Cabecalho* cab=lerCabecalho(fb);
        Arvore_Disciplina* root=(Arvore_Disciplina*)malloc(sizeof(Arvore_Disciplina));

        root->esq=root->dir=-1;//no ainda nao possui filhos. inicializados como "null"

        printf("Digite o codigo da Disciplina:\n");
        scanf("%d%*c",&root->disc.code);

        

        //não permite inserir um codigo já existente
        if(buscarDisciplina_pos(fb,root->disc.code,cab->posCabeca)==-1){

            printf("Digite o nome da Disciplina:\n");
            scanf("%[^\n]%*c",&root->disc.name);

            printf("Digite o curso da Disciplina:\n");
            scanf("%d%*c",&root->disc.curso);

            printf("Digite a Serie:\n");
            scanf("%d%*c",&root->disc.serie);

            inserirDisciplina(fb,root);//função recursiva de inserir no arquivo binario
            printf("\nDisciplina INSERIDO COM SUCESSO...\n");
        }
        else printf("\nCODIGO EXISTENTE: NAO FOI POSSIVEL CONCLUIR O CADASTRO...\n");

        free(cab);
        free(root);
    }